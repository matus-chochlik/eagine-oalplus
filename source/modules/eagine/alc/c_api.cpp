/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/alc.h>)
#include <AL/alc.h>
#define EAGINE_HAS_ALC 1
#else
#define EAGINE_HAS_ALC 0
#endif

export module eagine.oalplus.alc:c_api;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :enum_types;
import :objects;
import :result;

#ifndef OALPLUS_ALC_STATIC_FUNC
#if EAGINE_HAS_ALC
#define OALPLUS_ALC_STATIC_FUNC(NAME) &::alc##NAME
#else
#define OALPLUS_ALC_STATIC_FUNC(NAME) nullptr
#endif
#endif

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Class wrapping the C-functions from the ALC API.
/// @ingroup al_api_wrap
/// @see basic_alc_constants
/// @see basic_alc_operations
export template <typename ApiTraits>
class basic_alc_c_api {
    ApiTraits& _traits;

public:
    using this_api = basic_alc_c_api;

    /// @brief Alias for the API traits policy type passed as template argument.
    using api_traits = ApiTraits;

    static constexpr bool has_api = alc_types::has_api;

    /// @brief Alias for device handle type.
    using device_type = typename alc_types::device_type;

    /// @brief Alias for context handle type.
    using context_type = typename alc_types::context_type;

    /// @brief Alias for enumeration type.
    using enum_type = typename alc_types::enum_type;

    /// @brief Alias for string character type.
    using char_type = typename alc_types::char_type;

    /// @brief Alias for boolean type.
    using bool_type = typename alc_types::bool_type;

    /// @brief Alias for signed integer type.
    using int_type = typename alc_types::int_type;

    /// @brief Alias for unsigned integer type.
    using uint_type = typename alc_types::uint_type;

    /// @brief Alias for integer type used to store sizes and counts.
    using size_type = typename alc_types::size_type;

    /// @brief Untyped non-const pointer type.
    using void_ptr_type = typename alc_types::void_ptr_type;

    template <typename Result, typename... U>
    constexpr auto check_result(Result res, device_handle dev, U&&...)
      const noexcept {
        res.error_code(this->GetError(static_cast<device_type*>(dev)));
        return res;
    }

    template <typename Result, typename Info, c_api::result_validity Validity>
    static constexpr auto collapse(
      c_api::result<Result, Info, Validity>&& r) noexcept {
        return r.collapsed(
          [](alc_types::bool_type value) { return bool(value); },
          [](auto& info) { info.set_unknown_error(); });
    }

    /// @brief Alias for ALC C-API function wrapper template.
    template <
      typename Signature,
      c_api::function_ptr<api_traits, nothing_t, Signature> Function>
    using alc_api_function = c_api::opt_function<
      api_traits,
      nothing_t,
      Signature,
      Function,
      has_api,
      bool(Function)>;

    /// @var GetError
    /// @alcfuncwrap{GetError}
    alc_api_function<enum_type(device_type*), OALPLUS_ALC_STATIC_FUNC(GetError)>
      GetError{"GetError", *this};

    /// @var GetProcAddress
    /// @alcfuncwrap{GetProcAddress}
    alc_api_function<
      void_ptr_type(device_type*, const char_type*),
      OALPLUS_ALC_STATIC_FUNC(GetProcAddress)>
      GetProcAddress{"GetProcAddress", *this};

    /// @var GetEnumValue
    /// @alcfuncwrap{GetEnumValue}
    alc_api_function<
      enum_type(device_type*, const char_type*),
      OALPLUS_ALC_STATIC_FUNC(GetEnumValue)>
      GetEnumValue{"GetEnumValue", *this};

    /// @var OpenDevice
    /// @alcfuncwrap{OpenDevice}
    alc_api_function<
      device_type*(const char_type*),
      OALPLUS_ALC_STATIC_FUNC(OpenDevice)>
      OpenDevice{"OpenDevice", *this};

    /// @var CaptureOpenDevice
    /// @alcfuncwrap{CaptureOpenDevice}
    alc_api_function<
      device_type*(
        const char_type*,
        uint_type freq,
        enum_type format,
        size_type bufsize),
      OALPLUS_ALC_STATIC_FUNC(CaptureOpenDevice)>
      CaptureOpenDevice{"CaptureOpenDevice", *this};

    /// @var CloseDevice
    /// @alcfuncwrap{CloseDevice}
    alc_api_function<
      bool_type(device_type*),
      OALPLUS_ALC_STATIC_FUNC(CloseDevice)>
      CloseDevice{"CloseDevice", *this};

    /// @var CaptureCloseDevice
    /// @alcfuncwrap{CaptureCloseDevice}
    alc_api_function<
      bool_type(device_type*),
      OALPLUS_ALC_STATIC_FUNC(CaptureCloseDevice)>
      CaptureCloseDevice{"CaptureCloseDevice", *this};

    /// @var GetString
    /// @alcfuncwrap{GetString}
    alc_api_function<
      const char_type*(device_type*, enum_type),
      OALPLUS_ALC_STATIC_FUNC(GetString)>
      GetString{"GetString", *this};

    /// @var GetIntegerv
    /// @alcfuncwrap{GetIntegerv}
    alc_api_function<
      void(device_type*, enum_type, size_type, int_type*),
      OALPLUS_ALC_STATIC_FUNC(GetIntegerv)>
      GetIntegerv{"GetIntegerv", *this};

    /// @var IsExtensionPresent
    /// @alcfuncwrap{IsExtensionPresent}
    alc_api_function<
      bool_type(device_type*, const char_type*),
      OALPLUS_ALC_STATIC_FUNC(IsExtensionPresent)>
      IsExtensionPresent{"IsExtensionPresent", *this};

    /// @var CreateContext
    /// @alcfuncwrap{CreateContext}
    alc_api_function<
      context_type*(device_type*, const int_type*),
      OALPLUS_ALC_STATIC_FUNC(CreateContext)>
      CreateContext{"CreateContext", *this};

    /// @var ProcessContext
    /// @alcfuncwrap{ProcessContext}
    alc_api_function<void(context_type*), OALPLUS_ALC_STATIC_FUNC(ProcessContext)>
      ProcessContext{"ProcessContext", *this};

    /// @var SuspendContext
    /// @alcfuncwrap{SuspendContext}
    alc_api_function<void(context_type*), OALPLUS_ALC_STATIC_FUNC(SuspendContext)>
      SuspendContext{"SuspendContext", *this};

    /// @var DestroyContext
    /// @alcfuncwrap{DestroyContext}
    alc_api_function<void(context_type*), OALPLUS_ALC_STATIC_FUNC(DestroyContext)>
      DestroyContext{"DestroyContext", *this};

    /// @var MakeContextCurrent
    /// @alcfuncwrap{MakeContextCurrent}
    alc_api_function<
      bool_type(context_type*),
      OALPLUS_ALC_STATIC_FUNC(MakeContextCurrent)>
      MakeContextCurrent{"MakeContextCurrent", *this};

    /// @var GetCurrentContext
    /// @alcfuncwrap{GetCurrentContext}
    alc_api_function<context_type*(), OALPLUS_ALC_STATIC_FUNC(GetCurrentContext)>
      GetCurrentContext{"GetCurrentContext", *this};

    /// @var GetContextsDevice
    /// @alcfuncwrap{GetContextsDevice}
    alc_api_function<
      device_type*(context_type*),
      OALPLUS_ALC_STATIC_FUNC(GetContextsDevice)>
      GetContextsDevice{"GetContextsDevice", *this};

    /// @var CaptureStart
    /// @alcfuncwrap{CaptureStart}
    alc_api_function<void(device_type*), OALPLUS_ALC_STATIC_FUNC(CaptureStart)>
      CaptureStart{"CaptureStart", *this};

    /// @var CaptureStop
    /// @alcfuncwrap{CaptureStop}
    alc_api_function<void(device_type*), OALPLUS_ALC_STATIC_FUNC(CaptureStop)>
      CaptureStop{"CaptureStop", *this};

    /// @var CaptureSamples
    /// @alcfuncwrap{CaptureSamples}
    alc_api_function<
      void(device_type*, void_ptr_type, size_type),
      OALPLUS_ALC_STATIC_FUNC(CaptureSamples)>
      CaptureSamples{"CaptureSamples", *this};

    basic_alc_c_api(api_traits& traits)
      : _traits{traits} {}

    auto traits() noexcept -> api_traits& {
        return _traits;
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

