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

export module eagine.oalplus.al:api;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.string;
import eagine.core.c_api;
import :config;
import :enum_types;
import :result;
import :c_api;
import :math;
import :objects;
import :constants;
import :api_traits;

namespace eagine::oalplus {
using c_api::adapted_function;
using c_api::simple_adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the AL API.
/// @ingroup al_api_wrap
/// @see basic_al_constants
/// @see basic_al_c_api
export template <typename ApiTraits>
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

    template <auto Wrapper, typename ObjTag>
    struct gen_object_func
      : simple_adapted_function<Wrapper, void(span<name_type>)> {
        using base = simple_adapted_function<Wrapper, void(span<name_type>)>;
        using base::base;
        using base::operator();

        constexpr auto operator()() const noexcept {
            name_type n{};
            return base::operator()(cover_one(n))
              .transform_if([&n](auto, bool valid) {
                  return al_owned_object_name<ObjTag>(valid ? n : 0);
              });
        }

        constexpr auto object() const noexcept
          -> al_object<basic_al_operations, ObjTag> {
            al_owned_object_name<ObjTag> name;
            (*this)() >> name;
            return {
              static_cast<const basic_al_operations&>(base::api()),
              std::move(name)};
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
      simple_adapted_function<Wrapper, void(span<name_type>)>,
      simple_adapted_function<Wrapper, void(al_owned_object_name<ObjTag>)>>;

    del_object_func<&al_api::DeleteSources, source_tag> delete_sources{*this};

    auto clean_up(owned_source_name obj) const noexcept {
        return delete_sources(std::move(obj));
    }

    auto clean_up(al_object_name_span<source_tag> objs) const noexcept {
        return delete_sources(objs.raw_handles());
    }

    del_object_func<&al_api::DeleteBuffers, buffer_tag> delete_buffers{*this};

    auto clean_up(owned_buffer_name obj) const noexcept {
        return delete_buffers(std::move(obj));
    }

    auto clean_up(al_object_name_span<buffer_tag> objs) const noexcept {
        return delete_buffers(objs.raw_handles());
    }

    del_object_func<&al_api::DeleteEffects, effect_tag> delete_effects{*this};

    auto clean_up(owned_effect_name obj) const noexcept {
        return delete_effects(std::move(obj));
    }

    auto clean_up(al_object_name_span<effect_tag> objs) const noexcept {
        return delete_effects(objs.raw_handles());
    }

    del_object_func<&al_api::DeleteFilters, filter_tag> delete_filters{*this};

    auto clean_up(owned_filter_name obj) const noexcept {
        return delete_filters(std::move(obj));
    }

    auto clean_up(al_object_name_span<filter_tag> objs) const noexcept {
        return delete_filters(objs.raw_handles());
    }

    del_object_func<&al_api::DeleteAuxiliaryEffectSlots, auxiliary_effect_slot_tag>
      delete_auxiliary_effect_slots{*this};

    auto clean_up(owned_auxiliary_effect_slot_name obj) const noexcept {
        return delete_auxiliary_effect_slots(std::move(obj));
    }

    auto clean_up(
      al_object_name_span<auxiliary_effect_slot_tag> objs) const noexcept {
        return delete_auxiliary_effect_slots(objs.raw_handles());
    }

    simple_adapted_function<&al_api::IsSource, bool_type(source_name)> is_source{
      *this};

    simple_adapted_function<&al_api::IsBuffer, bool_type(buffer_name)> is_buffer{
      *this};

    simple_adapted_function<&al_api::IsEffect, bool_type(effect_name)> is_effect{
      *this};

    simple_adapted_function<&al_api::IsFilter, bool_type(filter_name)> is_filter{
      *this};

    simple_adapted_function<
      &al_api::IsAuxiliaryEffectSlot,
      bool_type(auxiliary_effect_slot_name)>
      is_auxiliary_effect_slot{*this};

    simple_adapted_function<&al_api::Enable, void(al_capability)> enable{*this};
    simple_adapted_function<&al_api::Disable, void(al_capability)> disable{
      *this};
    simple_adapted_function<&al_api::IsEnabled, bool(al_capability)> is_enabled{
      *this};

    c_api::combined<
      simple_adapted_function<
        &al_api::Listeneri,
        void(listener_attribute, int_type)>,
      simple_adapted_function<
        &al_api::Listener3i,
        void(listener_attribute, int_type, int_type, int_type)>,
      simple_adapted_function<
        &al_api::Listeneriv,
        void(listener_attribute, span<const int_type>)>>
      listener_i{*this};

    c_api::combined<
      simple_adapted_function<
        &al_api::Listenerf,
        void(listener_attribute, float_type)>,
      simple_adapted_function<
        &al_api::Listener3f,
        void(listener_attribute, float_type, float_type, float_type)>,
      simple_adapted_function<&al_api::Listener3f, void(listener_attribute, vec3)>,
      simple_adapted_function<
        &al_api::Listenerfv,
        void(listener_attribute, span<const float_type>)>>
      listener_f{*this};

    simple_adapted_function<
      &al_api::GetListeneriv,
      void(listener_attribute, span<int_type>)>
      get_listener_i{*this};

    simple_adapted_function<
      &al_api::GetListenerfv,
      void(listener_attribute, span<float_type>)>
      get_listener_f{*this};

    c_api::combined<
      simple_adapted_function<&al_api::Bufferi, void(buffer_attribute, int_type)>,
      simple_adapted_function<
        &al_api::Buffer3i,
        void(buffer_attribute, int_type, int_type, int_type)>,
      simple_adapted_function<
        &al_api::Bufferiv,
        void(buffer_attribute, span<const int_type>)>>
      buffer_i{*this};

    c_api::combined<
      simple_adapted_function<&al_api::Bufferf, void(buffer_attribute, float_type)>,
      simple_adapted_function<
        &al_api::Buffer3f,
        void(buffer_attribute, float_type, float_type, float_type)>,
      simple_adapted_function<&al_api::Buffer3f, void(buffer_attribute, vec3)>,
      simple_adapted_function<
        &al_api::Bufferfv,
        void(buffer_attribute, span<const float_type>)>>
      buffer_f{*this};

    simple_adapted_function<
      &al_api::GetBufferiv,
      void(buffer_name, buffer_attribute, span<int_type>)>
      get_buffer_i{*this};

    simple_adapted_function<
      &al_api::GetBufferfv,
      void(buffer_name, buffer_attribute, span<float_type>)>
      get_buffer_f{*this};

    c_api::combined<
      simple_adapted_function<
        &al_api::Sourcei,
        void(source_name, source_attribute, int_type)>,
      simple_adapted_function<
        &al_api::Source3i,
        void(source_name, source_attribute, int_type, int_type, int_type)>,
      simple_adapted_function<
        &al_api::Sourceiv,
        void(source_name, source_attribute, span<const int_type>)>>
      source_i{*this};

    c_api::combined<
      simple_adapted_function<
        &al_api::Sourcef,
        void(source_name, source_attribute, float_type)>,
      simple_adapted_function<
        &al_api::Source3f,
        void(source_name, source_attribute, float_type, float_type, float_type)>,
      simple_adapted_function<
        &al_api::Source3f,
        void(source_name, source_attribute, vec3)>,
      simple_adapted_function<
        &al_api::Sourcefv,
        void(source_name, source_attribute, span<const float_type>)>>
      source_f{*this};

    simple_adapted_function<
      &al_api::GetSourceiv,
      void(source_name, source_attribute, span<int_type>)>
      get_source_i{*this};

    simple_adapted_function<
      &al_api::GetSourcefv,
      void(source_name, source_attribute, span<float_type>)>
      get_source_f{*this};

    c_api::combined<
      simple_adapted_function<
        &al_api::SourceQueueBuffers,
        void(source_name, span<const name_type>)>,
      simple_adapted_function<
        &al_api::SourceQueueBuffers,
        void(source_name, buffer_name)>>
      source_queue_buffers{*this};

    c_api::combined<
      simple_adapted_function<
        &al_api::SourceUnqueueBuffers,
        void(source_name, span<const name_type>)>,
      simple_adapted_function<
        &al_api::SourceUnqueueBuffers,
        void(source_name, buffer_name)>>
      source_unqueue_buffers{*this};

    c_api::combined<
      simple_adapted_function<&al_api::SourcePlay, void(source_name)>,
      simple_adapted_function<&al_api::SourcePlayv, void(span<const name_type>)>>
      source_play{*this};

    c_api::combined<
      simple_adapted_function<&al_api::SourcePause, void(source_name)>,
      simple_adapted_function<&al_api::SourcePausev, void(span<const name_type>)>>
      source_pause{*this};

    c_api::combined<
      simple_adapted_function<&al_api::SourceStop, void(source_name)>,
      simple_adapted_function<&al_api::SourceStopv, void(span<const name_type>)>>
      source_stop{*this};

    c_api::combined<
      simple_adapted_function<&al_api::SourceRewind, void(source_name)>,
      simple_adapted_function<&al_api::SourceRewindv, void(span<const name_type>)>>
      source_rewind{*this};

    simple_adapted_function<&al_api::GetString, string_view(al_string_query)>
      get_string{*this};

    // get_strings
    auto get_strings(al_string_query query, char separator) const noexcept {
        return get_string(query).transform([separator](auto src) {
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
          .transform([](auto src) { return split_into_string_list(src, ' '); })
          .or_default();
    }

    basic_al_operations(api_traits& traits)
      : al_api{traits} {}
};
//------------------------------------------------------------------------------
export template <typename ApiTraits>
class basic_al_api
  : protected ApiTraits
  , public basic_al_operations<ApiTraits>
  , public basic_al_constants<ApiTraits> {
public:
    basic_al_api(ApiTraits traits)
      : ApiTraits{std::move(traits)}
      , basic_al_operations<ApiTraits>{*static_cast<ApiTraits*>(this)}
      , basic_al_constants<ApiTraits>{
          *static_cast<ApiTraits*>(this),
          *static_cast<basic_al_operations<ApiTraits>*>(this)} {}

    basic_al_api()
      : basic_al_api{ApiTraits{}} {}

    /// @brief Returns a reference to the wrapped operations.
    auto operations() const noexcept -> const basic_al_operations<ApiTraits>& {
        return *this;
    }

    /// @brief Returns a reference to the wrapped constants.
    auto constants() const noexcept -> const basic_al_constants<ApiTraits>& {
        return *this;
    }
};

export template <std::size_t I, typename ApiTraits>
auto get(const basic_al_api<ApiTraits>& x) noexcept -> const
  typename std::tuple_element<I, basic_al_api<ApiTraits>>::type& {
    return x;
}
//------------------------------------------------------------------------------
/// @brief Alias for the default instantation of basic_al_api.
/// @ingroup al_api_wrap
export using al_api = basic_al_api<al_api_traits>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std {
//------------------------------------------------------------------------------
template <typename ApiTraits>
struct tuple_size<eagine::oalplus::basic_al_api<ApiTraits>>
  : integral_constant<std::size_t, 2> {};

template <typename ApiTraits>
struct tuple_element<0, eagine::oalplus::basic_al_api<ApiTraits>>
  : type_identity<eagine::oalplus::basic_al_operations<ApiTraits>> {};

template <typename ApiTraits>
struct tuple_element<1, eagine::oalplus::basic_al_api<ApiTraits>>
  : type_identity<eagine::oalplus::basic_al_constants<ApiTraits>> {};
//------------------------------------------------------------------------------
} // namespace std
namespace eagine::oalplus {
//------------------------------------------------------------------------------
export template <typename ApiTraits>
using basic_al_api_reference =
  c_api::basic_api_reference<basic_al_api<ApiTraits>>;

export using al_api_reference = basic_al_api_reference<al_api_traits>;
//------------------------------------------------------------------------------
export struct al_context_handler : interface<al_context_handler> {
    virtual auto make_current() noexcept -> bool = 0;
};
//------------------------------------------------------------------------------
export template <typename ApiTraits>
struct basic_al_api_context {
    basic_al_api_context() noexcept = default;
    basic_al_api_context(ApiTraits traits) noexcept
      : al_api{std::move(traits)} {}

    shared_holder<al_context_handler> al_context{};
    const basic_al_api<ApiTraits> al_api{};
};
//------------------------------------------------------------------------------
export template <typename ApiTraits>
class basic_shared_al_api_context {
public:
    basic_shared_al_api_context() noexcept = default;

    template <std::derived_from<al_context_handler> ContextHandler>
    basic_shared_al_api_context(shared_holder<ContextHandler> handler) noexcept
      : _shared{default_selector} {
        set_context(std::move(handler));
    }

    explicit operator bool() const noexcept {
        return bool(_shared);
    }

    auto set_context(shared_holder<al_context_handler> context) noexcept
      -> basic_shared_al_api_context& {
        assert(_shared);
        _shared->al_context = std::move(context);
        return *this;
    }

    auto ensure() -> basic_shared_al_api_context& {
        _shared.ensure();
        return *this;
    }

    auto ensure(ApiTraits traits) -> basic_shared_al_api_context& {
        _shared.ensure(std::move(traits));
        return *this;
    }

    auto make_current() noexcept -> bool {
        if(_shared and _shared->al_context) {
            return _shared->al_context->make_current();
        }
        return false;
    }

    auto al_ref() const noexcept -> basic_al_api_reference<ApiTraits> {
        if(_shared) {
            return {_shared->al_api};
        }
        return {};
    }

    auto al_api() const noexcept -> const basic_al_api<ApiTraits>& {
        assert(_shared);
        return _shared->al_api;
    }

private:
    shared_holder<basic_al_api_context<ApiTraits>> _shared;
};

export using shared_al_api_context = basic_shared_al_api_context<al_api_traits>;
//------------------------------------------------------------------------------

} // namespace eagine::oalplus

