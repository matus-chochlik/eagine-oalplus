/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/alc.h>)
#include <AL/alc.h>
#define EAGINE_HAS_ALC 1
#else
#define EAGINE_HAS_ALC 0
#endif

export module eagine.oalplus.alc:constants;
import std;
import eagine.core.types;
import eagine.core.c_api;
import :config;
import :enum_types;
import :c_api;

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Class wrapping the constants from the ALC API.
/// @ingroup al_api_wrap
/// @see basic_alc_c_api
/// @see basic_alc_operations
export template <typename ApiTraits>
class basic_alc_constants {
public:
    template <typename ClassList, typename Constant, typename Tag = nothing_t>
    using opt_constant = c_api::opt_constant<ClassList, Constant, Tag>;

    using enum_type = typename alc_types::enum_type;
    using enum_type_i = std::type_identity<enum_type>;
    template <enum_type value>
    using enum_type_c = std::integral_constant<enum_type, value>;

    /// @var no_error
    /// @alcconstwrap{NO_ERROR}
    opt_constant<
      mp_list<alc_error_code>,
#ifdef ALC_NO_ERROR
      enum_type_c<ALC_NO_ERROR>>
#else
      enum_type_i>
#endif
      no_error;

    /// @var invalid_device
    /// @alcconstwrap{INVALID_DEVICE}
    opt_constant<
      mp_list<alc_error_code>,
#ifdef ALC_INVALID_DEVICE
      enum_type_c<ALC_INVALID_DEVICE>>
#else
      enum_type_i>
#endif
      invalid_device;

    /// @var invalid_context
    /// @alcconstwrap{INVALID_CONTEXT}
    opt_constant<
      mp_list<alc_error_code>,
#ifdef ALC_INVALID_CONTEXT
      enum_type_c<ALC_INVALID_CONTEXT>>
#else
      enum_type_i>
#endif
      invalid_context;

    /// @var invalid_enum
    /// @alcconstwrap{INVALID_ENUM}
    opt_constant<
      mp_list<alc_error_code>,
#ifdef ALC_INVALID_ENUM
      enum_type_c<ALC_INVALID_ENUM>>
#else
      enum_type_i>
#endif
      invalid_enum;

    /// @var invalid_value
    /// @alcconstwrap{INVALID_VALUE}
    opt_constant<
      mp_list<alc_error_code>,
#ifdef ALC_INVALID_VALUE
      enum_type_c<ALC_INVALID_VALUE>>
#else
      enum_type_i>
#endif
      invalid_value;

    /// @var out_of_memory
    /// @alcconstwrap{OUT_OF_MEMORY}
    opt_constant<
      mp_list<alc_error_code>,
#ifdef ALC_OUT_OF_MEMORY
      enum_type_c<ALC_OUT_OF_MEMORY>>
#else
      enum_type_i>
#endif
      out_of_memory;

    /// @var device_specifier
    /// @alcconstwrap{DEVICE_SPECIFIER}
    opt_constant<
      mp_list<alc_string_query>,
#ifdef ALC_DEVICE_SPECIFIER
      enum_type_c<ALC_DEVICE_SPECIFIER>>
#else
      enum_type_i>
#endif
      device_specifier;

    /// @var capture_device_specifier
    /// @alcconstwrap{CAPTURE_DEVICE_SPECIFIER}
    opt_constant<
      mp_list<alc_string_query>,
#ifdef ALC_CAPTURE_DEVICE_SPECIFIER
      enum_type_c<ALC_CAPTURE_DEVICE_SPECIFIER>>
#else
      enum_type_i>
#endif
      capture_device_specifier;

    /// @var default_device_specifier
    /// @alcconstwrap{DEFAULT_DEVICE_SPECIFIER}
    opt_constant<
      mp_list<alc_string_query>,
#ifdef ALC_DEFAULT_DEVICE_SPECIFIER
      enum_type_c<ALC_DEFAULT_DEVICE_SPECIFIER>>
#else
      enum_type_i>
#endif
      default_device_specifier;

    /// @var capture_default_device_specifier
    /// @alcconstwrap{CAPTURE_DEFAULT_DEVICE_SPECIFIER}
    opt_constant<
      mp_list<alc_string_query>,
#ifdef ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER
      enum_type_c<ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER>>
#else
      enum_type_i>
#endif
      capture_default_device_specifier;

    /// @var all_devices_specifier
    /// @alcconstwrap{ALL_DEVICES_SPECIFIER}
    const c_api::dynamic_constant<mp_list<alc_string_query>, enum_type>
      all_devices_specifier;

    /// @var default_all_devices_specifier
    /// @alcconstwrap{DEFAULT_ALL_DEVICES_SPECIFIER}
    const c_api::dynamic_constant<mp_list<alc_string_query>, enum_type>
      default_all_devices_specifier;

    /// @var extensions
    /// @alcconstwrap{EXTENSIONS}
    opt_constant<
      mp_list<alc_string_query>,
#ifdef ALC_EXTENSIONS
      enum_type_c<ALC_EXTENSIONS>>
#else
      enum_type_i>
#endif
      extensions;

    /// @var major_version
    /// @alcconstwrap{MAJOR_VERSION}
    opt_constant<
      mp_list<alc_integer_query>,
#ifdef ALC_MAJOR_VERSION
      enum_type_c<ALC_MAJOR_VERSION>>
#else
      enum_type_i>
#endif
      major_version;

    /// @var minor_version
    /// @alcconstwrap{MINOR_VERSION}
    opt_constant<
      mp_list<alc_integer_query>,
#ifdef ALC_MINOR_VERSION
      enum_type_c<ALC_MINOR_VERSION>>
#else
      enum_type_i>
#endif
      minor_version;

    /// @var capture_samples
    /// @alcconstwrap{CAPTURE_SAMPLES}
    opt_constant<
      mp_list<alc_integer_query>,
#ifdef ALC_CAPTURE_SAMPLES
      enum_type_c<ALC_CAPTURE_SAMPLES>>
#else
      enum_type_i>
#endif
      capture_samples;

    /// @var frequency
    /// @alcconstwrap{FREQUENCY}
    opt_constant<
      mp_list<context_attribute>,
#ifdef ALC_FREQUENCY
      enum_type_c<ALC_FREQUENCY>>
#else
      enum_type_i>
#endif
      frequency;

    /// @var refresh
    /// @alcconstwrap{REFRESH}
    opt_constant<
      mp_list<context_attribute>,
#ifdef ALC_REFRESH
      enum_type_c<ALC_REFRESH>>
#else
      enum_type_i>
#endif
      refresh;

    /// @var sync
    /// @alcconstwrap{SYNC}
    opt_constant<
      mp_list<context_attribute>,
#ifdef ALC_SYNC
      enum_type_c<ALC_SYNC>>
#else
      enum_type_i>
#endif
      sync;

    /// @var mono_sources
    /// @alcconstwrap{MONO_SOURCES}
    opt_constant<
      mp_list<context_attribute>,
#ifdef ALC_MONO_SOURCES
      enum_type_c<ALC_MONO_SOURCES>>
#else
      enum_type_i>
#endif
      mono_sources;

    /// @var stereo_sources
    /// @alcconstwrap{STEREO_SOURCES}
    opt_constant<
      mp_list<context_attribute>,
#ifdef ALC_STEREO_SOURCES
      enum_type_c<ALC_STEREO_SOURCES>>
#else
      enum_type_i>
#endif
      stereo_sources;

    /// @var hrtf_soft
    /// @alcconstwrap{HRTF_SOFT}
    const c_api::dynamic_constant<mp_list<context_attribute>, enum_type>
      hrtf_soft;

    /// @var hrtf_id_soft
    /// @alcconstwrap{HRTF_ID_SOFT}
    const c_api::dynamic_constant<mp_list<context_attribute>, enum_type>
      hrtf_id_soft;

    /// @var hrtf_specifier_soft
    /// @alcconstwrap{HRTF_SPECIFIER_SOFT}
    const c_api::dynamic_constant<mp_list<alc_string_query>, enum_type>
      hrtf_specifier_soft;

    basic_alc_constants(ApiTraits& traits, basic_alc_c_api<ApiTraits>& api);
};
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_alc_constants<ApiTraits>::basic_alc_constants(
  ApiTraits& traits,
  basic_alc_c_api<ApiTraits>& api)
  : no_error("NO_ERROR", traits, api)
  , invalid_device("INVALID_DEVICE", traits, api)
  , invalid_context("INVALID_CONTEXT", traits, api)
  , invalid_enum("INVALID_ENUM", traits, api)
  , invalid_value("INVALID_VALUE", traits, api)
  , out_of_memory("OUT_OF_MEMORY", traits, api)
  , device_specifier("DEVICE_SPECIFIER", traits, api)
  , capture_device_specifier("CAPTURE_DEVICE_SPECIFIER", traits, api)
  , default_device_specifier("DEFAULT_DEVICE_SPECIFIER", traits, api)
  , capture_default_device_specifier(
      "DEFAULT_CAPTURE_DEVICE_SPECIFIER",
      traits,
      api)
  , all_devices_specifier("ALL_DEVICES_SPECIFIER", traits, api)
  , default_all_devices_specifier("DEFAULT_ALL_DEVICES_SPECIFIER", traits, api)
  , extensions("EXTENSIONS", traits, api)
  , major_version("MAJOR_VERSION", traits, api)
  , minor_version("MINOR_VERSION", traits, api)
  , capture_samples("CAPTURE_SAMPLES", traits, api)
  , frequency("FREQUENCY", traits, api)
  , refresh("REFRESH", traits, api)
  , sync("SYNC", traits, api)
  , mono_sources("MONO_SOURCES", traits, api)
  , stereo_sources("STEREO_SOURCES", traits, api)
  , hrtf_soft("HRTF_SOFT", traits, api)
  , hrtf_id_soft("HRTF_ID_SOFT", traits, api)
  , hrtf_specifier_soft("HRTF_SPECIFIER_SOFT", traits, api) {}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

