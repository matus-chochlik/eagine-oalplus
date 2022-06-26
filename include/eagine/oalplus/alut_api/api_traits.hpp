/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_ALUT_API_API_TRAITS_HPP
#define EAGINE_OALPLUS_ALUT_API_API_TRAITS_HPP

#include "result.hpp"
#include <eagine/c_api/api_traits.hpp>

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Policy customizing the generic C-API wrappers for the ALUT API
/// @ingroup al_api_wrap
class alut_api_traits : public c_api::default_traits {
public:
    /// @brief Alias for result type of currently unavailable functions.
    template <typename R>
    using no_result = alut_no_result<R>;

    /// @brief Alias for result type of functions.
    template <typename R>
    using result = alut_result<R>;

    /// @brief Alias for result type of optionally available functions.
    template <typename R>
    using opt_result = alut_opt_result<R>;

private:
    std::string _full_name;
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#include <eagine/oalplus/alut_api/api_traits.inl>

#endif // EAGINE_OALPLUS_ALUT_API_API_TRAITS_HPP
