/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/alut.h>)
#include <AL/alut.h>
#define EAGINE_HAS_ALUT 1
#else
#define EAGINE_HAS_ALUT 0
#endif

export module eagine.oalplus.alut:api;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import eagine.oalplus.al;
import :config;
import :enum_types;
import :result;
import :c_api;
import :constants;

namespace eagine::oalplus {
using c_api::plain_adapted_function;
using c_api::simple_adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the ALUT API.
/// @ingroup al_api_wrap
/// @see basic_alut_constants
/// @see basic_alut_c_api
export template <typename ApiTraits>
class basic_alut_operations : public basic_alut_c_api<ApiTraits> {

public:
    using api_traits = ApiTraits;
    using alut_api = basic_alut_c_api<ApiTraits>;

    using enum_type = typename alut_types::enum_type;
    using char_type = typename alut_types::char_type;

    plain_adapted_function<&alut_api::Init> init{*this};

    simple_adapted_function<
      &alut_api::CreateBufferHelloWorld,
      owned_buffer_name()>
      create_buffer_hello_world{*this};

    plain_adapted_function<&alut_api::Exit> exit{*this};

    basic_alut_operations(api_traits& traits)
      : alut_api{traits} {}
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

