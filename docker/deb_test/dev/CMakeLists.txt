# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 3.16)
project(eagine_oalplus_deb_test CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

find_package(EAGine REQUIRED COMPONENTS OALplus)

if(EAGineOALplus_FOUND)
	if(TARGET EAGine::OALplus)
		message("EAGine OALplus found")
		add_subdirectory(example)
	else()
		message(FATAL_ERROR "EAGine OALplus target not found")
	endif()
else()
	message(FATAL_ERROR "EAGine OALplus package not found")
endif()

