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
#include <eagine/c_api/handle.hpp>
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
/// @ingroup egl_api_wrap
using device_handle = c_api::basic_handle<
  device_tag,
  alc_types::device_type*,
  static_cast<alc_types::device_type*>(nullptr)>;
//------------------------------------------------------------------------------
/// @brief Alias for ALC context handle wrapper.
/// @ingroup egl_api_wrap
using context_handle = c_api::basic_handle<
  context_tag,
  alc_types::context_type*,
  static_cast<alc_types::context_type*>(nullptr)>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#endif
