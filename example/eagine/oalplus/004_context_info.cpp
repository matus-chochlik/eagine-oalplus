/// @example oalplus/004_context.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/oalplus/al.hpp>
#include <eagine/oalplus/al_api.hpp>
#include <eagine/oalplus/alc_api.hpp>
#include <iostream>

auto main() -> int {
    using namespace eagine;
    using namespace eagine::oalplus;

    const alc_api alc;

    if(const auto device{alc.open_device.object()}) {
        if(const auto context{alc.create_context.object(device, {})}) {
            alc.make_context_current(device, context);

            const al_api al;

            if(const ok info{al.get_string(al.vendor)}) {
                std::cout << "Vendor: " << extract(info) << std::endl;
            }

            if(const ok info{al.get_string(al.renderer)}) {
                std::cout << "Renderer: " << extract(info) << std::endl;
            }

            if(const ok info{al.get_string(al.version)}) {
                std::cout << "Version: " << extract(info) << std::endl;
            }
        }
    }

    return 0;
}
