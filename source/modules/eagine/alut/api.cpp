/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<AL/alut.h>)
#include <AL/alut.h>
#define EAGINE_HAS_ALUT 1
#else
#define EAGINE_HAS_ALUT 0
#endif

export module eagine.oalplus.alut:api;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import eagine.oalplus.al;
import :config;
import :enum_types;
import :result;
import :c_api;
import :constants;
import :api_traits;

namespace eagine::oalplus {
using c_api::plain_adapted_function;
using c_api::simple_adapted_function;
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the ALUT API.
/// @ingroup al_api_wrap
/// @see basic_alut_constants
/// @see basic_alut_c_api
export template <typename ApiTraits>
class basic_alut_operations : public basic_alut_c_api<ApiTraits> {

public:
    using api_traits = ApiTraits;
    using alut_api = basic_alut_c_api<ApiTraits>;

    using enum_type = typename alut_types::enum_type;
    using char_type = typename alut_types::char_type;
    using float_type = typename alut_types::float_type;

    plain_adapted_function<&alut_api::Init> init{*this};

    simple_adapted_function<
      &alut_api::CreateBufferHelloWorld,
      owned_buffer_name()>
      create_buffer_hello_world{*this};

    simple_adapted_function<
      &alut_api::CreateBufferFromFile,
      owned_buffer_name(string_view)>
      create_buffer_from_file{*this};

    simple_adapted_function<
      &alut_api::CreateBufferFromFileImage,
      owned_buffer_name(memory::const_block)>
      create_buffer_from_file_image{*this};

    simple_adapted_function<
      &alut_api::CreateBufferWaveform,
      owned_buffer_name(waveform_function, float_type, float_type, float_type)>
      create_buffer_waveform{*this};

    plain_adapted_function<&alut_api::Exit> exit{*this};

    basic_alut_operations(api_traits& traits)
      : alut_api{traits} {}
};
//------------------------------------------------------------------------------
export template <typename ApiTraits>
class basic_alut_api
  : protected ApiTraits
  , public basic_alut_operations<ApiTraits>
  , public basic_alut_constants<ApiTraits> {
public:
    basic_alut_api(ApiTraits traits)
      : ApiTraits{std::move(traits)}
      , basic_alut_operations<ApiTraits>{*static_cast<ApiTraits*>(this)}
      , basic_alut_constants<ApiTraits> {
        *static_cast<ApiTraits*>(this),
          *static_cast<basic_alut_operations<ApiTraits>*>(this)
    }
    {}

    basic_alut_api()
      : basic_alut_api{ApiTraits{}} {}

    /// @brief Returns a reference to the wrapped operations.
    auto operations() const noexcept
      -> const basic_alut_operations<ApiTraits>& {
        return *this;
    }

    /// @brief Returns a reference to the wrapped constants.
    auto constants() const noexcept -> const basic_alut_constants<ApiTraits>& {
        return *this;
    }
};

export template <std::size_t I, typename ApiTraits>
auto get(const basic_alut_api<ApiTraits>& x) noexcept -> const
  typename std::tuple_element<I, basic_alut_api<ApiTraits>>::type& {
    return x;
}
//------------------------------------------------------------------------------
/// @brief Alias for the default instantation of basic_alut_api.
/// @ingroup al_api_wrap
export using alut_api = basic_alut_api<alut_api_traits>;
//------------------------------------------------------------------------------
} // namespace eagine::oalplus
// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std {
//------------------------------------------------------------------------------
template <typename ApiTraits>
struct tuple_size<eagine::oalplus::basic_alut_api<ApiTraits>>
  : public std::integral_constant<std::size_t, 2> {};

template <typename ApiTraits>
struct tuple_element<0, eagine::oalplus::basic_alut_api<ApiTraits>> {
    using type = eagine::oalplus::basic_alut_operations<ApiTraits>;
};

template <typename ApiTraits>
struct tuple_element<1, eagine::oalplus::basic_alut_api<ApiTraits>> {
    using type = eagine::oalplus::basic_alut_constants<ApiTraits>;
};
//------------------------------------------------------------------------------
} // namespace std
namespace eagine::oalplus {
//------------------------------------------------------------------------------
export template <typename ApiTraits>
using basic_alut_api_reference =
  c_api::basic_api_reference<basic_alut_api<ApiTraits>>;

export using alut_api_reference = basic_alut_api_reference<alut_api_traits>;
} // namespace eagine::oalplus

