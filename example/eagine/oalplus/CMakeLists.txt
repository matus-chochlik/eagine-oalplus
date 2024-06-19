# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
#

add_custom_target(eagine-oalplus-examples ALL)
set_target_properties(
	eagine-oalplus-examples
	PROPERTIES FOLDER "Example/OALplus"
)

function(eagine_install_example TARGET_NAME)
	install(
		TARGETS ${TARGET_NAME}
		COMPONENT oalplus-examples
		DESTINATION share/eagine/example/oalplus)
endfunction()

function(eagine_example_common EXAMPLE_NAME)
	add_executable(
		oalplus-${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		"${EXAMPLE_NAME}.cpp"
		${ARGN}
	)
	eagine_add_exe_analysis(oalplus-${EXAMPLE_NAME})
	eagine_target_modules(
		oalplus-${EXAMPLE_NAME}
		std
		eagine.core
		eagine.oalplus
	)
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

eagine_add_package_property(
	oalplus-examples
	GENERATOR DEBIAN
	VARIABLE PACKAGE_DEPENDS
	VALUE "\${CXX_RUNTIME_PKGS},\${EAGINE_CORE_RUNTIME_PKGS}")

eagine_add_package_property(
	oalplus-examples
	GENERATOR DEBIAN
	VARIABLE DESCRIPTION
	VALUE "EAGine OALplus examples.")

