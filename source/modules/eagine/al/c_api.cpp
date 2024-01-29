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

export module eagine.oalplus.al:c_api;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :result;

#ifndef OALPLUS_AL_STATIC_FUNC
#if EAGINE_HAS_AL
#define OALPLUS_AL_STATIC_FUNC(NAME) &::al##NAME
#else
#define OALPLUS_AL_STATIC_FUNC(NAME) nullptr
#endif
#endif

namespace eagine::oalplus {
//------------------------------------------------------------------------------
/// @brief Class wrapping the C-functions from the AL API.
/// @ingroup al_api_wrap
/// @see basic_al_constants
/// @see basic_al_operations
export template <typename ApiTraits>
class basic_al_c_api {
    ApiTraits& _traits;

public:
    using this_api = basic_al_c_api;

    /// @brief Alias for the API traits policy type passed as template argument.
    using api_traits = ApiTraits;

    static constexpr bool has_api = al_types::has_api;

    /// @brief Alias for enumeration type.
    using enum_type = typename al_types::enum_type;

    /// @brief Alias for string characted type.
    using char_type = typename al_types::char_type;

    /// @brief Alias for boolean type.
    using bool_type = typename al_types::bool_type;

    /// @brief Alias for signed interger type.
    using int_type = typename al_types::int_type;

    /// @brief Alias for unsigned integer type.
    using uint_type = typename al_types::uint_type;

    /// @brief Alias for object handle type.
    using name_type = typename al_types::name_type;

    /// @brief Alias for integer type used to store sizes and counts.
    using size_type = typename al_types::size_type;

    /// @brief Alias for floating-point type.
    using float_type = typename al_types::float_type;

    /// @brief Alias for double-precision floating-point type.
    using double_type = typename al_types::double_type;

    /// @brief Untyped non-const pointer type.
    using void_ptr_type = typename al_types::void_ptr_type;

    /// @brief Untyped const pointer type.
    using const_void_ptr_type = typename al_types::const_void_ptr_type;

    template <typename Result, typename... U>
    constexpr auto check_result(Result res, U&&...) const noexcept {
        res.error_code(this->GetError());
        return res;
    }

    /// @brief Alias for AL C-API function wrapper template.
    template <
      typename Signature,
      c_api::function_ptr<api_traits, nothing_t, Signature> Function>
    using al_api_function = c_api::opt_function<
      api_traits,
      nothing_t,
      Signature,
      Function,
      has_api,
      bool(Function)>;

    /// @var GetError
    /// @alfuncwrap{GetError}
    al_api_function<enum_type(), OALPLUS_AL_STATIC_FUNC(GetError)> GetError{
      "GetError",
      *this};

    /// @var GetProcAddress
    /// @alfuncwrap{GetProcAddress}
    al_api_function<
      void_ptr_type(const char_type*),
      OALPLUS_AL_STATIC_FUNC(GetProcAddress)>
      GetProcAddress{"GetProcAddress", *this};

    /// @var GetEnumValue
    /// @alfuncwrap{GetEnumValue}
    al_api_function<
      enum_type(const char_type*),
      OALPLUS_AL_STATIC_FUNC(GetEnumValue)>
      GetEnumValue{"GetEnumValue", *this};

    /// @var Enable
    /// @alfuncwrap{Enable}
    al_api_function<void(enum_type), OALPLUS_AL_STATIC_FUNC(Enable)> Enable{
      "Enable",
      *this};

    /// @var Disable
    /// @alfuncwrap{Disable}
    al_api_function<void(enum_type), OALPLUS_AL_STATIC_FUNC(Disable)> Disable{
      "Disable",
      *this};

    /// @var IsEnabled
    /// @alfuncwrap{IsEnabled}
    al_api_function<bool_type(enum_type), OALPLUS_AL_STATIC_FUNC(IsEnabled)>
      IsEnabled{"IsEnabled", *this};

    /// @var GetBooleanv
    /// @alfuncwrap{GetBooleanv}
    al_api_function<
      void(enum_type, bool_type*),
      OALPLUS_AL_STATIC_FUNC(GetBooleanv)>
      GetBooleanv{"GetBooleanv", *this};

    /// @var GetIntegerv
    /// @alfuncwrap{GetIntegerv}
    al_api_function<
      void(enum_type, int_type*),
      OALPLUS_AL_STATIC_FUNC(GetIntegerv)>
      GetIntegerv{"GetIntegerv", *this};

    /// @var GetFloatv
    /// @alfuncwrap{GetFloatv}
    al_api_function<
      void(enum_type, float_type*),
      OALPLUS_AL_STATIC_FUNC(GetFloatv)>
      GetFloatv{"GetFloatv", *this};

    /// @var GetDoublev
    /// @alfuncwrap{GetDoublev}
    al_api_function<
      void(enum_type, double_type*),
      OALPLUS_AL_STATIC_FUNC(GetDoublev)>
      GetDoublev{"GetDoublev", *this};

    /// @var GetBoolean
    /// @alfuncwrap{GetBoolean}
    al_api_function<bool_type(enum_type), OALPLUS_AL_STATIC_FUNC(GetBoolean)>
      GetBoolean{"GetBoolean", *this};

    /// @var GetInteger
    /// @alfuncwrap{GetInteger}
    al_api_function<int_type(enum_type), OALPLUS_AL_STATIC_FUNC(GetInteger)>
      GetInteger{"GetInteger", *this};

    /// @var GetInteger
    /// @alfuncwrap{GetInteger}
    al_api_function<float_type(enum_type), OALPLUS_AL_STATIC_FUNC(GetFloat)>
      GetFloat{"GetFloat", *this};

    /// @var GetFloat
    /// @alfuncwrap{GetFloat}
    al_api_function<double_type(enum_type), OALPLUS_AL_STATIC_FUNC(GetDouble)>
      GetDouble{"GetDouble", *this};

    /// @var GetString
    /// @alfuncwrap{GetString}
    al_api_function<
      const char_type*(enum_type),
      OALPLUS_AL_STATIC_FUNC(GetString)>
      GetString{"GetString", *this};

    /// @var DistanceModel
    /// @alfuncwrap{DistanceModel}
    al_api_function<void(enum_type), OALPLUS_AL_STATIC_FUNC(DistanceModel)>
      DistanceModel{"DistanceModel", *this};

    /// @var DopplerFactor
    /// @alfuncwrap{DopplerFactor}
    al_api_function<void(float_type), OALPLUS_AL_STATIC_FUNC(DopplerFactor)>
      DopplerFactor{"DopplerFactor", *this};

    /// @var SpeedOfSound
    /// @alfuncwrap{SpeedOfSound}
    al_api_function<void(float_type), OALPLUS_AL_STATIC_FUNC(SpeedOfSound)>
      SpeedOfSound{"SpeedOfSound", *this};

    /// @var Listeneri
    /// @alfuncwrap{Listeneri}
    al_api_function<void(enum_type, int_type), OALPLUS_AL_STATIC_FUNC(Listeneri)>
      Listeneri{"Listeneri", *this};

    /// @var Listener3i
    /// @alfuncwrap{Listener3i}
    al_api_function<
      void(enum_type, int_type, int_type, int_type),
      OALPLUS_AL_STATIC_FUNC(Listener3i)>
      Listener3i{"Listener3i", *this};

    /// @var Listeneriv
    /// @alfuncwrap{Listeneriv}
    al_api_function<
      void(enum_type, const int_type*),
      OALPLUS_AL_STATIC_FUNC(Listeneriv)>
      Listeneriv{"Listeneriv", *this};

    /// @var GetListeneriv
    /// @alfuncwrap{GetListeneriv}
    al_api_function<
      void(enum_type, int_type*),
      OALPLUS_AL_STATIC_FUNC(GetListeneriv)>
      GetListeneriv{"GetListeneriv", *this};

    /// @var Listenerf
    /// @alfuncwrap{Listenerf}
    al_api_function<
      void(enum_type, float_type),
      OALPLUS_AL_STATIC_FUNC(Listenerf)>
      Listenerf{"Listenerf", *this};

    /// @var Listener3f
    /// @alfuncwrap{Listener3f}
    al_api_function<
      void(enum_type, float_type, float_type, float_type),
      OALPLUS_AL_STATIC_FUNC(Listener3f)>
      Listener3f{"Listener3f", *this};

    /// @var Listenerfv
    /// @alfuncwrap{Listenerfv}
    al_api_function<
      void(enum_type, const float_type*),
      OALPLUS_AL_STATIC_FUNC(Listenerfv)>
      Listenerfv{"Listenerfv", *this};

    /// @var GetListenerfv
    /// @alfuncwrap{GetListenerfv}
    al_api_function<
      void(enum_type, float_type*),
      OALPLUS_AL_STATIC_FUNC(GetListenerfv)>
      GetListenerfv{"GetListenerfv", *this};

    /// @var GenBuffers
    /// @alfuncwrap{GenBuffers}
    al_api_function<
      void(size_type, name_type*),
      OALPLUS_AL_STATIC_FUNC(GenBuffers)>
      GenBuffers{"GenBuffers", *this};

    /// @var DeleteBuffers
    /// @alfuncwrap{DeleteBuffers}
    al_api_function<
      void(size_type, const name_type*),
      OALPLUS_AL_STATIC_FUNC(DeleteBuffers)>
      DeleteBuffers{"DeleteBuffers", *this};

    /// @var IsBuffer
    /// @alfuncwrap{IsBuffer}
    al_api_function<bool_type(name_type), OALPLUS_AL_STATIC_FUNC(IsBuffer)>
      IsBuffer{"IsBuffer", *this};

    /// @var BufferData
    /// @alfuncwrap{BufferData}
    al_api_function<
      void(name_type, enum_type, const_void_ptr_type, size_type, size_type),
      OALPLUS_AL_STATIC_FUNC(BufferData)>
      BufferData{"BufferData", *this};

    /// @var Bufferi
    /// @alfuncwrap{Bufferi}
    al_api_function<
      void(name_type, enum_type, int_type),
      OALPLUS_AL_STATIC_FUNC(Bufferi)>
      Bufferi{"Bufferi", *this};

    /// @var Buffer3i
    /// @alfuncwrap{Buffer3i}
    al_api_function<
      void(name_type, enum_type, int_type, int_type, int_type),
      OALPLUS_AL_STATIC_FUNC(Buffer3i)>
      Buffer3i{"Buffer3i", *this};

    /// @var Bufferiv
    /// @alfuncwrap{Bufferiv}
    al_api_function<
      void(name_type, enum_type, const int_type*),
      OALPLUS_AL_STATIC_FUNC(Bufferiv)>
      Bufferiv{"Bufferiv", *this};

    /// @var GetBufferiv
    /// @alfuncwrap{GetBufferiv}
    al_api_function<
      void(name_type, enum_type, int_type*),
      OALPLUS_AL_STATIC_FUNC(GetBufferiv)>
      GetBufferiv{"GetBufferiv", *this};

    /// @var Bufferf
    /// @alfuncwrap{Bufferf}
    al_api_function<
      void(name_type, enum_type, float_type),
      OALPLUS_AL_STATIC_FUNC(Bufferf)>
      Bufferf{"Bufferf", *this};

    /// @var Buffer3f
    /// @alfuncwrap{Buffer3f}
    al_api_function<
      void(name_type, enum_type, float_type, float_type, float_type),
      OALPLUS_AL_STATIC_FUNC(Buffer3f)>
      Buffer3f{"Buffer3f", *this};

    /// @var Bufferfv
    /// @alfuncwrap{Bufferfv}
    al_api_function<
      void(name_type, enum_type, const float_type*),
      OALPLUS_AL_STATIC_FUNC(Bufferfv)>
      Bufferfv{"Bufferfv", *this};

    /// @var GetBufferfv
    /// @alfuncwrap{GetBufferfv}
    al_api_function<
      void(name_type, enum_type, float_type*),
      OALPLUS_AL_STATIC_FUNC(GetBufferfv)>
      GetBufferfv{"GetBufferfv", *this};

    /// @var GenSources
    /// @alfuncwrap{GenSources}
    al_api_function<
      void(size_type, name_type*),
      OALPLUS_AL_STATIC_FUNC(GenSources)>
      GenSources{"GenSources", *this};

    /// @var DeleteSources
    /// @alfuncwrap{DeleteSources}
    al_api_function<
      void(size_type, const name_type*),
      OALPLUS_AL_STATIC_FUNC(DeleteSources)>
      DeleteSources{"DeleteSources", *this};

    /// @var IsSource
    /// @alfuncwrap{IsSource}
    al_api_function<bool_type(name_type), OALPLUS_AL_STATIC_FUNC(IsSource)>
      IsSource{"IsSource", *this};

    /// @var Sourcei
    /// @alfuncwrap{Sourcei}
    al_api_function<
      void(name_type, enum_type, int_type),
      OALPLUS_AL_STATIC_FUNC(Sourcei)>
      Sourcei{"Sourcei", *this};

    /// @var Source3i
    /// @alfuncwrap{Source3i}
    al_api_function<
      void(name_type, enum_type, int_type, int_type, int_type),
      OALPLUS_AL_STATIC_FUNC(Source3i)>
      Source3i{"Source3i", *this};

    /// @var Sourceiv
    /// @alfuncwrap{Sourceiv}
    al_api_function<
      void(name_type, enum_type, const int_type*),
      OALPLUS_AL_STATIC_FUNC(Sourceiv)>
      Sourceiv{"Sourceiv", *this};

    /// @var GetSourceiv
    /// @alfuncwrap{GetSourceiv}
    al_api_function<
      void(name_type, enum_type, int_type*),
      OALPLUS_AL_STATIC_FUNC(GetSourceiv)>
      GetSourceiv{"GetSourceiv", *this};

    /// @var Sourcef
    /// @alfuncwrap{Sourcef}
    al_api_function<
      void(name_type, enum_type, float_type),
      OALPLUS_AL_STATIC_FUNC(Sourcef)>
      Sourcef{"Sourcef", *this};

    /// @var Source3f
    /// @alfuncwrap{Source3f}
    al_api_function<
      void(name_type, enum_type, float_type, float_type, float_type),
      OALPLUS_AL_STATIC_FUNC(Source3f)>
      Source3f{"Source3f", *this};

    /// @var Sourcefv
    /// @alfuncwrap{Sourcefv}
    al_api_function<
      void(name_type, enum_type, const float_type*),
      OALPLUS_AL_STATIC_FUNC(Sourcefv)>
      Sourcefv{"Sourcefv", *this};

    /// @var GetSourcefv
    /// @alfuncwrap{GetSourcefv}
    al_api_function<
      void(name_type, enum_type, float_type*),
      OALPLUS_AL_STATIC_FUNC(GetSourcefv)>
      GetSourcefv{"GetSourcefv", *this};

    /// @var SourcePlay
    /// @alfuncwrap{SourcePlay}
    al_api_function<void(name_type), OALPLUS_AL_STATIC_FUNC(SourcePlay)>
      SourcePlay{"SourcePlay", *this};

    /// @var SourceStop
    /// @alfuncwrap{SourceStop}
    al_api_function<void(name_type), OALPLUS_AL_STATIC_FUNC(SourceStop)>
      SourceStop{"SourceStop", *this};

    /// @var SourceRewind
    /// @alfuncwrap{SourceRewind}
    al_api_function<void(name_type), OALPLUS_AL_STATIC_FUNC(SourceRewind)>
      SourceRewind{"SourceRewind", *this};

    /// @var SourcePause
    /// @alfuncwrap{SourcePause}
    al_api_function<void(name_type), OALPLUS_AL_STATIC_FUNC(SourcePause)>
      SourcePause{"SourcePause", *this};

    /// @var SourcePlayv
    /// @alfuncwrap{SourcePlayv}
    al_api_function<
      void(size_type, const name_type*),
      OALPLUS_AL_STATIC_FUNC(SourcePlayv)>
      SourcePlayv{"SourcePlayv", *this};

    /// @var SourceStopv
    /// @alfuncwrap{SourceStopv}
    al_api_function<
      void(size_type, const name_type*),
      OALPLUS_AL_STATIC_FUNC(SourceStopv)>
      SourceStopv{"SourceStopv", *this};

    /// @var SourceRewindv
    /// @alfuncwrap{SourceRewindv}
    al_api_function<
      void(size_type, const name_type*),
      OALPLUS_AL_STATIC_FUNC(SourceRewindv)>
      SourceRewindv{"SourceRewindv", *this};

    /// @var SourcePausev
    /// @alfuncwrap{SourcePausev}
    al_api_function<
      void(size_type, const name_type*),
      OALPLUS_AL_STATIC_FUNC(SourcePausev)>
      SourcePausev{"SourcePausev", *this};

    /// @var SourceQueueBuffers
    /// @alfuncwrap{SourceQueueBuffers}
    al_api_function<
      void(name_type, size_type, const name_type*),
      OALPLUS_AL_STATIC_FUNC(SourceQueueBuffers)>
      SourceQueueBuffers{"SourceQueueBuffers", *this};

    /// @var SourceUnqueueBuffers
    /// @alfuncwrap{SourceUnqueueBuffers}
    al_api_function<
      void(name_type, size_type, name_type*),
      OALPLUS_AL_STATIC_FUNC(SourceUnqueueBuffers)>
      SourceUnqueueBuffers{"SourceUnqueueBuffers", *this};

    /// @var GenEffects
    /// @alfuncwrap{GenEffects}
    al_api_function<void(size_type, name_type*), nullptr> GenEffects{
      "GenEffects",
      *this};

    /// @var DeleteEffects
    /// @alfuncwrap{DeleteEffects}
    al_api_function<void(size_type, const name_type*), nullptr> DeleteEffects{
      "DeleteEffects",
      *this};

    /// @var IsEffect
    /// @alfuncwrap{IsEffect}
    al_api_function<bool_type(name_type), nullptr> IsEffect{"IsEffect", *this};

    /// @var Effecti
    /// @alfuncwrap{Effecti}
    al_api_function<void(name_type, enum_type, int_type), nullptr> Effecti{
      "Effecti",
      *this};

    /// @var Effectiv
    /// @alfuncwrap{Effectiv}
    al_api_function<void(name_type, enum_type, const int_type*), nullptr>
      Effectiv{"Effecti", *this};

    /// @var Effectf
    /// @alfuncwrap{Effectf}
    al_api_function<void(name_type, enum_type, float_type), nullptr> Effectf{
      "Effectf",
      *this};

    /// @var Effectfv
    /// @alfuncwrap{Effectfv}
    al_api_function<void(name_type, enum_type, const float_type*), nullptr>
      Effectfv{"Effectfv", *this};

    /// @var GetEffecti
    /// @alfuncwrap{GetEffecti}
    al_api_function<void(name_type, enum_type, int_type*), nullptr> GetEffecti{
      "GetEffecti",
      *this};

    /// @var GetEffectiv
    /// @alfuncwrap{GetEffectiv}
    al_api_function<void(name_type, enum_type, int_type*), nullptr> GetEffectiv{
      "GetEffectiv",
      *this};

    /// @var GetEffectf
    /// @alfuncwrap{GetEffectf}
    al_api_function<void(name_type, enum_type, float_type*), nullptr> GetEffectf{
      "GetEffectf",
      *this};

    /// @var GetEffectfv
    /// @alfuncwrap{GetEffectfv}
    al_api_function<void(name_type, enum_type, float_type*), nullptr>
      GetEffectfv{"GetEffectfv", *this};

    /// @var GenFilters
    /// @alfuncwrap{GenFilters}
    al_api_function<void(size_type, name_type*), nullptr> GenFilters{
      "GenFilters",
      *this};

    /// @var DeleteFilters
    /// @alfuncwrap{DeleteFilters}
    al_api_function<void(size_type, const name_type*), nullptr> DeleteFilters{
      "DeleteFilters",
      *this};

    /// @var IsFilter
    /// @alfuncwrap{IsFilter}
    al_api_function<bool_type(name_type), nullptr> IsFilter{"IsFilter", *this};

    /// @var Filteri
    /// @alfuncwrap{Filteri}
    al_api_function<void(name_type, enum_type, int_type), nullptr> Filteri{
      "Filteri",
      *this};

    /// @var Filteriv
    /// @alfuncwrap{Filteriv}
    al_api_function<void(name_type, enum_type, const int_type*), nullptr>
      Filteriv{"Filteriv", *this};

    /// @var Filterf
    /// @alfuncwrap{Filterf}
    al_api_function<void(name_type, enum_type, float_type), nullptr> Filterf{
      "Filterf",
      *this};

    /// @var Filterfv
    /// @alfuncwrap{Filterfv}
    al_api_function<void(name_type, enum_type, const float_type*), nullptr>
      Filterfv{"Filterfv", *this};

    /// @var GetFilteri
    /// @alfuncwrap{GetFilteri}
    al_api_function<void(name_type, enum_type, int_type*), nullptr> GetFilteri{
      "GetFilteri",
      *this};

    /// @var GetFilteriv
    /// @alfuncwrap{GetFilteriv}
    al_api_function<void(name_type, enum_type, int_type*), nullptr> GetFilteriv{
      "GetFilteriv",
      *this};

    /// @var GetFilterf
    /// @alfuncwrap{GetFilterf}
    al_api_function<void(name_type, enum_type, float_type*), nullptr> GetFilterf{
      "GetFilterf",
      *this};

    /// @var GetFilterfv
    /// @alfuncwrap{GetFilterfv}
    al_api_function<void(name_type, enum_type, float_type*), nullptr>
      GetFilterfv{"GetFilterfv", *this};

    /// @var GenAuxiliaryEffectSlots
    /// @alfuncwrap{GenAuxiliaryEffectSlots}
    al_api_function<void(size_type, name_type*), nullptr>
      GenAuxiliaryEffectSlots{"GenAuxiliaryEffectSlots", *this};

    /// @var DeleteAuxiliaryEffectSlots
    /// @alfuncwrap{DeleteAuxiliaryEffectSlots}
    al_api_function<void(size_type, const name_type*), nullptr>
      DeleteAuxiliaryEffectSlots{"DeleteAuxiliaryEffectSlots", *this};

    /// @var IsAuxiliaryEffectSlot
    /// @alfuncwrap{IsAuxiliaryEffectSlot}
    al_api_function<bool_type(name_type), nullptr> IsAuxiliaryEffectSlot{
      "IsAuxiliaryEffectSlot",
      *this};

    /// @var AuxiliaryEffectSloti
    /// @alfuncwrap{AuxiliaryEffectSloti}
    al_api_function<void(name_type, enum_type, int_type), nullptr>
      AuxiliaryEffectSloti{"AuxiliaryEffectSloti", *this};

    /// @var AuxiliaryEffectSlotiv
    /// @alfuncwrap{AuxiliaryEffectSlotiv}
    al_api_function<void(name_type, enum_type, const int_type*), nullptr>
      AuxiliaryEffectSlotiv{"AuxiliaryEffectSlotiv", *this};

    /// @var AuxiliaryEffectSlotf
    /// @alfuncwrap{AuxiliaryEffectSlotf}
    al_api_function<void(name_type, enum_type, float_type), nullptr>
      AuxiliaryEffectSlotf{"AuxiliaryEffectSlotf", *this};

    /// @var AuxiliaryEffectSlotfv
    /// @alfuncwrap{AuxiliaryEffectSlotfv}
    al_api_function<void(name_type, enum_type, const float_type*), nullptr>
      AuxiliaryEffectSlotfv{"AuxiliaryEffectSlotfv", *this};

    /// @var GetAuxiliaryEffectSloti
    /// @alfuncwrap{GetAuxiliaryEffectSloti}
    al_api_function<void(name_type, enum_type, int_type*), nullptr>
      GetAuxiliaryEffectSloti{"GetAuxiliaryEffectSloti", *this};

    /// @var GetAuxiliaryEffectSlotiv
    /// @alfuncwrap{GetError}
    al_api_function<void(name_type, enum_type, int_type*), nullptr>
      GetAuxiliaryEffectSlotiv{"GetAuxiliaryEffectSlotiv", *this};

    /// @var GetAuxiliaryEffectSlotf
    /// @alfuncwrap{GetAuxiliaryEffectSlotf}
    al_api_function<void(name_type, enum_type, float_type*), nullptr>
      GetAuxiliaryEffectSlotf{"GetAuxiliaryEffectSlotf", *this};

    /// @var GetAuxiliaryEffectSlotfv
    /// @alfuncwrap{GetAuxiliaryEffectSlotfv}
    al_api_function<void(name_type, enum_type, float_type*), nullptr>
      GetAuxiliaryEffectSlotfv{"GetAuxiliaryEffectSlotfv", *this};

    basic_al_c_api(api_traits& traits)
      : _traits{traits} {}

    auto traits() noexcept -> api_traits& {
        return _traits;
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

