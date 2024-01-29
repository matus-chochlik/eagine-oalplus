/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/alut.h>)
#include <AL/alut.h>
#define EAGINE_HAS_ALUT 1
#else
#define EAGINE_HAS_ALUT 0
#endif

export module eagine.oalplus.alut:config;
import std;
import eagine.core.types;
import eagine.oalplus.al;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Collection of aliases for ALUT types.
/// @ingroup al_api_wrap
export struct alut_types {

    /// @brief Boolean type.
    using bool_type = al_types::bool_type;

    /// @brief String character type.
    using char_type = al_types::char_type;

    /// @brief Enum type.
    using enum_type = al_types::enum_type;

    /// @brief Integer type.
    using int_type = al_types::int_type;

    /// @brief Unsigned integer type.
    using uint_type = al_types::uint_type;

    /// @brief AL object handle type.
    using name_type = al_types::name_type;

    /// @brief Integer type used to store sizes and counts.
    using size_type = al_types::size_type;

    /// @brief Floating-point type.
    using float_type = al_types::float_type;

    /// @brief Untyped pointer type.
    using void_ptr_type = al_types::void_ptr_type;

    /// @brief Untyped const pointer type.
    using const_void_ptr_type = al_types::const_void_ptr_type;
#if EAGINE_HAS_ALUT
    static constexpr bool has_api = true;
#else
    static constexpr bool has_api = false;
#endif

    static constexpr auto bool_true(bool_type b) noexcept -> bool {
#if EAGINE_HAS_ALUT
        return b == AL_TRUE;
#else
        return b;
#endif
    }

    static constexpr auto error_code_no_error(
      [[maybe_unused]] enum_type ec) noexcept -> bool {
#if EAGINE_HAS_ALUT
        return ec == ALUT_ERROR_NO_ERROR;
#else
        return false;
#endif
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

