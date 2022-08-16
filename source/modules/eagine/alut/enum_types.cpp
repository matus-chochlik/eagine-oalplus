/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oalplus.alut:enum_types;
import eagine.core.types;
import eagine.core.identifier;
import eagine.core.c_api;
import :config;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Typed wrapper class for ALUT enum constants/values.
/// @ingroup al_api_wrap
/// @see al_enum_class
/// @see alc_enum_class
///
/// This wrapper uses the specified Id to group various ALUT constants logically
/// belonging together and prevents accidental mismatches and use of ALUT
/// constants from unrelated groups.
export template <typename Self, identifier_value Id>
using alut_enum_class =
  c_api::enum_class<Self, alut_types::enum_type, "ALUT", Id>;

/// @brief Type erasure alias for ALUT enum classes.
/// @ingroup al_api_wrap
export using alut_any_enum_class = c_api::any_enum_class<"ALUT">;

/// @brief Type erasure alias for ALUT enum values.
/// @ingroup al_api_wrap
export using alut_any_enum_value = c_api::any_enum_value<"ALUT">;

export constexpr auto same_enum_class(
  const alut_any_enum_class a,
  const alut_any_enum_class b) noexcept -> bool {
    return ::eagine::c_api::same_enum_class(a, b);
}
//------------------------------------------------------------------------------
/// @brief Typed enumeration for ALUT error code constants.
/// @ingroup al_api_wrap
/// @see al_error_code
/// @see alc_error_code
export struct alut_error_code : alut_enum_class<alut_error_code, "ErrorCode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for ALUT waveform function constants.
/// @ingroup al_api_wrap
export struct waveform_function
  : alut_enum_class<waveform_function, "WvefrmFunc"> {
    using enum_class::enum_class;
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

