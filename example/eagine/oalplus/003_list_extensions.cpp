/// @example oalplus/002_list_extensions.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oalplus/al.hpp>
#include <eagine/oalplus/alc_api.hpp>
#include <iostream>

auto main() -> int {
    using namespace eagine;
    using namespace eagine::oalplus;

    const alc_api alc;

    if(alc.get_string) {
        if(const ok name{alc.get_default_device_specifier()}) {
            std::cout << "Default device: " << name.get() << std::endl;
        }
    }

    if(alc.open_device && alc.close_device) {
        if(const ok device{alc.open_device()}) {
            // closes the device when going out of scope
            const auto cleanup_dev = alc.close_device.raii(device);

            if(const ok extensions{alc.get_extensions(device)}) {
                for(const auto name : extensions) {
                    std::cout << "  " << name << std::endl;
                }
            } else {
                std::cerr << "failed to get extension list: "
                          << (!extensions).message() << std::endl;
            }
        } else {
            std::cout << "missing required API function." << std::endl;
        }
    }
    return 0;
}
