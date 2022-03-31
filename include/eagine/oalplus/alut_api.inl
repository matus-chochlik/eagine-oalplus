/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

// clang-format off
#include <eagine/oalplus/alut_api/api_traits.inl>
#include <eagine/oalplus/alut_api/constants.inl>
#include <eagine/oalplus/alut_api/c_api.inl>
// clang-format on

namespace eagine::oalplus {

template class basic_alut_constants<alut_api_traits>;
template class basic_alut_operations<alut_api_traits>;
template class basic_alut_c_api<alut_api_traits>;
template class basic_alut_api<alut_api_traits>;

} // namespace eagine::oalplus
