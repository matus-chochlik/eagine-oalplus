#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt
#
# Package specific options
#  Debian
#   Dependencies
set(CPACK_DEBIAN_OALPLUS-APPS_PACKAGE_DEPENDS "")
set(CPACK_DEBIAN_OALPLUS-DEV_PACKAGE_DEPENDS "eagine-core-dev (>= @EAGINE_VERSION@)")
#   Descriptions
set(CPACK_DEBIAN_OALPLUS-APPS_DESCRIPTION "Collection of OALplus applications.")
set(CPACK_DEBIAN_OALPLUS-DEV_DESCRIPTION "C++ wrapper for OpenAL and ALUT.")

