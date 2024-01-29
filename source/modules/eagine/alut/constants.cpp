/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/alut.h>)
#include <AL/alut.h>
#define EAGINE_HAS_ALUT 1
#else
#define EAGINE_HAS_ALUT 0
#endif

export module eagine.oalplus.alut:constants;
import std;
import eagine.core.types;
import eagine.core.c_api;
import :config;
import :enum_types;
import :c_api;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Class wrapping the constants from the ALUT API.
/// @ingroup al_api_wrap
/// @see basic_alut_c_api
/// @see basic_alut_operations
export template <typename ApiTraits>
class basic_alut_constants {
public:
    template <typename ClassList, typename Constant, typename Tag = nothing_t>
    using opt_constant = c_api::opt_constant<ClassList, Constant, Tag>;

    using enum_type = typename alut_types::enum_type;
    using enum_type_i = std::type_identity<enum_type>;
    template <enum_type value>
    using enum_type_c = std::integral_constant<enum_type, value>;

    /// @var no_error
    /// @alutconstwrap{NO_ERROR}
    opt_constant<
      mp_list<alut_error_code>,
#ifdef ALUT_ERROR_NO_ERROR
      enum_type_c<ALUT_ERROR_NO_ERROR>>
#else
      enum_type_i>
#endif
      no_error;

    /// @var waveform_sine
    /// @alutconstwrap{WAVEFORM_SINE}
    opt_constant<
      mp_list<waveform_function>,
#ifdef ALUT_WAVEFORM_SINE
      enum_type_c<ALUT_WAVEFORM_SINE>>
#else
      enum_type_i>
#endif
      waveform_sine;

    /// @var waveform_square
    /// @alutconstwrap{WAVEFORM_SQUARE}
    opt_constant<
      mp_list<waveform_function>,
#ifdef ALUT_WAVEFORM_SQUARE
      enum_type_c<ALUT_WAVEFORM_SQUARE>>
#else
      enum_type_i>
#endif
      waveform_square;

    /// @var waveform_sawtooth
    /// @alutconstwrap{WAVEFORM_SAWTOOTH}
    opt_constant<
      mp_list<waveform_function>,
#ifdef ALUT_WAVEFORM_SAWTOOTH
      enum_type_c<ALUT_WAVEFORM_SAWTOOTH>>
#else
      enum_type_i>
#endif
      waveform_sawtooth;

    /// @var waveform_whitenoise
    /// @alutconstwrap{WAVEFORM_WHITENOISE}
    opt_constant<
      mp_list<waveform_function>,
#ifdef ALUT_WAVEFORM_WHITENOISE
      enum_type_c<ALUT_WAVEFORM_WHITENOISE>>
#else
      enum_type_i>
#endif
      waveform_whitenoise;

    /// @var waveform_impulse
    /// @alutconstwrap{WAVEFORM_IMPULSE}
    opt_constant<
      mp_list<waveform_function>,
#ifdef ALUT_WAVEFORM_IMPULSE
      enum_type_c<ALUT_WAVEFORM_IMPULSE>>
#else
      enum_type_i>
#endif
      waveform_impulse;

    basic_alut_constants(ApiTraits& traits, basic_alut_c_api<ApiTraits>& api);
};
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_alut_constants<ApiTraits>::basic_alut_constants(
  ApiTraits& traits,
  basic_alut_c_api<ApiTraits>& api)
  : no_error("ERROR_NO_ERROR", traits, api)
  , waveform_sine("WAVEFORM_SINE", traits, api)
  , waveform_square("WAVEFORM_SQUARE", traits, api)
  , waveform_sawtooth("WAVEFORM_SAWTOOTH", traits, api)
  , waveform_whitenoise("WAVEFORM_WHITENOISE", traits, api)
  , waveform_impulse("WAVEFORM_IMPULSE", traits, api) {}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

