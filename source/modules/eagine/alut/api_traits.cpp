/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/alut.h>)
#include <AL/alut.h>
#define EAGINE_HAS_ALUT 1
#else
#define EAGINE_HAS_ALUT 0
#endif

export module eagine.oalplus.alut:api_traits;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :result;
import std;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Policy customizing the generic C-API wrappers for the ALUT API
/// @ingroup al_api_wrap
export class alut_api_traits : public c_api::default_traits {
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

