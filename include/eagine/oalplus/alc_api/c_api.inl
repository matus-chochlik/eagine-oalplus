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
basic_alc_c_api<ApiTraits>::basic_alc_c_api(api_traits& traits)
  : _traits{traits}
  , GetError{"GetError", *this}
  , GetProcAddress{"GetProcAddress", *this}
  , GetEnumValue{"GetEnumValue", *this}
  , OpenDevice{"OpenDevice", *this}
  , CaptureOpenDevice{"CaptureOpenDevice", *this}
  , CloseDevice{"CloseDevice", *this}
  , CaptureCloseDevice{"CaptureCloseDevice", *this}
  , GetString{"GetString", *this}
  , GetIntegerv{"GetIntegerv", *this}
  , IsExtensionPresent{"IsExtensionPresent", *this}
  , CreateContext{"CreateContext", *this}
  , ProcessContext{"ProcessContext", *this}
  , SuspendContext{"SuspendContext", *this}
  , DestroyContext{"DestroyContext", *this}
  , MakeContextCurrent{"MakeContextCurrent", *this}
  , GetCurrentContext{"GetCurrentContext", *this}
  , GetContextsDevice{"GetContextsDevice", *this}
  , CaptureStart{"CaptureStart", *this}
  , CaptureStop{"CaptureStop", *this}
  , CaptureSamples{"CaptureSamples", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
