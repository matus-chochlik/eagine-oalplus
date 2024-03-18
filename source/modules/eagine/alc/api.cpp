/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#include <cassert>
#if __has_include(<AL/alc.h>)
#include <AL/alc.h>
#define EAGINE_HAS_ALC 1
#else
#define EAGINE_HAS_ALC 0
#endif

export module eagine.oalplus.alc:api;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.string;
import eagine.core.utility;
import eagine.core.identifier;
import eagine.core.c_api;
import eagine.core.main_ctx;
import :config;
import :enum_types;
import :attributes;
import :result;
import :c_api;
import :objects;
import :constants;
import :api_traits;

namespace eagine::oalplus {
using c_api::simple_adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the ALC API.
/// @ingroup al_api_wrap
/// @see basic_alc_constants
/// @see basic_alc_c_api
export template <typename ApiTraits>
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

    using _open_device_t = simple_adapted_function<
      &alc_api::OpenDevice,
      owned_device_handle(device_handle, string_view)>;

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

    auto make_function(device_tag) const noexcept -> const auto& {
        return open_device;
    }

    simple_adapted_function<
      &alc_api::CloseDevice,
      c_api::collapsed<bool_type>(owned_device_handle)>
      close_device{*this};

    auto clean_up(owned_device_handle obj) const noexcept {
        return close_device(std::move(obj));
    }

    simple_adapted_function<
      &alc_api::CreateContext,
      owned_context_handle(device_handle, context_attributes)>
      create_context{*this};

    auto make_function(context_tag) const noexcept -> const auto& {
        return create_context;
    }

    simple_adapted_function<
      &alc_api::DestroyContext,
      void(device_handle, owned_context_handle)>
      destroy_context{*this};

    auto clean_up(owned_context_handle ctx, device_handle dev) const noexcept {
        return destroy_context(dev, std::move(ctx));
    }

    using _make_context_current_t = simple_adapted_function<
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

    using _get_current_context_t = simple_adapted_function<
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
      simple_adapted_function<
        &alc_api::GetIntegerv,
        bool_type(device_handle, alc_integer_query, span<int_type>)>,
      simple_adapted_function<
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

    using _get_string_t = simple_adapted_function<
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
        return get_string(dev, query).transform([separator](auto src) {
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
          .transform([](auto src) { return split_into_string_list(src, ' '); })
          .or_default();
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
          .transform(
            [](auto src) { return split_into_string_list(src, '\0'); });
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
          .transform(
            [](auto src) { return split_into_string_list(src, '\0'); });
    }

    basic_alc_operations(api_traits& traits)
      : alc_api{traits} {}
};
//------------------------------------------------------------------------------
export template <typename ApiTraits>
class basic_alc_api
  : public main_ctx_object
  , protected ApiTraits
  , public basic_alc_operations<ApiTraits>
  , public basic_alc_constants<ApiTraits> {
public:
    basic_alc_api(main_ctx_parent parent, ApiTraits traits)
      : main_ctx_object{"ALCAPI", parent}
      , ApiTraits{std::move(traits)}
      , basic_alc_operations<ApiTraits>{*static_cast<ApiTraits*>(this)}
      , basic_alc_constants<ApiTraits>{
          *static_cast<ApiTraits*>(this),
          *static_cast<basic_alc_operations<ApiTraits>*>(this)} {}

    basic_alc_api(main_ctx_parent parent)
      : basic_alc_api{parent, ApiTraits{}} {}

    /// @brief Returns a reference to the wrapped operations.
    auto operations() const noexcept -> const basic_alc_operations<ApiTraits>& {
        return *this;
    }

    /// @brief Returns a reference to the wrapped constants.
    auto constants() const noexcept -> const basic_alc_constants<ApiTraits>& {
        return *this;
    }

    template <identifier_value Id, typename Handle, Handle invalid, typename... P>
    auto to_object(
      c_api::basic_owned_handle<alc_lib_tag<Id>, Handle, invalid> name,
      P...) const noexcept
      -> basic_alc_object<
        basic_alc_api<ApiTraits>,
        alc_lib_tag<Id>,
        Handle,
        invalid,
        P...>;

    template <
      identifier_value Id,
      typename Handle,
      Handle invalid,
      typename Info,
      c_api::result_validity validity,
      typename... P>
    auto to_object(
      c_api::result<
        c_api::basic_owned_handle<alc_lib_tag<Id>, Handle, invalid>,
        Info,
        validity>&& res,
      P...) const noexcept
      -> basic_alc_object<
        basic_alc_api<ApiTraits>,
        alc_lib_tag<Id>,
        Handle,
        invalid,
        P...>;

    auto create_object(device_tag tg) const noexcept {
        return to_object(this->make_function(tg)());
    }

    auto create_object(
      context_tag tg,
      device_handle dev,
      const context_attributes& attr) const noexcept {
        return to_object(this->make_function(tg)(dev, attr), dev);
    }

    auto open_device_object() const noexcept {
        return create_object(device_tag{});
    }

    auto create_context_object(
      device_handle dev,
      const context_attributes& attr) const noexcept {
        return create_object(context_tag{}, dev, attr);
    }
};

export template <std::size_t I, typename ApiTraits>
auto get(const basic_alc_api<ApiTraits>& x) noexcept -> const
  typename std::tuple_element<I, basic_alc_api<ApiTraits>>::type& {
    return x;
}
//------------------------------------------------------------------------------
template <typename ApiTraits>
template <identifier_value Id, typename Handle, Handle invalid, typename... P>
auto basic_alc_api<ApiTraits>::to_object(
  c_api::basic_owned_handle<alc_lib_tag<Id>, Handle, invalid> name,
  P... params) const noexcept
  -> basic_alc_object<
    basic_alc_api<ApiTraits>,
    alc_lib_tag<Id>,
    Handle,
    invalid,
    P...> {
    return {*this, std::move(name), params...};
}
//------------------------------------------------------------------------------
template <typename ApiTraits>
template <
  identifier_value Id,
  typename Handle,
  Handle invalid,
  typename Info,
  c_api::result_validity validity,
  typename... P>
auto basic_alc_api<ApiTraits>::to_object(
  c_api::result<
    c_api::basic_owned_handle<alc_lib_tag<Id>, Handle, invalid>,
    Info,
    validity>&& res,
  P... params) const noexcept
  -> basic_alc_object<
    basic_alc_api<ApiTraits>,
    alc_lib_tag<Id>,
    Handle,
    invalid,
    P...> {
    return std::move(res)
      .transform(
        [&, this](auto&& name) -> basic_alc_object<
                                 basic_alc_api<ApiTraits>,
                                 alc_lib_tag<Id>,
                                 Handle,
                                 invalid,
                                 P...> {
            return {*this, std::move(name), params...};
        })
      .or_default();
}
//------------------------------------------------------------------------------
/// @brief Alias for the default instantation of basic_alc_api.
/// @ingroup al_api_wrap
export using alc_api = basic_alc_api<alc_api_traits>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std {

template <typename ApiTraits>
struct tuple_size<eagine::oalplus::basic_alc_api<ApiTraits>>
  : integral_constant<std::size_t, 2> {};

template <typename ApiTraits>
struct tuple_element<0, eagine::oalplus::basic_alc_api<ApiTraits>>
  : type_identity<eagine::oalplus::basic_alc_operations<ApiTraits>> {};

template <typename ApiTraits>
struct tuple_element<1, eagine::oalplus::basic_alc_api<ApiTraits>>
  : type_identity<eagine::oalplus::basic_alc_constants<ApiTraits>> {};

} // namespace std
namespace eagine::oalplus {
//------------------------------------------------------------------------------
export template <typename ApiTraits>
using basic_alc_api_reference =
  c_api::basic_api_reference<const basic_alc_api<ApiTraits>>;

export using alc_api_reference = basic_alc_api_reference<alc_api_traits>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

