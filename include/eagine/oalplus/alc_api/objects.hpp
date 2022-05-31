/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_ALC_API_OBJECTS_HPP
#define EAGINE_OALPLUS_ALC_API_OBJECTS_HPP

#include "config.hpp"
#include <eagine/c_api/object.hpp>
#include <eagine/c_api/parameter_map.hpp>
#include <eagine/message_id.hpp>

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Tag type denoting ALC device object.
/// @ingroup al_api_wrap
/// @see device_handle
using device_tag = EAGINE_MSG_TYPE(alc, Device);

/// @brief Tag type denoting ALC context object.
/// @ingroup al_api_wrap
/// @see context_handle
using context_tag = EAGINE_MSG_TYPE(alc, Context);

//------------------------------------------------------------------------------
/// @brief Alias for ALC device handle wrapper.
/// @ingroup al_api_wrap
using device_handle = c_api::basic_handle<
  device_tag,
  alc_types::device_type*,
  static_cast<alc_types::device_type*>(nullptr)>;

/// @brief Alias for ALC context handle wrapper.
/// @ingroup al_api_wrap
using context_handle = c_api::basic_handle<
  context_tag,
  alc_types::context_type*,
  static_cast<alc_types::context_type*>(nullptr)>;
//------------------------------------------------------------------------------
/// @brief Alias for owned ALC device handle wrapper.
/// @ingroup al_api_wrap
/// @see device_handle
using owned_device_handle = c_api::basic_owned_handle<
  device_tag,
  alc_types::device_type*,
  static_cast<alc_types::device_type*>(nullptr)>;

/// @brief Alias for owned ALC context handle wrapper.
/// @ingroup al_api_wrap
/// @see context_handle
using owned_context_handle = c_api::basic_owned_handle<
  context_tag,
  alc_types::context_type*,
  static_cast<alc_types::context_type*>(nullptr)>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

namespace eagine::c_api {

template <typename CH, typename... CT, typename... CppT>
    requires(!std::is_same_v<CH, oalplus::alc_types::device_type*>)
struct make_args_map<
  1,
  1,
  mp_list<CH, CT...>,
  mp_list<oalplus::device_handle, CppT...>>
  : make_args_map<1, 2, mp_list<CH, CT...>, mp_list<CppT...>> {};

template <>
struct make_args_map<
  1,
  1,
  mp_list<const char*>,
  mp_list<oalplus::device_handle, string_view>> : get_data_map<1, 2> {};

} // namespace eagine::c_api

#endif
