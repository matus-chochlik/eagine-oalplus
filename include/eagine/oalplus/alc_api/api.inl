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
basic_alc_operations<ApiTraits>::basic_alc_operations(api_traits& traits)
  : c_api{traits}
  , open_device{"open_device", *this}
  , close_device{"close_device", *this}
  , create_context{"create_context", *this}
  , destroy_context{"destroy_context", *this}
  , make_context_current{"make_context_current", *this}
  , get_current_context{"get_current_context", *this}
  , get_integer{"get_integer", *this}
  , get_string{"get_string", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
