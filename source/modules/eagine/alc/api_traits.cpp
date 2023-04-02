/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/alc.h>)
#include <AL/alc.h>
#define EAGINE_HAS_ALC 1
#else
#define EAGINE_HAS_ALC 0
#endif

export module eagine.oalplus.alc:api_traits;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :result;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Policy customizing the generic C-API wrappers for the ALC API
/// @ingroup al_api_wrap
export class alc_api_traits : public c_api::default_traits {
public:
    /// @brief Alias for result type of currently unavailable functions.
    template <typename R>

    /// @brief Alias for result type of functions.
    using no_result = alc_no_result<R>;
    template <typename R>

    /// @brief Alias for result type of optionally available functions.
    using result = alc_result<R>;
    template <typename R>
    using opt_result = alc_opt_result<R>;

    /// @brief Loads an ALC constant with the specified name and Type.
    template <typename Api, typename Type>
    auto load_constant(Api& api, string_view name, std::type_identity<Type>)
      -> std::tuple<Type, bool>;

    /// @brief Links an ALC function with the specified name and Signature.
    template <typename Api, typename Tag, typename Signature>
    auto link_function(
      Api& api,
      Tag,
      string_view name,
      std::type_identity<Signature>) -> std::add_pointer_t<Signature>;

private:
    std::string _full_name;
};
//------------------------------------------------------------------------------
template <typename Api, typename Type>
auto alc_api_traits::load_constant(
  Api& api,
  string_view name,
  std::type_identity<Type>) -> std::tuple<Type, bool> {
    if(api.GetEnumValue) {
        _full_name.clear();
        _full_name.reserve(4 + name.size() + 1);
        _full_name.append("ALC_");
        _full_name.append(name.data(), std::size_t(name.size()));
        return {
          static_cast<Type>(api.GetEnumValue(nullptr, _full_name.c_str())),
          true};
    }
    return {{}, false};
}
//------------------------------------------------------------------------------
template <typename Api, typename Tag, typename Signature>
auto alc_api_traits::link_function(
  Api& api,
  Tag,
  string_view name,
  std::type_identity<Signature>) -> std::add_pointer_t<Signature> {
    if(api.GetProcAddress and api.GetError) {
        _full_name.clear();
        _full_name.reserve(3 + name.size() + 1);
        _full_name.append("alc");
        _full_name.append(name.data(), std::size_t(name.size()));
        auto func = api.GetProcAddress(nullptr, _full_name.c_str());
        if(alc_types::error_code_no_error(api.GetError(nullptr))) {
            return reinterpret_cast<std::remove_pointer_t<Signature>*>(func);
        }
    }
    return nullptr;
}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

