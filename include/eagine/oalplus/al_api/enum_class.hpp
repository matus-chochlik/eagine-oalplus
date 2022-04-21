/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_AL_API_ENUM_CLASS_HPP
#define EAGINE_OALPLUS_AL_API_ENUM_CLASS_HPP

#include "config.hpp"
#include <eagine/c_api/enum_class.hpp>
#include <eagine/identifier.hpp>

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Typed wrapper class for AL enum constants/values.
/// @ingroup al_api_wrap
/// @see alc_enum_class
/// @see alut_enum_class
///
/// This wrapper uses the specified Id to group various AL constants logically
/// belonging together and prevents accidental mismatches and use of AL constants
/// from unrelated groups. For example using a source attribute constant in place
/// of listener attribute constants. Such mismatches result in compilation errors.
template <typename Self, identifier_t Id>
using al_enum_class =
  c_api::enum_class<Self, al_types::enum_type, EAGINE_ID_V(AL), Id>;

/// @brief Type erasure alias for AL enum classes.
/// @ingroup al_api_wrap
using al_any_enum_class = c_api::any_enum_class<EAGINE_ID_V(AL)>;

/// @brief Type erasure alias for AL enum values.
/// @ingroup al_api_wrap
using al_any_enum_value = c_api::any_enum_value<EAGINE_ID_V(AL)>;

static constexpr auto same_enum_class(
  const al_any_enum_class a,
  const al_any_enum_class b) noexcept -> bool {
    return ::eagine::c_api::same_enum_class(a, b);
}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#endif // EAGINE_OALPLUS_AL_API_ENUM_CLASS_HPP
