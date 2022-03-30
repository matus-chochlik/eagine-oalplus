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
#define OALPAFP(FUNC) decltype(al_api::FUNC), &al_api::FUNC
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
    struct del_object_func : adapted_function<Wrapper, void(span<name_type>)> {
        using base = adapted_function<Wrapper, void(span<name_type>)>;
        using base::base;
        using base::raii;
        using base::operator();

        constexpr auto operator()(
          al_owned_object_name<ObjTag>& name) const noexcept {
            auto n = name.release();
            return base::operator()(cover_one(n));
        }

        auto raii(al_owned_object_name<ObjTag>& name) const noexcept {
            return eagine::finally([this, &name]() { (*this)(name); });
        }

        template <typename Res>
        auto raii_opt(Res& res) const noexcept {
            return eagine::finally([this, &res]() {
                if(res) {
                    (*this)(extract(res));
                }
            });
        }
    };

    del_object_func<&al_api::DeleteSources, source_tag> delete_sources{*this};

    del_object_func<&al_api::DeleteBuffers, buffer_tag> delete_buffers{*this};

    del_object_func<&al_api::DeleteEffects, effect_tag> delete_effects{*this};

    del_object_func<&al_api::DeleteFilters, filter_tag> delete_filters{*this};

    del_object_func<&al_api::DeleteAuxiliaryEffectSlots, auxiliary_effect_slot_tag>
      delete_auxiliary_effect_slots{*this};

    template <typename ObjTag, typename W, W al_api::*IsObject>
    struct is_object_func : func<W, IsObject> {
        using func<W, IsObject>::func;

        constexpr auto operator()(al_object_name<ObjTag> name) const noexcept {
            return this->_chkcall(name_type(name));
        }
    };

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

    // listener_i
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().Listeneri) &&
                   bool(this->api().Listener3i) && bool(this->api().Listeneriv);
        }

        constexpr auto operator()(listener_attribute attr, int_type v0)
          const noexcept {
            return this->_check(
              this->_call(this->api().Listeneri, enum_type(attr), v0));
        }

        constexpr auto operator()(
          listener_attribute attr,
          int_type v0,
          int_type v1,
          int_type v2) const noexcept {
            return this->_check(
              this->_call(this->api().Listener3i, enum_type(attr), v0, v1, v2));
        }

        constexpr auto operator()(
          listener_attribute attr,
          span<const int_type> v) const noexcept {
            return this->_check(
              this->_call(this->api().Listeneriv, enum_type(attr), v.data()));
        }
    } listener_i;

    // listener_f
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().Listenerf) &&
                   bool(this->api().Listener3f) && bool(this->api().Listenerfv);
        }

        constexpr auto operator()(listener_attribute attr, float_type v0)
          const noexcept {
            return this->_check(
              this->_call(this->api().Listenerf, enum_type(attr), v0));
        }

        constexpr auto operator()(
          listener_attribute attr,
          float_type v0,
          float_type v1,
          float_type v2) const noexcept {
            return this->_check(
              this->_call(this->api().Listener3f, enum_type(attr), v0, v1, v2));
        }

        constexpr auto operator()(
          listener_attribute attr,
          span<const float_type> v) const noexcept {
            return this->_check(
              this->_call(this->api().Listenerfv, enum_type(attr), v.data()));
        }
    } listener_f;

    // get_listener_i
    struct : func<OALPAFP(GetListeneriv)> {
        using func<OALPAFP(GetListeneriv)>::func;

        constexpr auto operator()(listener_attribute attr, span<int_type> v)
          const noexcept {
            return this->_chkcall(enum_type(attr), v.data());
        }
    } get_listener_i;

    // get_listener_f
    struct : func<OALPAFP(GetListenerfv)> {
        using func<OALPAFP(GetListenerfv)>::func;

        constexpr auto operator()(listener_attribute attr, span<float_type> v)
          const noexcept {
            return this->_chkcall(enum_type(attr), v.data());
        }
    } get_listener_f;

    // buffer_i
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().Bufferi) && bool(this->api().Buffer3i) &&
                   bool(this->api().Bufferiv);
        }

        constexpr auto operator()(
          buffer_name src,
          buffer_attribute attr,
          int_type v0) const noexcept {
            return this->_check(this->_call(
              this->api().Bufferi, name_type(src), enum_type(attr), v0));
        }

        constexpr auto operator()(
          buffer_name src,
          buffer_attribute attr,
          int_type v0,
          int_type v1,
          int_type v2) const noexcept {
            return this->_check(this->_call(
              this->api().Buffer3i,
              name_type(src),
              enum_type(attr),
              v0,
              v1,
              v2));
        }

        constexpr auto operator()(
          buffer_name src,
          buffer_attribute attr,
          span<const int_type> v) const noexcept {
            return this->_check(this->_call(
              this->api().Bufferiv, name_type(src), enum_type(attr), v.data()));
        }
    } buffer_i;

    // buffer_f
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().Bufferf) && bool(this->api().Buffer3f) &&
                   bool(this->api().Bufferfv);
        }

        constexpr auto operator()(
          buffer_name src,
          buffer_attribute attr,
          float_type v0) const noexcept {
            return this->_check(this->_call(
              this->api().Bufferf, name_type(src), enum_type(attr), v0));
        }

        constexpr auto operator()(
          buffer_name src,
          buffer_attribute attr,
          float_type v0,
          float_type v1,
          float_type v2) const noexcept {
            return this->_check(this->_call(
              this->api().Buffer3f,
              name_type(src),
              enum_type(attr),
              v0,
              v1,
              v2));
        }

        constexpr auto operator()(
          buffer_name src,
          buffer_attribute attr,
          span<const float_type> v) const noexcept {
            return this->_check(this->_call(
              this->api().Bufferfv, name_type(src), enum_type(attr), v.data()));
        }
    } buffer_f;

    // get_buffer_i
    struct : func<OALPAFP(GetBufferiv)> {
        using func<OALPAFP(GetBufferiv)>::func;

        constexpr auto operator()(
          buffer_name src,
          buffer_attribute attr,
          span<int_type> v) const noexcept {
            return this->_chkcall(name_type(src), enum_type(attr), v.data());
        }
    } get_buffer_i;

    // get_buffer_f
    struct : func<OALPAFP(GetBufferfv)> {
        using func<OALPAFP(GetBufferfv)>::func;

        constexpr auto operator()(
          buffer_name src,
          buffer_attribute attr,
          span<float_type> v) const noexcept {
            return this->_chkcall(name_type(src), enum_type(attr), v.data());
        }
    } get_buffer_f;

    // source_i
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().Sourcei) && bool(this->api().Source3i) &&
                   bool(this->api().Sourceiv);
        }

        constexpr auto operator()(
          source_name src,
          source_attribute attr,
          int_type v0) const noexcept {
            return this->_check(this->_call(
              this->api().Sourcei, name_type(src), enum_type(attr), v0));
        }

        constexpr auto operator()(
          source_name src,
          source_attribute attr,
          int_type v0,
          int_type v1,
          int_type v2) const noexcept {
            return this->_check(this->_call(
              this->api().Source3i,
              name_type(src),
              enum_type(attr),
              v0,
              v1,
              v2));
        }

        constexpr auto operator()(
          source_name src,
          source_attribute attr,
          span<const int_type> v) const noexcept {
            return this->_check(this->_call(
              this->api().Sourceiv, name_type(src), enum_type(attr), v.data()));
        }
    } source_i;

    // source_f
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().Sourcef) && bool(this->api().Source3f) &&
                   bool(this->api().Sourcefv);
        }

        constexpr auto operator()(
          source_name src,
          source_attribute attr,
          float_type v0) const noexcept {
            return this->_check(this->_call(
              this->api().Sourcef, name_type(src), enum_type(attr), v0));
        }

        constexpr auto operator()(
          source_name src,
          source_attribute attr,
          float_type v0,
          float_type v1,
          float_type v2) const noexcept {
            return this->_check(this->_call(
              this->api().Source3f,
              name_type(src),
              enum_type(attr),
              v0,
              v1,
              v2));
        }

        constexpr auto operator()(
          source_name src,
          source_attribute attr,
          span<const float_type> v) const noexcept {
            return this->_check(this->_call(
              this->api().Sourcefv, name_type(src), enum_type(attr), v.data()));
        }
    } source_f;

    // get_source_i
    struct : func<OALPAFP(GetSourceiv)> {
        using func<OALPAFP(GetSourceiv)>::func;

        constexpr auto operator()(
          source_name src,
          source_attribute attr,
          span<int_type> v) const noexcept {
            return this->_chkcall(name_type(src), enum_type(attr), v.data());
        }
    } get_source_i;

    // get_source_f
    struct : func<OALPAFP(GetSourcefv)> {
        using func<OALPAFP(GetSourcefv)>::func;

        constexpr auto operator()(
          source_name src,
          source_attribute attr,
          span<float_type> v) const noexcept {
            return this->_chkcall(name_type(src), enum_type(attr), v.data());
        }
    } get_source_f;

    // source_queue_buffers
    struct : func<OALPAFP(SourceQueueBuffers)> {
        using func<OALPAFP(SourceQueueBuffers)>::func;

        constexpr auto operator()(source_name src, buffer_name buf)
          const noexcept {
            const auto n = name_type(buf);
            return this->_chkcall(name_type(src), 1, &n);
        }

        constexpr auto operator()(source_name src, span<const name_type> bufs)
          const noexcept {
            return this->_chkcall(
              name_type(src), size_type(bufs.size()), bufs.data());
        }
    } source_queue_buffers;

    // source_unqueue_buffers
    struct : func<OALPAFP(SourceUnqueueBuffers)> {
        using func<OALPAFP(SourceUnqueueBuffers)>::func;

        constexpr auto operator()(source_name src, buffer_name buf)
          const noexcept {
            auto n = name_type(buf);
            return this->_chkcall(name_type(src), 1, &n);
        }

        constexpr auto operator()(source_name src, span<name_type> bufs)
          const noexcept {
            return this->_chkcall(
              name_type(src), size_type(bufs.size()), bufs.data());
        }
    } source_unqueue_buffers;

    // source_play
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().SourcePlay) &&
                   bool(this->api().SourcePlayv);
        }

        constexpr auto operator()(source_name src) const noexcept {
            return this->_check(
              this->_call(this->api().SourcePlay, name_type(src)));
        }

        constexpr auto operator()(span<const name_type> srcs) const noexcept {
            return this->_check(this->_call(
              this->api().SourcePlayv, size_type(srcs.size()), srcs.data()));
        }
    } source_play;

    // source_pause
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().SourcePause) &&
                   bool(this->api().SourcePausev);
        }

        constexpr auto operator()(source_name src) const noexcept {
            return this->_check(
              this->_call(this->api().SourcePause, name_type(src)));
        }

        constexpr auto operator()(span<const name_type> srcs) const noexcept {
            return this->_check(this->_call(
              this->api().SourcePausev, size_type(srcs.size()), srcs.data()));
        }
    } source_pause;

    // source_stop
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().SourceStop) &&
                   bool(this->api().SourceStopv);
        }

        constexpr auto operator()(source_name src) const noexcept {
            return this->_check(
              this->_call(this->api().SourceStop, name_type(src)));
        }

        constexpr auto operator()(span<const name_type> srcs) const noexcept {
            return this->_check(this->_call(
              this->api().SourceStopv, size_type(srcs.size()), srcs.data()));
        }
    } source_stop;

    // source_rewind
    struct : derived_func {
        using derived_func::derived_func;

        explicit constexpr operator bool() const noexcept {
            return bool(this->api().SourceRewind) &&
                   bool(this->api().SourceRewindv);
        }

        constexpr auto operator()(source_name src) const noexcept {
            return this->_check(
              this->_call(this->api().SourceRewind, name_type(src)));
        }

        constexpr auto operator()(span<const name_type> srcs) const noexcept {
            return this->_check(this->_call(
              this->api().SourceRewindv, size_type(srcs.size()), srcs.data()));
        }
    } source_rewind;

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

    basic_al_operations(api_traits& traits);
};
//------------------------------------------------------------------------------
#undef OALPAFP
//------------------------------------------------------------------------------
} // namespace eagine::oalplus

#endif // EAGINE_OALPLUS_AL_API_API_HPP
