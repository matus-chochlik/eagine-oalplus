# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	PARTITION config
	IMPORTS
		std
		eagine.core.types)

eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	PARTITION enum_types
	IMPORTS
		std config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api)

eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	PARTITION attributes
	IMPORTS
		std config enum_types
		eagine.core.types
		eagine.core.c_api)

eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	PARTITION result
	IMPORTS
		std config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api)

eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	PARTITION objects
	IMPORTS
		std config
		eagine.core.types
		eagine.core.memory
		eagine.core.identifier
		eagine.core.c_api)

eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	PARTITION c_api
	IMPORTS
		std config enum_types
		objects result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api)

eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	PARTITION api_traits
	IMPORTS
		std config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api)

eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	PARTITION constants
	IMPORTS
		std config
		enum_types c_api
		eagine.core.types
		eagine.core.c_api)

eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	PARTITION api
	IMPORTS
		std config enum_types
		attributes constants objects
		api_traits c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.string
		eagine.core.utility
		eagine.core.identifier
		eagine.core.c_api
		eagine.core.main_ctx)

eagine_add_module(
	eagine.oalplus.alc
	COMPONENT oalplus-dev
	SOURCES
	IMPORTS
		std
		eagine.core.types)

target_link_libraries(
	eagine.oalplus.alc
	PUBLIC
	OpenAL::OpenAL)
