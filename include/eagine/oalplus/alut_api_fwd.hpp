/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_ALUT_API_FWD_HPP
#define EAGINE_OALPLUS_ALUT_API_FWD_HPP

namespace eagine::oalp {
//------------------------------------------------------------------------------
class alut_api_traits;

template <typename ApiTraits>
class basic_alut_api;

/// @brief Alias for the default instantation of basic_alut_api.
/// @ingroup al_api_wrap
using alut_api = basic_alut_api<alut_api_traits>;
//------------------------------------------------------------------------------
} // namespace eagine::oalp

#endif // EAGINE_OALPLUS_ALUT_API_FWD_HPP
