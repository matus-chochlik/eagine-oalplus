/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
export module eagine.oalplus.al:math;
import eagine.core.types;
import eagine.core.math;
import :config;

namespace eagine::oalplus {

//------------------------------------------------------------------------------
/// @brief Alias for math::sign.
/// @ingroup al_utils
export using sign = math::sign<al_types::float_type>;
//------------------------------------------------------------------------------
/// @brief Alias for math::vector.
/// @ingroup al_utils
export using math::vector;

/// @brief Alias for a floating-point 2D vector type.
/// @ingroup al_utils
export using vec2 = vector<al_types::float_type, 2, true>;

/// @brief Alias for a floating-point 3D vector type.
/// @ingroup al_utils
export using vec3 = vector<al_types::float_type, 3, true>;

/// @brief Alias for a floating-point 4D vector type.
/// @ingroup al_utils
export using vec4 = vector<al_types::float_type, 4, true>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

