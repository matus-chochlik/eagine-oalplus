/// @example oalplus/001_basic_info.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.oalplus;
import std;

namespace eagine {

auto main(main_ctx& ctx) -> int {
    using namespace eagine::oalplus;

    const alc_api alc;
    const main_ctx_object out{"OALplus", ctx};

    out.cio_print("Default playback device: ${device}")
      .arg("device", alc.get_default_device_specifier().value_or("N/A"));

    out.cio_print("Default capture device: ${device}")
      .arg(
        "device", alc.get_capture_default_device_specifier().value_or("N/A"));

    out.cio_print("ALC version: ${major}.${minor}")
      .arg("major", alc.get_integer(alc.major_version).value_or(0))
      .arg("minor", alc.get_integer(alc.minor_version).value_or(0));

    return 0;
}

} // namespace eagine

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

