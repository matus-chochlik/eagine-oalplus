# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
#
set(PKG_NAME "eagine-oalplus-dev_${EAGINE_VERSION}-${EAGINE_GIT_COMMITS_SINCE_VERSION}_${PKG_ARCH}")
set(PKG_DIR "${CMAKE_CURRENT_BINARY_DIR}/${PKG_NAME}")
set(PKG_PREFIX "${PKG_DIR}/usr")
# ------------------------------------------------------------------------------
eagine_generate_module_json(eagine.oalplus)
# ------------------------------------------------------------------------------
configure_file(build-pkg.py.in build-pkg.py @ONLY)
# ------------------------------------------------------------------------------
add_custom_command(
	OUTPUT "${PKG_DIR}/DEBIAN/control"
	COMMAND ${PYTHON_COMMAND}
	ARGS "${CMAKE_CURRENT_BINARY_DIR}/build-pkg.py"
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	COMMENT "Preparing files for ${PKG_NAME}.deb package")

add_custom_command(
	OUTPUT ${PKG_NAME}.deb
	COMMAND ${DPKG_DEB_COMMAND}
	ARGS --build --root-owner-group ${PKG_NAME}
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	DEPENDS eagine.oalplus "${PKG_DIR}/DEBIAN/control"
	COMMENT "Building ${PKG_NAME}.deb package")
# ------------------------------------------------------------------------------
add_custom_target(
	eagine-oalplus-dev-deb
	DEPENDS ${PKG_NAME}.deb)

add_dependencies(eagine-oalplus-deb eagine-oalplus-dev-deb)

