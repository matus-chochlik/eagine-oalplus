/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_AL_API_API_HPP
#define EAGINE_OALPLUS_AL_API_API_HPP

#include "c_api.hpp"
#include "enum_types.hpp"
#include "object_name.hpp"
#include <eagine/c_api/adapted_function.hpp>
#include <eagine/c_api_wrap.hpp>
#include <eagine/scope_exit.hpp>
#include <eagine/string_list.hpp>

namespace eagine::oalplus {
using c_api::adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the AL API.
/// @ingroup al_api_wrap
/// @see basic_al_constants
/// @see basic_al_c_api
template <typename ApiTraits>
class basic_al_operations : public basic_al_c_api<ApiTraits> {

public:
    using api_traits = ApiTraits;
    using al_api = basic_al_c_api<ApiTraits>;

    using int_type = typename al_types::int_type;
    using bool_type = typename al_types::char_type;
    using char_type = typename al_types::char_type;
    using enum_type = typename al_types::enum_type;
    using name_type = typename al_types::name_type;
    using size_type = typename al_types::size_type;
    using float_type = typename al_types::float_type;

    struct derived_func
      : derived_c_api_function<al_api, api_traits, nothing_t> {
        using base = derived_c_api_function<al_api, api_traits, nothing_t>;
        using base::base;

        template <typename Res>
        constexpr auto _check(Res&& res) const noexcept {
            res.error_code(this->api().GetError());
            return std::forward<Res>(res);
        }
    };

    template <typename W, W al_api::*F, typename Signature = typename W::signature>
    class func;

    template <typename W, W al_api::*F, typename RVC, typename... Params>
    class func<W, F, RVC(Params...)>
      : public wrapped_c_api_function<al_api, api_traits, nothing_t, W, F> {
        using base =
          wrapped_c_api_function<al_api, api_traits, nothing_t, W, F>;

    private:
        template <typename Res>
        constexpr auto _check(Res&& res) const noexcept {
            res.error_code(this->api().GetError());
            return std::forward<Res>(res);
        }

    protected:
        template <typename... Args>
        constexpr auto _chkcall(Args&&... args) const noexcept {
            return this->_check(this->_call(std::forward<Args>(args)...));
        }

        using base::_conv;

    public:
        using base::base;

        constexpr auto operator()(Params... params) const noexcept {
            return this->_chkcall(_conv(params)...)
              .cast_to(type_identity<RVC>{});
        }
    };

    template <auto Wrapper, typename ObjTag>
    struct gen_object_func : adapted_function<Wrapper, void(span<name_type>)> {
        using base = adapted_function<Wrapper, void(span<name_type>)>;
        using base::base;
        using base::operator();

        constexpr auto operator()() const noexcept {
            name_type n{};
            return base::operator()(cover_one(n)).transformed([&n](bool valid) {
                return al_owned_object_name<ObjTag>(valid ? n : 0);
            });
        }
    };

    gen_object_func<&al_api::GenSources, source_tag> gen_sources{*this};

    gen_object_func<&al_api::GenBuffers, buffer_tag> gen_buffers{*this};

    gen_object_func<&al_api::GenEffects, effect_tag> gen_effects{*this};

    gen_object_func<&al_api::GenFilters, filter_tag> gen_filters{*this};

    gen_object_func<&al_api::GenAuxiliaryEffectSlots, auxiliary_effect_slot_tag>
      gen_auxiliary_effect_slots{*this};

    template <auto Wrapper, typename ObjTag>
    using del_object_func = c_api::combined<
      adapted_function<Wrapper, void(span<name_type>)>,
      adapted_function<Wrapper, void(al_owned_object_name<ObjTag>)>>;

    del_object_func<&al_api::DeleteSources, source_tag> delete_sources{*this};

    del_object_func<&al_api::DeleteBuffers, buffer_tag> delete_buffers{*this};

    del_object_func<&al_api::DeleteEffects, effect_tag> delete_effects{*this};

    del_object_func<&al_api::DeleteFilters, filter_tag> delete_filters{*this};

    del_object_func<&al_api::DeleteAuxiliaryEffectSlots, auxiliary_effect_slot_tag>
      delete_auxiliary_effect_slots{*this};

    adapted_function<&al_api::IsSource, bool_type(source_name)> is_source{
      *this};

    adapted_function<&al_api::IsBuffer, bool_type(buffer_name)> is_buffer{
      *this};

    adapted_function<&al_api::IsEffect, bool_type(effect_name)> is_effect{
      *this};

    adapted_function<&al_api::IsFilter, bool_type(filter_name)> is_filter{
      *this};

    adapted_function<
      &al_api::IsAuxiliaryEffectSlot,
      bool_type(auxiliary_effect_slot_name)>
      is_auxiliary_effect_slot{*this};

    c_api::combined<
      adapted_function<&al_api::Listeneri, void(listener_attribute, int_type)>,
      adapted_function<
        &al_api::Listener3i,
        void(listener_attribute, int_type, int_type, int_type)>,
      adapted_function<
        &al_api::Listeneriv,
        void(listener_attribute, span<const int_type>)>>
      listener_i{*this};

    c_api::combined<
      adapted_function<&al_api::Listenerf, void(listener_attribute, float_type)>,
      adapted_function<
        &al_api::Listener3f,
        void(listener_attribute, float_type, float_type, float_type)>,
      adapted_function<
        &al_api::Listenerfv,
        void(listener_attribute, span<const float_type>)>>
      listener_f{*this};

    adapted_function<
      &al_api::GetListeneriv,
      void(listener_attribute, span<int_type>)>
      get_listener_i{*this};

    adapted_function<
      &al_api::GetListenerfv,
      void(listener_attribute, span<float_type>)>
      get_listener_f{*this};

    c_api::combined<
      adapted_function<&al_api::Bufferi, void(buffer_attribute, int_type)>,
      adapted_function<
        &al_api::Buffer3i,
        void(buffer_attribute, int_type, int_type, int_type)>,
      adapted_function<
        &al_api::Bufferiv,
        void(buffer_attribute, span<const int_type>)>>
      buffer_i{*this};

    c_api::combined<
      adapted_function<&al_api::Bufferf, void(buffer_attribute, float_type)>,
      adapted_function<
        &al_api::Buffer3f,
        void(buffer_attribute, float_type, float_type, float_type)>,
      adapted_function<
        &al_api::Bufferfv,
        void(buffer_attribute, span<const float_type>)>>
      buffer_f{*this};

    adapted_function<
      &al_api::GetBufferiv,
      void(buffer_name, buffer_attribute, span<int_type>)>
      get_buffer_i{*this};

    adapted_function<
      &al_api::GetBufferfv,
      void(buffer_name, buffer_attribute, span<float_type>)>
      get_buffer_f{*this};

    c_api::combined<
      adapted_function<
        &al_api::Sourcei,
        void(source_name, source_attribute, int_type)>,
      adapted_function<
        &al_api::Source3i,
        void(source_name, source_attribute, int_type, int_type, int_type)>,
      adapted_function<
        &al_api::Sourceiv,
        void(source_name, source_attribute, span<const int_type>)>>
      source_i{*this};

    c_api::combined<
      adapted_function<
        &al_api::Sourcef,
        void(source_name, source_attribute, float_type)>,
      adapted_function<
        &al_api::Source3f,
        void(source_name, source_attribute, float_type, float_type, float_type)>,
      adapted_function<
        &al_api::Sourcefv,
        void(source_name, source_attribute, span<const float_type>)>>
      source_f{*this};

    adapted_function<
      &al_api::GetSourceiv,
      void(source_name, source_attribute, span<int_type>)>
      get_source_i{*this};

    adapted_function<
      &al_api::GetSourcefv,
      void(source_name, source_attribute, span<float_type>)>
      get_source_f{*this};

    c_api::combined<
      adapted_function<
        &al_api::SourceQueueBuffers,
        void(source_name, span<const name_type>)>,
      adapted_function<&al_api::SourceQueueBuffers, void(source_name, buffer_name)>>
      source_queue_buffers{*this};

    c_api::combined<
      adapted_function<
        &al_api::SourceUnqueueBuffers,
        void(source_name, span<const name_type>)>,
      adapted_function<
        &al_api::SourceUnqueueBuffers,
        void(source_name, buffer_name)>>
      source_unqueue_buffers{*this};

    c_api::combined<
      adapted_function<&al_api::SourcePlay, void(source_name)>,
      adapted_function<&al_api::SourcePlayv, void(span<const name_type>)>>
      source_play{*this};

    c_api::combined<
      adapted_function<&al_api::SourcePause, void(source_name)>,
      adapted_function<&al_api::SourcePausev, void(span<const name_type>)>>
      source_pause{*this};

    c_api::combined<
      adapted_function<&al_api::SourceStop, void(source_name)>,
      adapted_function<&al_api::SourceStopv, void(span<const name_type>)>>
      source_stop{*this};

    c_api::combined<
      adapted_function<&al_api::SourceRewind, void(source_name)>,
      adapted_function<&al_api::SourceRewindv, void(span<const name_type>)>>
      source_rewind{*this};

    adapted_function<&al_api::GetString, string_view(al_string_query)>
      get_string{*this};

    // get_strings
    auto get_strings(al_string_query query, char separator) const noexcept {
        return get_string(query).transformed([separator](auto src, bool) {
            return split_into_string_list(src, separator);
        });
    }

    // get_extensions
    auto get_extensions() const noexcept {
#ifdef AL_EXTENSIONS
        return get_string(al_string_query(AL_EXTENSIONS))
#else
        return get_string
          .fail()
#endif
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    basic_al_operations(api_traits& traits)
      : al_api{traits} {}
};
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#endif // EAGINE_OALPLUS_AL_API_API_HPP
