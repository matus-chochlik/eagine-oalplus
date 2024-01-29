/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/alc.h>)
#include <AL/alc.h>
#define EAGINE_HAS_ALC 1
#else
#define EAGINE_HAS_ALC 0
#endif

export module eagine.oalplus.alc:attributes;
import eagine.core.types;
import eagine.core.c_api;
import :config;
import :enum_types;

namespace eagine::oalplus {

/// @brief Traits for ALC context attribute key/value list traits.
/// @ingroup alc_api_wrap
export struct context_attrib_traits {
    /// @brief Alias for the key type.
    using key_type = context_attribute;
    using conv_type = alc_types::enum_type;
    /// @brief Alias for the value type.
    using value_type = alc_types::int_type;

    static constexpr auto terminator() noexcept -> alc_types::int_type {
        return 0;
    }
};

/// @brief Alias for ALC context attribute key/value list.
/// @ingroup alc_api_wrap
export using context_attributes = c_api::key_value_list<context_attrib_traits>;

/// @brief Alias for ALC context attribute list key/value pair.
/// @ingroup alc_api_wrap
/// @see context_attributes
export using context_attribute_value =
  c_api::key_value_list_element<context_attrib_traits>;

/// @brief Concatenation operator for context attribute list key and value.
/// @ingroup alc_api_wrap
/// @relates config_attributes
export constexpr auto operator|(
  const context_attribute key,
  const alc_types::int_type value) noexcept -> context_attribute_value {
    return {key, value};
}

/// @brief Concatenation operator for context attribute list key and value.
/// @ingroup alc_api_wrap
/// @relates config_attributes
export constexpr auto operator|(
  const context_attribute key,
  const bool value) noexcept -> context_attribute_value {
#if defined(ALC_TRUE) && defined(ALC_FALSE)
    return {key, value ? ALC_TRUE : ALC_FALSE};
#else
    return {key, value ? 1 : 0};
#endif
}

}; // namespace eagine::oalplus
