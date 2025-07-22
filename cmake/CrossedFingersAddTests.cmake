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

function(crossedfingers_discover_tests_impl)
    set(options "")
    set(one_value_args
            TEST_EXECUTABLE
            TEST_WORKING_DIRECTORY
            TEST_PROPERTIES
            CTEST_FILE
    )
    set(multi_value_args "")
    cmake_parse_arguments(PARSE_ARGV 0 arg "${options}" "${one_value_args}" "${multi_value_args}")

    set(PROPERTIES "WORKING_DIRECTORY ${arg_TEST_WORKING_DIRECTORY} ${arg_TEST_PROPERTIES}")
    string(REPLACE ";" " " PROPERTIES "${PROPERTIES}")

    # Remove the ctest file before writing in it
    file(REMOVE "${arg_CTEST_FILE}")

    if (NOT EXISTS "${arg_TEST_EXECUTABLE}")
        message(FATAL_ERROR "Given test executable does not exists: '${arg_TEST_EXECUTABLE}'")
    endif ()

    cmake_language(EVAL CODE
            "execute_process(
              COMMAND [==[${arg_TEST_EXECUTABLE}]==] list
              WORKING_DIRECTORY [==[${arg_TEST_WORKING_DIR}]==]
              OUTPUT_VARIABLE output
              RESULT_VARIABLE result
            )"
    )

    if (NOT ${result} EQUAL 0)
        message(FATAL_ERROR
                "Error while running test executable:\n"
                "    Path: '${arg_TEST_EXECUTABLE}'\n"
                "    Output:\n"
                "${output}"
        )
    endif ()

    # Parse output
    string(REPLACE "\n" ";" output "${output}")
    foreach (line ${output})
        # Skip empty line
        if (line STREQUAL "")
            continue()
        endif ()

        file(APPEND "${arg_CTEST_FILE}" "add_test([=[${line}]=] ${arg_TEST_EXECUTABLE} run [=[--filter=${line}]=])\n")
        file(APPEND "${arg_CTEST_FILE}" "set_tests_properties([=[${line}]=] PROPERTIES ${PROPERTIES})\n")
    endforeach ()
endfunction()

if (CMAKE_SCRIPT_MODE_FILE)
    crossedfingers_discover_tests_impl(
            TEST_EXECUTABLE "${TEST_EXECUTABLE}"
            TEST_WORKING_DIRECTORY "${TEST_WORKING_DIRECTORY}"
            TEST_PROPERTIES "${TEST_PROPERTIES}"
            CTEST_FILE "${CTEST_FILE}"
    )
endif ()
