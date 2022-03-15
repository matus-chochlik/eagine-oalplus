/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_ALC_API_API_HPP
#define EAGINE_OALPLUS_ALC_API_API_HPP

#include "c_api.hpp"
#include "enum_types.hpp"
#include "objects.hpp"
#include <eagine/scope_exit.hpp>
#include <eagine/span.hpp>
#include <eagine/string_list.hpp>

namespace eagine::oalplus {
//------------------------------------------------------------------------------
#define OALPAFP(FUNC) decltype(c_api::FUNC), &c_api::FUNC
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the ALC API.
/// @ingroup al_api_wrap
/// @see basic_alc_constants
/// @see basic_alc_c_api
template <typename ApiTraits>
class basic_alc_operations : public basic_alc_c_api<ApiTraits> {

public:
    using api_traits = ApiTraits;
    using c_api = basic_alc_c_api<ApiTraits>;

    using enum_type = typename alc_types::enum_type;
    using size_type = typename alc_types::size_type;
    using char_type = typename alc_types::char_type;
    using int_type = typename alc_types::int_type;

    template <typename W, W c_api::*F, typename Signature = typename W::signature>
    class func;

    template <typename W, W c_api::*F, typename RVC, typename... Params>
    class func<W, F, RVC(Params...)>
      : public wrapped_c_api_function<c_api, api_traits, nothing_t, W, F> {
        using base = wrapped_c_api_function<c_api, api_traits, nothing_t, W, F>;

    private:
        template <typename Res>
        constexpr auto _check(device_handle dev, Res&& res) const noexcept {
            res.error_code(
              this->api().GetError(static_cast<alc_types::device_type*>(dev)));
            return std::forward<Res>(res);
        }

    protected:
        template <typename... Args>
        constexpr auto _chkcall(device_handle dev, Args&&... args)
          const noexcept {
            return this->_check(dev, this->_call(std::forward<Args>(args)...));
        }

        template <typename... Args>
        constexpr auto _cnvchkcall(device_handle dev, Args&&... args)
          const noexcept {
            return this->_chkcall(dev, _conv(std::forward<Args>(args))...)
              .cast_to(type_identity<RVC>{});
        }

        using base::_conv;

    public:
        using base::base;

        constexpr auto operator()(Params... params) const noexcept {
            return this->_chkcall(_conv(params)...)
              .cast_to(type_identity<RVC>{});
        }

        auto bind(Params... params) const noexcept {
            return [this, params...] {
                return (*this)(params...);
            };
        }
    };

    // open_device
    struct : func<OALPAFP(OpenDevice)> {
        using func<OALPAFP(OpenDevice)>::func;

        constexpr auto operator()() const noexcept {
            return this->_chkcall(device_handle{}, nullptr)
              .cast_to(type_identity<device_handle>());
        }

        auto operator()(const string_view name) const noexcept {
            return this->_cnvchkcall(device_handle{}, name)
              .cast_to(type_identity<device_handle>());
        }
    } open_device;

    // close_device
    struct : func<OALPAFP(CloseDevice)> {
        using func<OALPAFP(CloseDevice)>::func;

        constexpr auto operator()(device_handle dev) const noexcept {
            return this->_cnvchkcall(dev, dev);
        }

        auto bind(device_handle dev) const noexcept {
            return [this, dev] {
                return (*this)(dev);
            };
        }

        auto raii(device_handle dev) const noexcept {
            return eagine::finally(this->bind(dev));
        }
    } close_device;

    // create_context
    struct : func<OALPAFP(CreateContext)> {
        using func<OALPAFP(CreateContext)>::func;

        constexpr auto operator()(device_handle dev) const noexcept {
            return this->_cnvchkcall(dev, dev, nullptr)
              .cast_to(type_identity<context_handle>());
        }

        constexpr auto operator()(
          device_handle dev,
          span<const int_type> attributes) const noexcept {
            return this->_cnvchkcall(dev, dev, attributes.data())
              .cast_to(type_identity<context_handle>());
        }
    } create_context;

    // destroy_context
    struct : func<OALPAFP(DestroyContext)> {
        using func<OALPAFP(DestroyContext)>::func;

        constexpr auto operator()(device_handle dev, context_handle ctx)
          const noexcept {
            return this->_cnvchkcall(dev, ctx);
        }

        auto bind(device_handle dev, context_handle ctxt) const noexcept {
            return [this, dev, ctxt] {
                return (*this)(dev, ctxt);
            };
        }

        auto raii(device_handle dev, context_handle ctx) const noexcept {
            return eagine::finally(this->bind(dev, ctx));
        }
    } destroy_context;

    // make_context_current
    struct : func<OALPAFP(MakeContextCurrent)> {
        using func<OALPAFP(MakeContextCurrent)>::func;

        constexpr auto operator()(device_handle dev, context_handle ctx)
          const noexcept {
            return this->_cnvchkcall(dev, ctx);
        }

        constexpr auto operator()(context_handle ctx) const noexcept {
            return (*this)(device_handle{}, ctx);
        }

        auto bind(device_handle dev, context_handle ctx) const noexcept {
            return [this, dev, ctx] {
                return (*this)(dev, ctx);
            };
        }

        constexpr auto operator()() const noexcept {
            return (*this)(device_handle{}, context_handle{});
        }

        auto bind() const noexcept {
            return [this] {
                return (*this)();
            };
        }

        auto raii(device_handle dev, context_handle ctx) const noexcept {
            return eagine::finally(this->bind(dev, ctx));
        }

        auto raii() const noexcept {
            return eagine::finally(this->bind());
        }

        constexpr auto none(device_handle dev) const noexcept {
            return (*this)(dev, context_handle{});
        }
    } make_context_current;

    // get_current_context
    struct : func<OALPAFP(GetCurrentContext)> {
        using func<OALPAFP(GetCurrentContext)>::func;

        constexpr auto operator()(device_handle dev) const noexcept {
            return this->_cnvchkcall(dev);
        }

        constexpr auto operator()() const noexcept {
            return this->_cnvchkcall(device_handle{});
        }
    } get_current_context;

    // get_integer
    struct : func<OALPAFP(GetIntegerv)> {
        using func<OALPAFP(GetIntegerv)>::func;

        constexpr auto operator()(device_handle dev, alc_integer_query query)
          const noexcept {
            int_type result{};
            return this
              ->_cnvchkcall(dev, dev, enum_type(query), size_type(1), &result)
              .replaced_with(result);
        }

        constexpr auto operator()(alc_integer_query query) const noexcept {
            return (*this)(device_handle{}, query);
        }

        constexpr auto operator()(
          device_handle dev,
          alc_integer_query query,
          span<int_type> dst) const noexcept {
            return this->_cnvchkcall(
              dev, dev, enum_type(query), size_type(dst.size()), dst.data());
        }
    } get_integer;

    // get_string
    struct : func<OALPAFP(GetString)> {
        using func<OALPAFP(GetString)>::func;

        constexpr auto operator()(device_handle dev, alc_string_query query)
          const noexcept {
            return this->_cnvchkcall(dev, dev, query)
              .cast_to(type_identity<string_view>{});
        }

        constexpr auto operator()(alc_string_query query) const noexcept {
            return (*this)(device_handle{}, query);
        }

        constexpr auto operator()(device_handle) const noexcept {
            return this->fake_empty_c_str().cast_to(
              type_identity<string_view>{});
        }
    } get_string;

    // get_strings
    auto get_strings(device_handle dev, alc_string_query query, char separator)
      const noexcept {
        return get_string(dev, query).transformed([separator](auto src, bool) {
            return split_into_string_list(src, separator);
        });
    }

    // get_extensions
    auto get_extensions(device_handle dev) const noexcept {
#ifdef ALC_EXTENSIONS
        return get_string(dev, alc_string_query(ALC_EXTENSIONS))
#else
        return get_string(dev)
#endif
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    // get_default_device_specifier
    auto get_default_device_specifier() const noexcept {
#ifdef ALC_DEFAULT_DEVICE_SPECIFIER
        return get_string(
          device_handle{}, alc_string_query(ALC_DEFAULT_DEVICE_SPECIFIER));
#else
        return get_string(device_handle{});
#endif
    }

    // get_device_specifiers
    auto get_device_specifiers() const noexcept {
#ifdef ALC_DEVICE_SPECIFIER
        return get_string(
                 device_handle{}, alc_string_query(ALC_DEVICE_SPECIFIER))
#else
        return get_string(device_handle{})
#endif
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, '\0'); });
    }

    // get_capture_default_device_specifier
    auto get_capture_default_device_specifier() const noexcept {
#ifdef ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER
        return get_string(
          device_handle{},
          alc_string_query(ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER));
#else
        return get_string(device_handle{});
#endif
    }

    // get_capture_device_specifiers
    auto get_capture_device_specifiers() const noexcept {
#ifdef ALC_CAPTURE_DEVICE_SPECIFIER
        return get_string(
                 device_handle{},
                 alc_string_query(ALC_CAPTURE_DEVICE_SPECIFIER))
#else
        return get_string(device_handle{})
#endif
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, '\0'); });
    }

    basic_alc_operations(api_traits& traits);
};
//------------------------------------------------------------------------------
#undef OALPAFP
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#endif // EAGINE_OALPLUS_ALC_API_API_HPP
