/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oalplus.alc:objects;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.identifier;
import eagine.core.c_api;
import :config;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
export template <identifier_value Id>
using alc_lib_tag = static_message_id<"alc", Id>;

/// @brief Tag type denoting ALC device object.
/// @ingroup al_api_wrap
/// @see device_handle
export using device_tag = alc_lib_tag<"Device">;

/// @brief Tag type denoting ALC context object.
/// @ingroup al_api_wrap
/// @see context_handle
export using context_tag = alc_lib_tag<"Context">;

//------------------------------------------------------------------------------
/// @brief Alias for ALC device handle wrapper.
/// @ingroup al_api_wrap
export using device_handle = c_api::basic_handle<
  device_tag,
  alc_types::device_type*,
  static_cast<alc_types::device_type*>(nullptr)>;

/// @brief Alias for ALC context handle wrapper.
/// @ingroup al_api_wrap
export using context_handle = c_api::basic_handle<
  context_tag,
  alc_types::context_type*,
  static_cast<alc_types::context_type*>(nullptr)>;
//------------------------------------------------------------------------------
/// @brief Alias for owned ALC device handle wrapper.
/// @ingroup al_api_wrap
/// @see device_handle
export using owned_device_handle = c_api::basic_owned_handle<
  device_tag,
  alc_types::device_type*,
  static_cast<alc_types::device_type*>(nullptr)>;

/// @brief Alias for owned ALC context handle wrapper.
/// @ingroup al_api_wrap
/// @see context_handle
export using owned_context_handle = c_api::basic_owned_handle<
  context_tag,
  alc_types::context_type*,
  static_cast<alc_types::context_type*>(nullptr)>;
//------------------------------------------------------------------------------
/// @brief Alias for ALC object template.
/// @ingroup al_api_wrap
/// @see al_object_name
/// @see al_owned_object_name
export template <
  typename Api,
  typename Tag,
  typename Handle,
  Handle invalid,
  typename... P>
struct basic_alc_object
  : c_api::basic_object_from_handle_t<
      Api,
      c_api::basic_handle<Tag, Handle, invalid>,
      P...> {
    using base = c_api::basic_object_from_handle_t<
      Api,
      c_api::basic_handle<Tag, Handle, invalid>,
      P...>;
    using base::base;
};
} // namespace eagine::oalplus

namespace eagine::c_api {

export template <typename CH, typename... CT, typename... CppT>
    requires(not std::is_same_v<CH, oalplus::alc_types::device_type*>)
struct make_args_map<
  1,
  1,
  mp_list<CH, CT...>,
  mp_list<oalplus::device_handle, CppT...>>
  : make_args_map<1, 2, mp_list<CH, CT...>, mp_list<CppT...>> {};

export template <>
struct make_args_map<
  1,
  1,
  mp_list<const char*>,
  mp_list<oalplus::device_handle, string_view>> : get_data_map<1, 2> {};

} // namespace eagine::c_api

