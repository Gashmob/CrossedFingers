# MIT License
#
# Copyright (c) 2025-Present Kevin Traini
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
include_guard()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

function(lib_package)
    set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
    set(CPACK_PACKAGE_VENDOR "CrossedFingers developers")
    set(CPACK_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
    set(CPACK_PACKAGE_CONTACT "Kevin Traini <kevin@ktraini.com>")
    set(CPACK_PACKAGE_DESCRIPTION "CrossedFingers")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ testing framework")
    set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/Gashmob/CrossedFingers")
    set(CPACK_PACKAGE_CHECKSUM "SHA512")
    set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.md")
    set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")

    # RPM package
    set(CPACK_RPM_PACKAGE_LICENSE "MIT")
    set(CPACK_RPM_PACKAGE_GROUP "Development/Tools")
    set(CPACK_RPM_PACKAGE_DESCRIPTION "CrossedFingers")
    set(CPACK_RPM_CHANGELOG_FILE "${CMAKE_CURRENT_BINARY_DIR}/changelog")

    # CMake package
    set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Location of header files")
    set(CROSSEDFINGERS_CMAKE_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/crossedfingers" CACHE STRING "Installation directory for cmake files, relative to ${CMAKE_INSTALL_PREFIX}.")
    set(version_config "${PROJECT_BINARY_DIR}/crossedfingers-config-version.cmake")
    set(project_config "${PROJECT_BINARY_DIR}/crossedfingers-config.cmake")
    set(targets_export_name crossedfingers-targets)
    set(PACKAGE_TEMPLATE_DIR "${PROJECT_SOURCE_DIR}/cmake/package")
    write_basic_package_version_file(
            ${version_config}
            VERSION ${VERSION}
            COMPATIBILITY SameMajorVersion
            ARCH_INDEPENDENT
    )
    configure_package_config_file(
            "${PACKAGE_TEMPLATE_DIR}/crossedfingers-config.cmake.in"
            ${project_config}
            INSTALL_DESTINATION ${CROSSEDFINGERS_CMAKE_DIR}
            PATH_VARS INCLUDE_INSTALL_DIR
    )
    export(TARGETS crossedfingers crossedfingers_main NAMESPACE crossedfingers::
            FILE ${PROJECT_BINARY_DIR}/${targets_export_name}.cmake)

    install(FILES
            ${project_config}
            ${version_config}
            DESTINATION ${CROSSEDFINGERS_CMAKE_DIR})
    install(FILES
            "${PROJECT_SOURCE_DIR}/cmake/CrossedFingers.cmake"
            "${PROJECT_SOURCE_DIR}/cmake/CrossedFingersAddTests.cmake"
            DESTINATION "${CROSSEDFINGERS_CMAKE_DIR}/modules")
    install(EXPORT ${targets_export_name} DESTINATION ${CROSSEDFINGERS_CMAKE_DIR}
            NAMESPACE crossedfingers::)
    install(TARGETS crossedfingers crossedfingers_main EXPORT ${targets_export_name} DESTINATION ${CMAKE_INSTALL_LIBDIR})
    install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION ${INCLUDE_INSTALL_DIR})

    include(CPack)
endfunction()
