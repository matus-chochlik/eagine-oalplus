/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oalplus.alc:enum_types;
import eagine.core.types;
import eagine.core.identifier;
import eagine.core.c_api;
import :config;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Typed wrapper class for ALC enum constants/values.
/// @ingroup al_api_wrap
/// @see al_enum_class
/// @see alut_enum_class
///
/// This wrapper uses the specified Id to group various ALC constants logically
/// belonging together and prevents accidental mismatches and use of ALC constants
/// from unrelated groups. For example using a context attribute constant in place
/// of string query constants. Such mismatches result in compilation errors.
export template <typename Self, identifier_value Id>
using alc_enum_class = c_api::enum_class<Self, alc_types::enum_type, "ALC", Id>;

/// @brief Type erasure alias for ALC enum classes.
/// @ingroup al_api_wrap
export using alc_any_enum_class = c_api::any_enum_class<"ALC">;

/// @brief Type erasure alias for ALC enum values.
/// @ingroup al_api_wrap
export using alc_any_enum_value = c_api::any_enum_value<"ALC">;

export constexpr auto same_enum_class(
  const alc_any_enum_class a,
  const alc_any_enum_class b) noexcept -> bool {
    return ::eagine::c_api::same_enum_class(a, b);
}
//------------------------------------------------------------------------------
/// @brief Typed enumeration for ALC error code constants.
/// @ingroup al_api_wrap
/// @see al_error_code
/// @see alut_error_code
export struct alc_error_code : alc_enum_class<alc_error_code, "ErrorCode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for ALC context attribute constants.
/// @ingroup al_api_wrap
export struct context_attribute
  : alc_enum_class<context_attribute, "CntxtAttr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for ALC string query constants.
/// @ingroup al_api_wrap
export struct alc_string_query : alc_enum_class<alc_string_query, "StrQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for ALC integer query constants.
/// @ingroup al_api_wrap
export struct alc_integer_query
  : alc_enum_class<alc_integer_query, "IntQuery"> {
    using enum_class::enum_class;
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

