# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
eagine_add_module(
	eagine.oalplus.alc PARTITION config
	IMPORTS eagine.core.types
)

eagine_add_module(
	eagine.oalplus.alc PARTITION enum_types
	IMPORTS
		config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alc PARTITION attributes
	IMPORTS
		config enum_types
		eagine.core.types
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alc PARTITION result
	IMPORTS
		config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alc PARTITION objects
	IMPORTS
		config
		eagine.core.types
		eagine.core.memory
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alc PARTITION c_api
	IMPORTS
		config enum_types
		objects result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alc PARTITION api_traits
	IMPORTS
		config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.oalplus.alc
	INTERFACES alc
	PARTITIONS
		config
		enum_types
		attributes
		result
		objects
		c_api
		api_traits
	SOURCES
)

