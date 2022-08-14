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
	eagine.oalplus.alut
	INTERFACES alut
	PARTITIONS
		config
		enum_types
	SOURCES
)
