/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_ALC_API_FWD_HPP
#define EAGINE_OALPLUS_ALC_API_FWD_HPP

namespace eagine::oalplus {
//------------------------------------------------------------------------------
class alc_api_traits;

template <typename ApiTraits>
class basic_alc_api;

/// @brief Alias for the default instantation of basic_alc_api.
/// @ingroup al_api_wrap
using alc_api = basic_alc_api<alc_api_traits>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#endif // EAGINE_OALPLUS_ALC_API_FWD_HPP
