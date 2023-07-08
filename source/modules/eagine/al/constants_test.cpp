/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/testing/unit_begin.hpp>
import std;
import eagine.core;
import eagine.oalplus.al;
//------------------------------------------------------------------------------
void constants_enum_by_name(auto& s) {
    eagitest::case_ test{s, 1, "AL enum by name"};
    std::set<eagine::oalplus::al_types::enum_type> distinct;

    const auto check{[&](eagine::string_view name) {
        if(auto value{eagine::oalplus::al_enum_by_name(name)}) {
            distinct.insert(*value);
        } else {
            test.fail(name);
        }
    }};
    check("inverse_distance");
    check("inverse_distance_clamped");
    check("linear_distance");
    check("linear_distance_clamped");
    check("exponent_distance");
    check("exponent_distance_clamped");

    test.check_equal(distinct.size(), 6U, "constant count");
}
//------------------------------------------------------------------------------
auto main(int argc, const char** argv) -> int {
    eagitest::suite test{argc, argv, "constants", 1};
    test.once(constants_enum_by_name);
    return test.exit_code();
}
//------------------------------------------------------------------------------
#include <eagine/testing/unit_end.hpp>
