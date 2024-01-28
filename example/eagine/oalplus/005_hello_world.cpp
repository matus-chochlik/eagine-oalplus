/// @example oalplus/005_hello_world.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.oalplus;
import std;

auto main(int argc, char** argv) -> int {
    using namespace eagine;
    using namespace eagine::oalplus;

    alc_api alc;

    if(ok device{alc.open_device()}) {
        const auto cleanup_dev{alc.close_device.raii(device)};

        const auto context_attribs = (alc.mono_sources | 1) +
                                     (alc.stereo_sources | 1) +
                                     (alc.sync | false);

        if(ok context{alc.create_context(device, context_attribs)}) {
            const auto cleanup_ctx{
              alc.destroy_context.raii(device, context.get())};

            alc.make_context_current(context);
            const auto reset_ctx = alc.make_context_current.raii();

            const al_api al;
            const alut_api alut;

            if(alut.init(&argc, argv)) {
                const auto do_exit{alut.exit.raii()};
                if(ok opt_src{al.gen_sources()}) {
                    const auto del_src{al.delete_sources.raii(opt_src)};
                    if(ok opt_buf{alut.create_buffer_hello_world()}) {
                        source_name src{opt_src};
                        buffer_name buf{opt_buf};
                        const auto del_buf{al.delete_buffers.raii(opt_buf)};

                        al.listener_i(al.position, 0, 0, 0);
                        al.listener_i(al.velocity, 0, 0, 0);
                        al.listener_f(al.gain, 5.F);

                        al.source_f(src, al.position, 0.F, 0.F, 1.F);
                        al.source_f(src, al.velocity, 0.F, 0.F, 0.F);

                        al.source_queue_buffers(src, buf);
                        al.source_play(src);
                        std::this_thread::sleep_for(std::chrono::seconds(2));

                        al.source_unqueue_buffers(src, buf);
                    }
                }
            }
        }
    }

    return 0;
}
