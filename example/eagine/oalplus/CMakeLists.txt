# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#

add_custom_target(eagine-oalplus-examples ALL)
set_target_properties(
	eagine-oalplus-examples
	PROPERTIES FOLDER "Example/OALplus"
)

function(eagine_install_example TARGET_NAME)
	install(
		TARGETS ${TARGET_NAME}
		DESTINATION share/eagine/example/oalplus
	)
endfunction()

function(eagine_example_common EXAMPLE_NAME)
	add_executable(
		oalplus-${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		"${EXAMPLE_NAME}.cpp"
		${ARGN}
	)
	if(${WITH_MODULES})
		eagine_target_modules(
			oalplus-${EXAMPLE_NAME}
			eagine.core
			eagine.oalplus
		)
	else()
		eagine_add_exe_analysis(oalplus-${EXAMPLE_NAME})
		target_link_libraries(
			oalplus-${EXAMPLE_NAME}
			PUBLIC EAGine::OALplus
			PRIVATE ${ARGN}
		)
	endif()
	add_dependencies(eagine-oalplus-examples oalplus-${EXAMPLE_NAME})

	set_target_properties(
		oalplus-${EXAMPLE_NAME}
		PROPERTIES FOLDER "Example/OALplus"
	)
	eagine_install_example(oalplus-${EXAMPLE_NAME})
endfunction()

eagine_example_common(001_basic_info)
eagine_example_common(002_list_devices)
eagine_example_common(003_list_extensions)
eagine_example_common(004_context_info)
eagine_example_common(005_hello_world)

