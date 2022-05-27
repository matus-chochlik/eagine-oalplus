/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_AL_API_OBJECT_NAME_HPP
#define EAGINE_OALPLUS_AL_API_OBJECT_NAME_HPP

#include "config.hpp"
#include <eagine/c_api/handle.hpp>
#include <eagine/message_id.hpp>

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Alias for template wrapping GL object handles.
/// @ingroup gl_api_wrap
/// @see gl_owned_object_name
/// @see al_object_name_view
/// @see al_object_name_span
/// @see al_object_name_array
template <typename Tag>
using al_object_name = c_api::basic_handle<Tag, al_types::name_type>;

/// @brief Alias for template wrapping owned GL object handles.
/// @ingroup gl_api_wrap
/// @see al_object_name
template <typename Tag>
using al_owned_object_name =
  c_api::basic_owned_handle<Tag, al_types::name_type>;

/// @brief Alias for template wrapping a mutable span of GL object handles.
/// @ingroup gl_api_wrap
/// @see al_object_name_view
/// @see al_object_name_array
template <typename Tag>
using al_object_name_span = c_api::basic_handle_span<al_object_name<Tag>>;

/// @brief Alias for template wrapping a const span of GL object handles.
/// @ingroup gl_api_wrap
/// @see al_object_name_span
/// @see al_object_name_array
template <typename Tag>
using al_object_name_view = c_api::basic_handle_view<al_object_name<Tag>>;

/// @brief Alias for template wrapping an array of GL object handles.
/// @ingroup gl_api_wrap
/// @see al_object_name_vector
/// @see al_object_name_span
/// @see al_object_name_view
template <typename Tag, std::size_t N>
using al_object_name_array = c_api::basic_handle_array<al_object_name<Tag>, N>;

/// @brief Alias for template wrapping a vector of GL object handles.
/// @ingroup gl_api_wrap
/// @see al_object_name_array
/// @see al_object_name_span
/// @see al_object_name_view
template <typename Tag>
using al_object_name_vector = c_api::basic_handle_vector<al_object_name<Tag>>;
//------------------------------------------------------------------------------
using source_tag = EAGINE_MSG_TYPE(al, Source);
using buffer_tag = EAGINE_MSG_TYPE(al, Buffer);
using effect_tag = EAGINE_MSG_TYPE(al, Effect);
using filter_tag = EAGINE_MSG_TYPE(al, Filter);
using auxiliary_effect_slot_tag = EAGINE_MSG_TYPE(al, AuxEffSlot);
//------------------------------------------------------------------------------
using source_name = al_object_name<source_tag>;
using buffer_name = al_object_name<buffer_tag>;
using effect_name = al_object_name<effect_tag>;
using filter_name = al_object_name<filter_tag>;
using auxiliary_effect_slot_name = al_object_name<auxiliary_effect_slot_tag>;
//------------------------------------------------------------------------------
using owned_source_name = al_owned_object_name<source_tag>;
using owned_buffer_name = al_owned_object_name<buffer_tag>;
using owned_effect_name = al_owned_object_name<effect_tag>;
using owned_filter_name = al_owned_object_name<filter_tag>;
using owned_auxiliary_effect_slot_name =
  al_owned_object_name<auxiliary_effect_slot_tag>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#endif // EAGINE_OALPLUS_AL_API_OBJECT_NAME_HPP
