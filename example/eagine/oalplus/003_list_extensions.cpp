/// @example oalplus/003_list_extensions.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.oalplus;
import std;

namespace eagine {

auto main(main_ctx& ctx) -> int {
    using namespace eagine::oalplus;

    const alc_api alc;
    const main_ctx_object out{"OALplus", ctx};

    if(alc.get_string) {
        if(const ok name{alc.get_default_device_specifier()}) {
            out.cio_print("Default device: ${name}").arg("name", name);
        }
    }

    if(alc.open_device and alc.close_device) {
        if(const auto device{alc.open_device.object()}) {

            const auto ext_cio{out.cio_print("Extensions:").to_be_continued()};

            for(const auto name : alc.get_extensions(device)) {
                ext_cio.print(name);
            }
        }
    } else {
        out.cio_error("missing required API function");
    }
    return 0;
}

} // namespace eagine

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

