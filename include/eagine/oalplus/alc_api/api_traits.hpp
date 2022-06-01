/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_ALC_API_API_TRAITS_HPP
#define EAGINE_OALPLUS_ALC_API_API_TRAITS_HPP

#include "result.hpp"
#include <eagine/c_api/api_traits.hpp>
#include <string>

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Policy customizing the generic C-API wrappers for the ALC API
/// @ingroup al_api_wrap
class alc_api_traits : public c_api::default_traits {
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
    auto load_constant(Api& api, string_view name, type_identity<Type>)
      -> std::tuple<Type, bool>;

    /// @brief Links an ALC function with the specified name and Signature.
    template <typename Api, typename Tag, typename Signature>
    auto link_function(Api& api, Tag, string_view name, type_identity<Signature>)
      -> std::add_pointer_t<Signature>;

private:
    std::string _full_name;
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#include <eagine/oalplus/alc_api/api_traits.inl>

#endif // EAGINE_OALPLUS_ALC_API_API_TRAITS_HPP
