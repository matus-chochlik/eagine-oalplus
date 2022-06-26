/// @example oalplus/003_list_devices.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/main_ctx.hpp>
#include <eagine/main_ctx_object.hpp>
#include <eagine/oalplus/al.hpp>
#include <eagine/oalplus/alc_api.hpp>

namespace eagine {

auto main(main_ctx& ctx) -> int {
    using namespace eagine::oalplus;

    const alc_api alc;
    const main_ctx_object out{EAGINE_ID(OALplus), ctx};

    if(alc.get_string) {
        const auto dev_cio{
          out.cio_print("Playback devices:").to_be_continued()};
        if(const ok names{alc.get_device_specifiers()}) {
            for(const auto name : names) {
                dev_cio.print(name);
            }
        } else {
            dev_cio.error("failed to list playback devices: ${message}")
              .arg(EAGINE_ID(message), (!names).message());
        }
    } else {
        out.cio_error("missing required API function: ${name}")
          .arg(EAGINE_ID(name), alc.get_string.underlying().name());
    }

    if(alc.get_string) {
        const auto dev_cio{out.cio_print("Capture devices:").to_be_continued()};
        if(const ok names{alc.get_capture_device_specifiers()}) {
            for(const auto name : names) {
                dev_cio.print(name);
            }
        } else {
            dev_cio.error("failed to list capture devices: ${message}")
              .arg(EAGINE_ID(message), (!names).message());
        }
    } else {
        out.cio_error("missing required API function: ${name}")
          .arg(EAGINE_ID(name), alc.get_string.underlying().name());
    }

    return 0;
}

} // namespace eagine

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

