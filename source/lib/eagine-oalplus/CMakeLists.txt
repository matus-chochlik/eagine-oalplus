# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

add_library(eagine-oalplus INTERFACE IMPORTED GLOBAL)

target_link_libraries(
	eagine-oalplus
	INTERFACE
		OpenAL::OpenAL
		EAGine::Core
		eagine-oalplus-headers
)
