/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oalplus.al:objects;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.identifier;
import eagine.core.c_api;
import :config;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
export template <identifier_value Id>
using al_lib_tag = static_message_id<"al", Id>;

/// @brief Alias for template wrapping AL object handles.
/// @ingroup al_api_wrap
/// @see al_owned_object_name
/// @see al_object_name_view
/// @see al_object_name_span
/// @see al_object_name_array
export template <typename Tag>
using al_object_name = c_api::basic_handle<Tag, al_types::name_type>;

/// @brief Alias for template wrapping owned AL object handles.
/// @ingroup al_api_wrap
/// @see al_object_name
export template <typename Tag>
using al_owned_object_name =
  c_api::basic_owned_handle<Tag, al_types::name_type>;

/// @brief Alias for template wrapping a mutable span of AL object handles.
/// @ingroup al_api_wrap
/// @see al_object_name_view
/// @see al_object_name_array
export template <typename Tag>
using al_object_name_span = c_api::basic_handle_span<al_object_name<Tag>>;

/// @brief Alias for AL object template.
/// @ingroup al_api_wrap
/// @see al_object_name
/// @see al_owned_object_name
export template <typename Api, typename Tag, typename... P>
using al_object =
  c_api::basic_object_from_handle_t<Api, al_object_name<Tag>, P...>;

/// @brief Alias for template wrapping a const span of AL object handles.
/// @ingroup al_api_wrap
/// @see al_object_name_span
/// @see al_object_name_array
export template <typename Tag>
using al_object_name_view = c_api::basic_handle_view<al_object_name<Tag>>;

/// @brief Alias for template wrapping an array of AL object handles.
/// @ingroup al_api_wrap
/// @see al_object_name_vector
/// @see al_object_name_span
/// @see al_object_name_view
export template <typename Tag, std::size_t N>
using al_object_name_array = c_api::basic_handle_array<al_object_name<Tag>, N>;

/// @brief Alias for template wrapping a vector of AL object handles.
/// @ingroup al_api_wrap
/// @see al_object_name_array
/// @see al_object_name_span
/// @see al_object_name_view
export template <typename Tag>
using al_object_name_vector = c_api::basic_handle_vector<al_object_name<Tag>>;
//------------------------------------------------------------------------------
export using source_tag = al_lib_tag<"Source">;
export using buffer_tag = al_lib_tag<"Buffer">;
export using effect_tag = al_lib_tag<"Effect">;
export using filter_tag = al_lib_tag<"Filter">;
export using auxiliary_effect_slot_tag = al_lib_tag<"AuxEffSlot">;
//------------------------------------------------------------------------------
export using source_name = al_object_name<source_tag>;
export using buffer_name = al_object_name<buffer_tag>;
export using effect_name = al_object_name<effect_tag>;
export using filter_name = al_object_name<filter_tag>;
export using auxiliary_effect_slot_name =
  al_object_name<auxiliary_effect_slot_tag>;
//------------------------------------------------------------------------------
export using owned_source_name = al_owned_object_name<source_tag>;
export using owned_buffer_name = al_owned_object_name<buffer_tag>;
export using owned_effect_name = al_owned_object_name<effect_tag>;
export using owned_filter_name = al_owned_object_name<filter_tag>;
export using owned_auxiliary_effect_slot_name =
  al_owned_object_name<auxiliary_effect_slot_tag>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

