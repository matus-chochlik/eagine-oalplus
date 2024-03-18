/// @example oalplus/004_context.cpp
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

    const alc_api alc{ctx};

    if(const auto device{alc.open_device_object()}) {
        if(const auto context{alc.create_context_object(device, {})}) {
            alc.make_context_current(device, context);

            const al_api al{ctx};

            if(const ok info{al.get_string(al.vendor)}) {
                std::cout << "Vendor: " << info << std::endl;
            }

            if(const ok info{al.get_string(al.renderer)}) {
                std::cout << "Renderer: " << info << std::endl;
            }

            if(const ok info{al.get_string(al.version)}) {
                std::cout << "Version: " << info << std::endl;
            }
        }
    }

    return 0;
}

} // namespace eagine

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}
