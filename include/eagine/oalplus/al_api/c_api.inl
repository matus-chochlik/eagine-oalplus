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
  : GetError{"GetError", traits, *this}
  , GetProcAddress{"GetProcAddress", traits, *this}
  , GetEnumValue{"GetEnumValue", traits, *this}
  , Enable{"Enable", traits, *this}
  , Disable{"Disable", traits, *this}
  , IsEnabled{"IsEnabled", traits, *this}
  , GetBooleanv{"GetBooleanv", traits, *this}
  , GetIntegerv{"GetIntegerv", traits, *this}
  , GetFloatv{"GetFloatv", traits, *this}
  , GetDoublev{"GetDoublev", traits, *this}
  , GetBoolean{"GetBoolean", traits, *this}
  , GetInteger{"GetInteger", traits, *this}
  , GetFloat{"GetFloat", traits, *this}
  , GetDouble{"GetDouble", traits, *this}
  , GetString{"GetString", traits, *this}
  , DistanceModel{"DistanceModel", traits, *this}
  , DopplerFactor{"DopplerFactor", traits, *this}
  , SpeedOfSound{"SpeedOfSound", traits, *this}
  , Listeneri{"Listeneri", traits, *this}
  , Listener3i{"Listener3i", traits, *this}
  , Listeneriv{"Listeneriv", traits, *this}
  , GetListeneriv{"GetListeneriv", traits, *this}
  , Listenerf{"Listenerf", traits, *this}
  , Listener3f{"Listener3f", traits, *this}
  , Listenerfv{"Listenerfv", traits, *this}
  , GetListenerfv{"GetListenerfv", traits, *this}
  , GenBuffers{"GenBuffers", traits, *this}
  , DeleteBuffers{"DeleteBuffers", traits, *this}
  , IsBuffer{"IsBuffer", traits, *this}
  , BufferData{"BufferData", traits, *this}
  , Bufferi{"Bufferi", traits, *this}
  , Buffer3i{"Buffer3i", traits, *this}
  , Bufferiv{"Bufferiv", traits, *this}
  , GetBufferiv{"GetBufferiv", traits, *this}
  , Bufferf{"Bufferf", traits, *this}
  , Buffer3f{"Buffer3f", traits, *this}
  , Bufferfv{"Bufferfv", traits, *this}
  , GetBufferfv{"GetBufferfv", traits, *this}
  , GenSources{"GenSources", traits, *this}
  , DeleteSources{"DeleteSources", traits, *this}
  , IsSource{"IsSource", traits, *this}
  , Sourcei{"Sourcei", traits, *this}
  , Source3i{"Source3i", traits, *this}
  , Sourceiv{"Sourceiv", traits, *this}
  , GetSourceiv{"GetSourceiv", traits, *this}
  , Sourcef{"Sourcef", traits, *this}
  , Source3f{"Source3f", traits, *this}
  , Sourcefv{"Sourcefv", traits, *this}
  , GetSourcefv{"GetSourcefv", traits, *this}
  , SourcePlay{"SourcePlay", traits, *this}
  , SourceStop{"SourceStop", traits, *this}
  , SourceRewind{"SourceRewind", traits, *this}
  , SourcePause{"SourcePause", traits, *this}
  , SourcePlayv{"SourcePlayv", traits, *this}
  , SourceStopv{"SourceStopv", traits, *this}
  , SourceRewindv{"SourceRewindv", traits, *this}
  , SourcePausev{"SourcePausev", traits, *this}
  , SourceQueueBuffers{"SourceQueueBuffers", traits, *this}
  , SourceUnqueueBuffers{"SourceUnqueueBuffers", traits, *this}
  , GenEffects{"GenEffects", traits, *this}
  , DeleteEffects{"DeleteEffects", traits, *this}
  , IsEffect{"IsEffect", traits, *this}
  , Effecti{"Effecti", traits, *this}
  , Effectiv{"Effecti", traits, *this}
  , Effectf{"Effecti", traits, *this}
  , Effectfv{"Effecti", traits, *this}
  , GetEffecti{"GetEffecti", traits, *this}
  , GetEffectiv{"GetEffecti", traits, *this}
  , GetEffectf{"GetEffecti", traits, *this}
  , GetEffectfv{"GetEffecti", traits, *this}
  , GenFilters{"GenFilters", traits, *this}
  , DeleteFilters{"DeleteFilters", traits, *this}
  , IsFilter{"IsFilter", traits, *this}
  , Filteri{"Filteri", traits, *this}
  , Filteriv{"Filteri", traits, *this}
  , Filterf{"Filteri", traits, *this}
  , Filterfv{"Filteri", traits, *this}
  , GetFilteri{"GetFilteri", traits, *this}
  , GetFilteriv{"GetFilteri", traits, *this}
  , GetFilterf{"GetFilteri", traits, *this}
  , GetFilterfv{"GetFilteri", traits, *this}
  , GenAuxiliaryEffectSlots{"GenEffects", traits, *this}
  , DeleteAuxiliaryEffectSlots{"DeleteEffects", traits, *this}
  , IsAuxiliaryEffectSlot{"IsEffect", traits, *this}
  , AuxiliaryEffectSloti{"Effecti", traits, *this}
  , AuxiliaryEffectSlotiv{"Effecti", traits, *this}
  , AuxiliaryEffectSlotf{"Effecti", traits, *this}
  , AuxiliaryEffectSlotfv{"Effecti", traits, *this}
  , GetAuxiliaryEffectSloti{"GetEffecti", traits, *this}
  , GetAuxiliaryEffectSlotiv{"GetEffecti", traits, *this}
  , GetAuxiliaryEffectSlotf{"GetEffecti", traits, *this}
  , GetAuxiliaryEffectSlotfv{"GetEffecti", traits, *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
