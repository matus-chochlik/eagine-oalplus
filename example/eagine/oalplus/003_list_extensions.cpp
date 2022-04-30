/// @example oalplus/002_list_extensions.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/main.hpp>
#include <eagine/main_ctx_object.hpp>
#include <eagine/oalplus/al.hpp>
#include <eagine/oalplus/alc_api.hpp>

namespace eagine {

auto main(main_ctx& ctx) -> int {
    using namespace eagine::oalplus;

    const alc_api alc;
    const main_ctx_object out{EAGINE_ID(OALplus), ctx};

    if(alc.get_string) {
        if(const ok name{alc.get_default_device_specifier()}) {
            out.cio_print("Default device: ${name}").arg(EAGINE_ID(name), name);
        }
    }

    if(alc.open_device && alc.close_device) {
        if(const ok device{alc.open_device()}) {
            // closes the device when going out of scope
            const auto cleanup_dev = alc.close_device.raii(device);

            const auto ext_cio{out.cio_print("Extensions:").to_be_continued()};

            if(const ok extensions{alc.get_extensions(device)}) {
                for(const auto name : extensions) {
                    ext_cio.print(name);
                }
            } else {
                ext_cio
                  .print(
                    console_entry_kind::error,
                    "failed to get extension list: ${message}")
                  .arg(EAGINE_ID(message), (!extensions).message());
            }
        } else {
            out.cio_error("missing required API function");
        }
    }
    return 0;
}

} // namespace eagine
