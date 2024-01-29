# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
add_subdirectory(modules)

set(EAGINE_OALPLUS_EXPORT_TARGETS)

install(
	TARGETS ${EAGINE_OALPLUS_EXPORT_TARGETS}
	EXPORT OALplus
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
	PUBLIC_HEADER DESTINATION include
)

