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

#ifndef ALC_NO_ERROR
#define ALC_NO_ERROR 0
#endif

export module eagine.oalplus.alc:result;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Class storing information about call result for unavailable ALC functions.
/// @ingroup al_api_wrap
/// @see al_no_result
/// @see al_result_info
export class alc_no_result_info {
public:
    constexpr auto error_code(const anything) noexcept -> auto& {
        return *this;
    }

    /// @brief Returns a message associated with the result.
    constexpr auto message() const noexcept -> string_view {
        return {"ALC function not available"};
    }

    constexpr auto set_unknown_error() const noexcept -> auto& {
        return *this;
    }

private:
};
//------------------------------------------------------------------------------
/// @brief Class storing information about an ALC function call result.
/// @ingroup al_api_wrap
/// @see al_result
/// @see al_no_result_info
export class alc_result_info {
public:
    using enum_type = alc_types::enum_type;

    /// @brief Indicates if the call finished without error.
    explicit constexpr operator bool() const noexcept {
        return alc_types::error_code_no_error(_error_code);
    }

    constexpr auto error_code(const enum_type ec) noexcept -> auto& {
        _error_code = ec;
        return *this;
    }

    constexpr auto error_code() const noexcept -> enum_type {
        return _error_code;
    }

    /// @brief Returns a message associated with the result.
    auto message() const noexcept -> string_view {
#ifdef ALC_INVALID_ENUM
        if(_error_code == ALC_INVALID_ENUM) {
            return {"invalid enumeration parameter value"};
        }
#endif
#ifdef ALC_INVALID_VALUE
        if(_error_code == ALC_INVALID_VALUE) {
            return {"invalid parameter value"};
        }
#endif
#ifdef ALC_INVALID_CONTEXT
        if(_error_code == ALC_INVALID_CONTEXT) {
            return {"invalid context"};
        }
#endif
#ifdef ALC_INVALID_DEVICE
        if(_error_code == ALC_INVALID_DEVICE) {
            return {"invalid device"};
        }
#endif
#ifdef ALC_NO_ERROR
        if(_error_code == ALC_NO_ERROR) {
            return {"no error"};
        }
#endif
#ifdef ALC_OUT_OF_MEMORY
        if(_error_code == ALC_OUT_OF_MEMORY) {
            return {"out of memory"};
        }
#endif
        return {"unknown error"};
    }

    constexpr auto set_unknown_error() noexcept -> auto& {
        if(_error_code != ALC_NO_ERROR) {
            _error_code = alc_types::enum_type(~0UL);
        }
        return *this;
    }

private:
    enum_type _error_code{ALC_NO_ERROR};
};
//------------------------------------------------------------------------------
/// @brief Alias for always-invalid result of a missing ALC API function call.
/// @ingroup al_api_wrap
/// @see al_result
/// @see al_opt_result
export template <typename Result>
using alc_no_result = c_api::no_result<Result, alc_no_result_info>;
//------------------------------------------------------------------------------
/// @brief Class wrapping the result of a ALC API function call.
/// @ingroup al_api_wrap
/// @see al_no_result
/// @see al_opt_result
export template <typename Result>
using alc_result = c_api::result<Result, alc_result_info>;
//------------------------------------------------------------------------------
/// @brief Class wrapping the result of a ALC API function call.
/// @ingroup al_api_wrap
/// @see al_no_result
/// @see al_opt_result
export template <typename Result>
using alc_opt_result = c_api::opt_result<Result, alc_result_info>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

