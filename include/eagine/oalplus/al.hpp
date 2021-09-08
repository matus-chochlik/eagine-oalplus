/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_OALPLUS_AL_HPP
#define EAGINE_OALPLUS_AL_HPP

#include <eagine/config/basic.hpp>

#if __has_include(<AL/al.h>)
#include <AL/al.h>
#endif
#if __has_include(<AL/alc.h>)
#include <AL/alc.h>
#endif
#if __has_include(<AL/alut.h>)
#include <AL/alut.h>
#endif

#endif // EAGINE_OALPLUS_AL_HPP
