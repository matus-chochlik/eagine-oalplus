/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/al.h>)
#include <AL/al.h>
#define EAGINE_HAS_AL 1
#else
#define EAGINE_HAS_AL 0
#endif

export module eagine.oalplus.al:result;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Class storing information about call result for unavailable AL functions.
/// @ingroup al_api_wrap
/// @see al_no_result
/// @see al_result_info
export class al_no_result_info {
public:
    constexpr auto error_code(const anything) noexcept -> auto& {
        return *this;
    }

    /// @brief Returns a message associated with the result.
    constexpr auto message() const noexcept -> string_view {
        return {"AL function not available"};
    }

private:
};
//------------------------------------------------------------------------------
/// @brief Class storing information about an AL function call result.
/// @ingroup al_api_wrap
/// @see al_result
/// @see al_no_result_info
export class al_result_info {
public:
    using enum_type = al_types::enum_type;

    /// @brief Indicates if the call finished without error.
    explicit constexpr operator bool() const noexcept {
        return al_types::error_code_no_error(_error_code);
    }

    constexpr auto error_code(const enum_type ec) noexcept -> auto& {
        _error_code = ec;
        return *this;
    }

    /// @brief Returns a message associated with the result.
    auto message() const noexcept -> string_view {
#ifdef AL_INVALID_NAME
        if(_error_code == AL_INVALID_NAME) {
            return {"invalid object name"};
        }
#endif
#ifdef AL_INVALID_ENUM
        if(_error_code == AL_INVALID_ENUM) {
            return {"invalid enumeration value"};
        }
#endif
#ifdef AL_INVALID_VALUE
        if(_error_code == AL_INVALID_VALUE) {
            return {"invalid parameter value"};
        }
#endif
#ifdef AL_INVALID_OPERATION
        if(_error_code == AL_INVALID_OPERATION) {
            return {"invalid operation"};
        }
#endif
#ifdef AL_NO_ERROR
        if(_error_code == AL_NO_ERROR) {
            return {"no error"};
        }
#endif
#ifdef AL_OUT_OF_MEMORY
        if(_error_code == AL_OUT_OF_MEMORY) {
            return {"out of memory"};
        }
#endif
        return {"unknown error"};
    }

private:
    enum_type _error_code{
#ifdef AL_NO_ERROR
      AL_NO_ERROR
#endif
    };
};
//------------------------------------------------------------------------------
/// @brief Alias for always-invalid result of a missing AL API function call.
/// @ingroup al_api_wrap
/// @see al_result
/// @see al_opt_result
export template <typename Result>
using al_no_result = c_api::no_result<Result, al_no_result_info>;
//------------------------------------------------------------------------------
/// @brief Class wrapping the result of an AL API function call.
/// @ingroup al_api_wrap
/// @see al_no_result
/// @see al_opt_result
export template <typename Result>
using al_result = c_api::result<Result, al_result_info>;
//------------------------------------------------------------------------------
/// @brief Alias for conditionally-valid result of an AL API function call.
/// @ingroup al_api_wrap
/// @see al_result
/// @see al_opt_result
export template <typename Result>
using al_opt_result = c_api::opt_result<Result, al_result_info>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

