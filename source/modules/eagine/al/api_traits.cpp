/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/al.h>)
#include <AL/al.h>
#define EAGINE_HAS_AL 1
#else
#define EAGINE_HAS_AL 0
#endif

export module eagine.oalplus.al:api_traits;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :result;
import <string>;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Policy customizing the generic C-API wrappers for the AL API
/// @ingroup al_api_wrap
class al_api_traits : public c_api::default_traits {
public:
    /// @brief Alias for result type of currently unavailable functions.
    template <typename R>
    using no_result = al_no_result<R>;

    /// @brief Alias for result type of functions.
    template <typename R>
    using result = al_result<R>;

    /// @brief Alias for result type of optionally available functions.
    template <typename R>
    using opt_result = al_opt_result<R>;

    /// @brief Loads an AL constant with the specified name and Type.
    template <typename Api, typename Type>
    auto load_constant(Api& api, string_view name, std::type_identity<Type>)
      -> std::tuple<Type, bool>;

    /// @brief Links an AL function with the specified name and Signature.
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
auto al_api_traits::load_constant(
  Api& api,
  string_view name,
  std::type_identity<Type>) -> std::tuple<Type, bool> {
    if(api.GetEnumValue && api.GetError) {
        _full_name.clear();
        _full_name.reserve(3 + name.size() + 1);
        _full_name.append("AL_");
        _full_name.append(name.data(), std::size_t(name.size()));
        const auto val = api.GetEnumValue(_full_name.c_str());
        if(al_types::error_code_no_error(api.GetError())) {
            return {static_cast<Type>(val), true};
        }
    }
    return {{}, false};
}
//------------------------------------------------------------------------------
template <typename Api, typename Tag, typename Signature>
auto al_api_traits::link_function(
  Api& api,
  Tag,
  string_view name,
  std::type_identity<Signature>) -> std::add_pointer_t<Signature> {
    if(api.GetProcAddress && api.GetError) {
        _full_name.clear();
        _full_name.reserve(2 + name.size() + 1);
        _full_name.append("al");
        _full_name.append(name.data(), std::size_t(name.size()));
        auto func = api.GetProcAddress(_full_name.c_str());
        if(al_types::error_code_no_error(api.GetError())) {
            return reinterpret_cast<std::remove_pointer_t<Signature>*>(func);
        }
    }
    return nullptr;
}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

