# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
eagine_add_module(
	eagine.oalplus.alut PARTITION config
	IMPORTS
		eagine.core.types
		eagine.oalplus.al
)

eagine_add_module(
	eagine.oalplus.alut PARTITION enum_types
	IMPORTS
		config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alut PARTITION result
	IMPORTS
		config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alut PARTITION c_api
	IMPORTS
		config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alut PARTITION api_traits
	IMPORTS
		config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alut PARTITION constants
	IMPORTS
		config enum_types c_api
		eagine.core.types
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alut PARTITION api
	IMPORTS
		config enum_types
		constants
		api_traits c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
		eagine.oalplus.al
)

eagine_add_module(
	eagine.oalplus.alut
	SOURCES
	IMPORTS
		eagine.core.types
)
target_link_libraries(
	eagine.oalplus.alut
	PUBLIC
	OpenAL::OpenAL
)
