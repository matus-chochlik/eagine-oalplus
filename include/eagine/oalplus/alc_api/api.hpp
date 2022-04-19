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
#include "context_attribs.hpp"
#include "enum_types.hpp"
#include "objects.hpp"
#include <eagine/c_api/adapted_function.hpp>
#include <eagine/scope_exit.hpp>
#include <eagine/span.hpp>
#include <eagine/string_list.hpp>

namespace eagine::oalplus {
using c_api::adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the ALC API.
/// @ingroup al_api_wrap
/// @see basic_alc_constants
/// @see basic_alc_c_api
template <typename ApiTraits>
class basic_alc_operations : public basic_alc_c_api<ApiTraits> {

public:
    using api_traits = ApiTraits;
    using alc_api = basic_alc_c_api<ApiTraits>;

    using bool_type = typename alc_types::bool_type;
    using enum_type = typename alc_types::enum_type;
    using size_type = typename alc_types::size_type;
    using char_type = typename alc_types::char_type;
    using int_type = typename alc_types::int_type;
    using device_type = typename alc_types::device_type;
    using context_type = typename alc_types::context_type;

    using _open_device_t = adapted_function<
      &alc_api::OpenDevice,
      device_handle(device_handle, string_view)>;

    struct : _open_device_t {
        using base = _open_device_t;
        using base::base;
        constexpr auto operator()(const string_view s) const noexcept {
            return base::operator()(device_handle{}, s);
        }

        constexpr auto operator()() const noexcept {
            return base::operator()(device_handle{}, {});
        }
    } open_device{*this};

    adapted_function<
      &alc_api::CloseDevice,
      c_api::collapsed<bool_type>(device_handle)>
      close_device{*this};

    adapted_function<
      &alc_api::CreateContext,
      context_handle(device_handle, context_attributes)>
      create_context{*this};

    adapted_function<
      &alc_api::DestroyContext,
      void(device_handle, context_handle)>
      destroy_context{*this};

    using _make_context_current_t = adapted_function<
      &alc_api::MakeContextCurrent,
      c_api::collapsed<bool_type>(device_handle, context_handle)>;

    struct : _make_context_current_t {
        using base = _make_context_current_t;
        using base::base;
        using base::operator();
        constexpr auto operator()(context_handle ctx) const noexcept {
            return (*this)(device_handle{}, ctx);
        }

        constexpr auto operator()() const noexcept {
            return (*this)(device_handle{}, context_handle{});
        }

        auto bind() const noexcept {
            return [this] {
                return (*this)();
            };
        }

        auto raii() const noexcept {
            return eagine::finally(this->bind());
        }

        constexpr auto none(device_handle dev) const noexcept {
            return (*this)(dev, context_handle{});
        }
    } make_context_current{*this};

    using _get_current_context_t = adapted_function<
      &alc_api::GetCurrentContext,
      context_handle(device_handle)>;

    struct : _get_current_context_t {
        using base = _get_current_context_t;
        using base::base;
        using base::operator();

        constexpr auto operator()() const noexcept {
            return base::operator()(device_handle{});
        }
    } get_current_context{*this};

    using _get_integer_t = c_api::combined<
      adapted_function<
        &alc_api::GetIntegerv,
        bool_type(device_handle, alc_integer_query, span<int_type>)>,
      adapted_function<
        &alc_api::GetIntegerv,
        c_api::returned<int_type>(
          device_handle,
          alc_integer_query,
          c_api::substituted<1>,
          c_api::returned<int_type>)>>;

    struct : _get_integer_t {
        using base = _get_integer_t;
        using base::base;
        using base::operator();

        constexpr auto operator()(alc_integer_query query) const noexcept {
            return base::operator()(device_handle{}, query);
        }
    } get_integer{*this};

    using _get_string_t = adapted_function<
      &alc_api::GetString,
      string_view(device_handle, alc_string_query)>;

    struct : _get_string_t {
        using base = _get_string_t;
        using base::base;
        using base::operator();

        constexpr auto operator()(alc_string_query query) const noexcept {
            return base::operator()(device_handle{}, query);
        }

        constexpr auto operator()(device_handle) const noexcept {
            return base::fail();
        }
    } get_string{*this};

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

    basic_alc_operations(api_traits& traits)
      : alc_api{traits} {}
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#endif // EAGINE_OALPLUS_ALC_API_API_HPP
