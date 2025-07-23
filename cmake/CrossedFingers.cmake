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

cmake_minimum_required(VERSION 3.22)

set(CURRENT_DIR "${CMAKE_CURRENT_LIST_DIR}")

function(crossedfingers_discover_tests target)
    set(options "")
    set(one_value_args
            WORKING_DIRECTORY
    )
    set(multi_value_args
            PROPERTIES
    )
    cmake_parse_arguments(PARSE_ARGV 1 arg "${options}" "${one_value_args}" "${multi_value_args}")

    # Arguments default values
    if (NOT arg_WORKING_DIRECTORY)
        set(arg_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    endif ()

    # Define test list files names
    set(ctest_file_base "${CMAKE_CURRENT_BINARY_DIR}/${target}")
    set(ctest_include_file "${ctest_file_base}_include.cmake")
    set(ctest_tests_file "${ctest_file_base}_tests.cmake")

    # Begin generation
    add_custom_command(
            TARGET ${target} POST_BUILD
            BYPRODUCTS "${ctest_tests_file}"
            COMMAND "${CMAKE_COMMAND}"
            -D "TEST_EXECUTABLE=$<TARGET_FILE:${target}>"
            -D "TEST_WORKING_DIRECTORY=${arg_WORKING_DIRECTORY}"
            -D "TEST_PROPERTIES=${arg_PROPERTIES}"
            -D "CTEST_FILE=${ctest_tests_file}"
            -P "${CURRENT_DIR}/CrossedFingersAddTests.cmake"
            VERBATIM
    )
    file(WRITE "${ctest_include_file}"
            "if(EXISTS \"${ctest_tests_file}\")\n"
            "  include(\"${ctest_tests_file}\")\n"
            "else()\n"
            "  message(WARNING \"${target} not built\")\n"
            "endif()\n"
    )

    set_property(DIRECTORY
            APPEND PROPERTY TEST_INCLUDE_FILES "${ctest_include_file}"
    )
endfunction()
