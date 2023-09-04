# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
eagine_add_module(
	eagine.oalplus.al PARTITION config
	IMPORTS
		std
		eagine.core.types
)

eagine_add_module(
	eagine.oalplus.al PARTITION math
	IMPORTS
		std config
		eagine.core.types
		eagine.core.math
)

eagine_add_module(
	eagine.oalplus.al PARTITION enum_types
	IMPORTS
		std config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION result
	IMPORTS
		std config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION objects
	IMPORTS
		std config
		eagine.core.types
		eagine.core.memory
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION c_api
	IMPORTS
		std config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION api_traits
	IMPORTS
		std config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION constants
	IMPORTS
		std config
		enum_types c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.identifier
		eagine.core.valid_if
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.al PARTITION from_string
	IMPORTS
		std enum_types constants
		eagine.core.types
		eagine.core.memory
		eagine.core.string
		eagine.core.valid_if
)

eagine_add_module(
	eagine.oalplus.al PARTITION api
	IMPORTS
		std config enum_types
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
		std
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
