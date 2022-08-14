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
	eagine.oalplus.alc
	INTERFACES alc
	PARTITIONS
		config
		enum_types
		attributes
	SOURCES
)

