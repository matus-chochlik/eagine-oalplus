/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oalplus.al:enum_types;
import eagine.core.types;
import eagine.core.identifier;
import eagine.core.c_api;
import :config;

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
export template <typename Self, identifier_value Id>
using al_enum_class = c_api::enum_class<Self, al_types::enum_type, "AL", Id>;

/// @brief Type erasure alias for AL enum classes.
/// @ingroup al_api_wrap
export using al_any_enum_class = c_api::any_enum_class<"AL">;

/// @brief Type erasure alias for AL enum values.
/// @ingroup al_api_wrap
export using al_any_enum_value = c_api::any_enum_value<"AL">;

export constexpr auto same_enum_class(
  const al_any_enum_class a,
  const al_any_enum_class b) noexcept -> bool {
    return ::eagine::c_api::same_enum_class(a, b);
}
//------------------------------------------------------------------------------
/// @brief Typed enumeration for AL error code constants.
/// @ingroup al_api_wrap
export struct al_error_code : al_enum_class<al_error_code, "ErrorCode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL capability constants.
/// @ingroup al_api_wrap
export struct al_capability : al_enum_class<al_capability, "Capability"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL boolean query constants.
/// @ingroup al_api_wrap
export struct al_boolean_query : al_enum_class<al_boolean_query, "BoolQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL integer query constants.
/// @ingroup al_api_wrap
export struct al_integer_query : al_enum_class<al_integer_query, "IntQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL numeric query constants.
/// @ingroup al_api_wrap
export struct al_numeric_query : al_enum_class<al_numeric_query, "NumQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL string query constants.
/// @ingroup al_api_wrap
export struct al_string_query : al_enum_class<al_string_query, "StrQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL distance model constants.
/// @ingroup al_api_wrap
export struct distance_model : al_enum_class<distance_model, "DistModel"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL listener attribute constants.
/// @ingroup al_api_wrap
export struct listener_attribute
  : al_enum_class<listener_attribute, "ListenAttr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL buffer attribute constants.
/// @ingroup al_api_wrap
export struct buffer_attribute : al_enum_class<buffer_attribute, "BufferAttr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL buffer format constants.
/// @ingroup al_api_wrap
export struct buffer_format : al_enum_class<buffer_format, "BufferFrmt"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL source attribute constants.
/// @ingroup al_api_wrap
export struct source_attribute : al_enum_class<source_attribute, "SourceAttr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL source state constants.
/// @ingroup al_api_wrap
export struct source_state : al_enum_class<source_state, "SourceStte"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for AL source type constants.
/// @ingroup al_api_wrap
export struct source_type : al_enum_class<source_type, "SourceType"> {
    using enum_class::enum_class;
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

