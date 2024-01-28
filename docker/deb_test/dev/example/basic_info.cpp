/// @example oalplus/basic_info.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oalplus/al.hpp>
#include <eagine/oalplus/alc_api.hpp>
#include <iostream>

auto main() -> int {
    using namespace eagine;
    using namespace eagine::oalplus;

    const alc_api alc;

    std::cout << "Default playback device: "
              << alc.get_default_device_specifier().value_or("N/A")
              << std::endl;

    std::cout << "Default capture device: "
              << alc.get_capture_default_device_specifier().value_or("N/A")
              << std::endl;

    std::cout << "ALC version: "
              << alc.get_integer(alc.major_version).value_or(0) << "."
              << alc.get_integer(alc.minor_version).value_or(0) << std::endl;

    return 0;
}
