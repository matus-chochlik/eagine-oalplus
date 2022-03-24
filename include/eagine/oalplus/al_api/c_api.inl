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
basic_al_c_api<ApiTraits>::basic_al_c_api(api_traits& traits)
  : _traits{traits}
  , GetError{"GetError", *this}
  , GetProcAddress{"GetProcAddress", *this}
  , GetEnumValue{"GetEnumValue", *this}
  , Enable{"Enable", *this}
  , Disable{"Disable", *this}
  , IsEnabled{"IsEnabled", *this}
  , GetBooleanv{"GetBooleanv", *this}
  , GetIntegerv{"GetIntegerv", *this}
  , GetFloatv{"GetFloatv", *this}
  , GetDoublev{"GetDoublev", *this}
  , GetBoolean{"GetBoolean", *this}
  , GetInteger{"GetInteger", *this}
  , GetFloat{"GetFloat", *this}
  , GetDouble{"GetDouble", *this}
  , GetString{"GetString", *this}
  , DistanceModel{"DistanceModel", *this}
  , DopplerFactor{"DopplerFactor", *this}
  , SpeedOfSound{"SpeedOfSound", *this}
  , Listeneri{"Listeneri", *this}
  , Listener3i{"Listener3i", *this}
  , Listeneriv{"Listeneriv", *this}
  , GetListeneriv{"GetListeneriv", *this}
  , Listenerf{"Listenerf", *this}
  , Listener3f{"Listener3f", *this}
  , Listenerfv{"Listenerfv", *this}
  , GetListenerfv{"GetListenerfv", *this}
  , GenBuffers{"GenBuffers", *this}
  , DeleteBuffers{"DeleteBuffers", *this}
  , IsBuffer{"IsBuffer", *this}
  , BufferData{"BufferData", *this}
  , Bufferi{"Bufferi", *this}
  , Buffer3i{"Buffer3i", *this}
  , Bufferiv{"Bufferiv", *this}
  , GetBufferiv{"GetBufferiv", *this}
  , Bufferf{"Bufferf", *this}
  , Buffer3f{"Buffer3f", *this}
  , Bufferfv{"Bufferfv", *this}
  , GetBufferfv{"GetBufferfv", *this}
  , GenSources{"GenSources", *this}
  , DeleteSources{"DeleteSources", *this}
  , IsSource{"IsSource", *this}
  , Sourcei{"Sourcei", *this}
  , Source3i{"Source3i", *this}
  , Sourceiv{"Sourceiv", *this}
  , GetSourceiv{"GetSourceiv", *this}
  , Sourcef{"Sourcef", *this}
  , Source3f{"Source3f", *this}
  , Sourcefv{"Sourcefv", *this}
  , GetSourcefv{"GetSourcefv", *this}
  , SourcePlay{"SourcePlay", *this}
  , SourceStop{"SourceStop", *this}
  , SourceRewind{"SourceRewind", *this}
  , SourcePause{"SourcePause", *this}
  , SourcePlayv{"SourcePlayv", *this}
  , SourceStopv{"SourceStopv", *this}
  , SourceRewindv{"SourceRewindv", *this}
  , SourcePausev{"SourcePausev", *this}
  , SourceQueueBuffers{"SourceQueueBuffers", *this}
  , SourceUnqueueBuffers{"SourceUnqueueBuffers", *this}
  , GenEffects{"GenEffects", *this}
  , DeleteEffects{"DeleteEffects", *this}
  , IsEffect{"IsEffect", *this}
  , Effecti{"Effecti", *this}
  , Effectiv{"Effecti", *this}
  , Effectf{"Effecti", *this}
  , Effectfv{"Effecti", *this}
  , GetEffecti{"GetEffecti", *this}
  , GetEffectiv{"GetEffecti", *this}
  , GetEffectf{"GetEffecti", *this}
  , GetEffectfv{"GetEffecti", *this}
  , GenFilters{"GenFilters", *this}
  , DeleteFilters{"DeleteFilters", *this}
  , IsFilter{"IsFilter", *this}
  , Filteri{"Filteri", *this}
  , Filteriv{"Filteri", *this}
  , Filterf{"Filteri", *this}
  , Filterfv{"Filteri", *this}
  , GetFilteri{"GetFilteri", *this}
  , GetFilteriv{"GetFilteri", *this}
  , GetFilterf{"GetFilteri", *this}
  , GetFilterfv{"GetFilteri", *this}
  , GenAuxiliaryEffectSlots{"GenEffects", *this}
  , DeleteAuxiliaryEffectSlots{"DeleteEffects", *this}
  , IsAuxiliaryEffectSlot{"IsEffect", *this}
  , AuxiliaryEffectSloti{"Effecti", *this}
  , AuxiliaryEffectSlotiv{"Effecti", *this}
  , AuxiliaryEffectSlotf{"Effecti", *this}
  , AuxiliaryEffectSlotfv{"Effecti", *this}
  , GetAuxiliaryEffectSloti{"GetEffecti", *this}
  , GetAuxiliaryEffectSlotiv{"GetEffecti", *this}
  , GetAuxiliaryEffectSlotf{"GetEffecti", *this}
  , GetAuxiliaryEffectSlotfv{"GetEffecti", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
