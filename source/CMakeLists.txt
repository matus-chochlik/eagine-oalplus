# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
if(${WITH_MODULES})
	add_subdirectory(modules)
else()
	add_subdirectory(lib)
endif()

set(EAGINE_OALPLUS_EXPORT_TARGETS)

if(TARGET eagine-oalplus)
	add_library(EAGine::OALplus INTERFACE IMPORTED GLOBAL)
	target_link_libraries(
		EAGine::OALplus
		INTERFACE
			eagine-oalplus-headers
			eagine-oalplus
	)
	list(
		APPEND EAGINE_OALPLUS_EXPORT_TARGETS
			eagine-oalplus-headers
	)

	install(
		EXPORT OALplus
		NAMESPACE EAGine::
		FILE OALplus.cmake
		DESTINATION lib/cmake/EAGine
	)
endif()

install(
	TARGETS ${EAGINE_OALPLUS_EXPORT_TARGETS}
	EXPORT OALplus
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
	PUBLIC_HEADER DESTINATION include
)

