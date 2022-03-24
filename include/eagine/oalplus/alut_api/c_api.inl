/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

namespace eagine::oalplus {
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_alut_c_api<ApiTraits>::basic_alut_c_api(api_traits& traits)
  : _traits{traits}
  , GetError{"GetError", *this}
  , GetErrorString{"GetErrorString", *this}
  , Init{"Init", *this}
  , InitWithoutContext{"InitWithoutContext", *this}
  , CreateBufferFromFile{"CreateBufferFromFile", *this}
  , CreateBufferFromFileImage{"CreateBufferFromFileImage", *this}
  , CreateBufferHelloWorld{"CreateBufferHelloWorld", *this}
  , CreateBufferWaveform{"CreateBufferWaveform", *this}
  , Exit{"Exit", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
