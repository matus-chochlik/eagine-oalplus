# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
add_subdirectory(al)
add_subdirectory(alc)
add_subdirectory(alut)

eagine_add_module(
	eagine.oalplus
	SUBMODULES
		al
		alc
		alut)

eagine_add_license(oalplus-dev)
eagine_add_debian_changelog(oalplus-dev)

