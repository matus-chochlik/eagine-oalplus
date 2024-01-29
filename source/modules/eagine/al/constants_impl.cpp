/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/al.h>)
#include <AL/al.h>
#define EAGINE_HAS_AL 1
#else
#define EAGINE_HAS_AL 0
#endif

module eagine.oalplus.al;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.container;
import eagine.core.valid_if;

namespace eagine {
//------------------------------------------------------------------------------
auto within_limits<oalplus::distance_model, oalplus::al_types::enum_type>::check(
  oalplus::al_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_AL
        case AL_INVERSE_DISTANCE:
        case AL_INVERSE_DISTANCE_CLAMPED:
        case AL_LINEAR_DISTANCE:
        case AL_LINEAR_DISTANCE_CLAMPED:
        case AL_EXPONENT_DISTANCE:
        case AL_EXPONENT_DISTANCE_CLAMPED:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
namespace oalplus {
//------------------------------------------------------------------------------
auto map_al_enum_by_name() noexcept {
    return basic_lc_identifier_trie<al_types::enum_type>()
#if EAGINE_HAS_AL
      .add("inverse_distance", AL_INVERSE_DISTANCE)
      .add("inverse_distance_clamped", AL_INVERSE_DISTANCE_CLAMPED)
      .add("linear_distance", AL_LINEAR_DISTANCE)
      .add("linear_distance_clamped", AL_LINEAR_DISTANCE_CLAMPED)
      .add("exponent_distance", AL_EXPONENT_DISTANCE)
      .add("exponent_distance_clamped", AL_EXPONENT_DISTANCE_CLAMPED)
#endif
      ;
}
//------------------------------------------------------------------------------
auto al_enum_by_name(const string_view name) noexcept
  -> optionally_valid<al_types::enum_type> {
    if(not name.empty()) [[likely]] {
        static const auto enums{map_al_enum_by_name()};
        if(auto found{enums.find(name)}) [[likely]] {
            return {*found, true};
        }
    }
    return {};
}
//------------------------------------------------------------------------------
} // namespace oalplus
} // namespace eagine
