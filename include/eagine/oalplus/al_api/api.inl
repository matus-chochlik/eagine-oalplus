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
  : c_api{traits}
  , gen_sources{"gen_sources", *this}
  , gen_buffers{"gen_buffers", *this}
  , gen_effects{"gen_effects", *this}
  , gen_filters{"gen_filters", *this}
  , gen_auxiliary_effect_slots{"gen_auxiliary_effect_slots", *this}
  , delete_sources{"delete_sources", *this}
  , delete_buffers{"delete_buffers", *this}
  , delete_effects{"delete_effects", *this}
  , delete_filters{"delete_filters", *this}
  , delete_auxiliary_effect_slots{"delete_auxiliary_effect_slots", *this}
  , is_source{"is_source", *this}
  , is_buffer{"is_buffer", *this}
  , is_effect{"is_effect", *this}
  , is_filter{"is_filter", *this}
  , is_auxiliary_effect_slot{"is_auxiliary_effect_slot", *this}
  , listener_i{"listener_i", *this}
  , listener_f{"listener_f", *this}
  , get_listener_i{"get_listener_i", *this}
  , get_listener_f{"get_listener_f", *this}
  , buffer_i{"buffer_i", *this}
  , buffer_f{"buffer_f", *this}
  , get_buffer_i{"get_buffer_i", *this}
  , get_buffer_f{"get_buffer_f", *this}
  , source_i{"source_i", *this}
  , source_f{"source_f", *this}
  , get_source_i{"get_source_i", *this}
  , get_source_f{"get_source_f", *this}
  , source_queue_buffers{"source_queue_buffers", *this}
  , source_unqueue_buffers{"source_unqueue_buffers", *this}
  , source_play{"source_play", *this}
  , source_pause{"source_pause", *this}
  , source_stop{"source_stop", *this}
  , source_rewind{"source_rewind", *this}
  , get_string{"get_string", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
