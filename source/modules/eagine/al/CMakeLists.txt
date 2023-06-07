# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
eagine_add_module(
	eagine.oalplus.al PARTITION config
	IMPORTS eagine.core.types
)

eagine_add_module(
	eagine.oalplus.al PARTITION enum_types
	IMPORTS
		config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION result
	IMPORTS
		config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION objects
	IMPORTS
		config
		eagine.core.types
		eagine.core.memory
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION c_api
	IMPORTS
		config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION api_traits
	IMPORTS
		config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION constants
	IMPORTS
		config enum_types c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.identifier
		eagine.core.valid_if
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION from_string
	IMPORTS
		enum_types constants
		eagine.core.types
		eagine.core.memory
		eagine.core.string
		eagine.core.valid_if
)

eagine_add_module(
	eagine.oalplus.al PARTITION api
	IMPORTS
		config enum_types
		constants objects
		api_traits c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.string
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al
	SOURCES
		constants
	IMPORTS
		eagine.core.types
		eagine.core.memory
		eagine.core.container
		eagine.core.valid_if
)
target_link_libraries(
	eagine.oalplus.al
	PUBLIC
	OpenAL::OpenAL
)

eagine_add_module_tests(
	eagine.oalplus.al
	UNITS
		constants
	IMPORTS
		eagine.core
)
