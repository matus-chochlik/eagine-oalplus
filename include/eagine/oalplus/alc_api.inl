/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

// clang-format off
#include <eagine/oalplus/alc_api/api_traits.inl>
#include <eagine/oalplus/alc_api/constants.inl>
#include <eagine/oalplus/alc_api/c_api.inl>
// clang-format on

namespace eagine::oalplus {

template class basic_alc_constants<alc_api_traits>;
template class basic_alc_operations<alc_api_traits>;
template class basic_alc_c_api<alc_api_traits>;
template class basic_alc_api<alc_api_traits>;

} // namespace eagine::oalplus
