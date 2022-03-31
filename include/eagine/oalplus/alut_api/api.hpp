/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_ALUT_API_API_HPP
#define EAGINE_OALPLUS_ALUT_API_API_HPP

#include "../al_api/object_name.hpp"
#include "c_api.hpp"
#include "enum_types.hpp"
#include <eagine/c_api/adapted_function.hpp>
#include <eagine/scope_exit.hpp>
#include <eagine/string_list.hpp>

namespace eagine::oalplus {
using c_api::adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the ALUT API.
/// @ingroup al_api_wrap
/// @see basic_alut_constants
/// @see basic_alut_c_api
template <typename ApiTraits>
class basic_alut_operations : public basic_alut_c_api<ApiTraits> {

public:
    using api_traits = ApiTraits;
    using alut_api = basic_alut_c_api<ApiTraits>;

    using enum_type = typename alut_types::enum_type;
    using char_type = typename alut_types::char_type;

    adapted_function<&alut_api::Init> init{*this};

    adapted_function<&alut_api::CreateBufferHelloWorld, owned_buffer_name()>
      create_buffer_hello_world{*this};

    adapted_function<&alut_api::Exit> exit{*this};

    basic_alut_operations(api_traits& traits)
      : alut_api{traits} {}
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#endif // EAGINE_OALPLUS_ALUT_API_API_HPP
