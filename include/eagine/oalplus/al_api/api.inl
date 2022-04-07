/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

namespace eagine::oalplus {
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_al_operations<ApiTraits>::basic_al_operations(api_traits& traits)
  : al_api{traits}
  , source_play{"source_play", *this}
  , source_pause{"source_pause", *this}
  , source_stop{"source_stop", *this}
  , source_rewind{"source_rewind", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
