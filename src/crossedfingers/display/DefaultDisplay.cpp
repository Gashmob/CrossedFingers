/*
 * MIT License
 *
 * Copyright (c) 2025-Present Kevin Traini
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "crossedfingers/internals/display/DefaultDisplay.h"

#include "crossedfingers/internals/display/OutputWrapper.h"

#include <format>

using namespace crossedfingers::internals;

auto DefaultDisplay::printBeginSuite(const std::string &suite_name) -> void {
    // Nothing to do
}

auto DefaultDisplay::printBeginCase(const std::string &case_name) -> void {
    OutputWrapper::print(std::format(" > {} - ", case_name));
}

auto DefaultDisplay::printEndCase(const std::string &case_name) -> void {
    OutputWrapper::print("SUCCESS\n");
}

auto DefaultDisplay::printEndSuite(const std::string &suite_name) -> void {
    // Nothing to do
}

auto DefaultDisplay::printSkipCase(const std::string &case_name) -> void {
    OutputWrapper::print("SKIP\n");
}

auto DefaultDisplay::printWarningCase(const std::string &case_name) -> void {
    OutputWrapper::print("WARNING\n");
}

auto DefaultDisplay::printFailCase(const std::string &case_name, const std::string &message) -> void {
    OutputWrapper::print(std::format("FAILURE\n    {}\n", message));
}

auto DefaultDisplay::printSummary(
    int test_count,
    int assertion_count,
    const std::vector<std::string> &succeed_tests,
    const std::vector<std::string> &skipped_tests,
    const std::map<std::string, std::string> &warning_tests,
    const std::map<std::string, std::string> &failed_tests
) -> void {
    OutputWrapper::print(std::format(
        R"(
    TEST COUNT: {}
    SUCCESS: {}
    SKIP: {}
    WARNING: {}
    FAILURES: {}
    TOTAL ASSERTIONS: {}

)",
        test_count,
        succeed_tests.size(),
        skipped_tests.size(),
        warning_tests.size(),
        failed_tests.size(),
        assertion_count
    ));

    if (! warning_tests.empty()) {
        OutputWrapper::print("Warning tests:\n\n");
        for (const auto &[test_name, message] : warning_tests) {
            OutputWrapper::print(std::format("  {}\n    {}\n\n", test_name, message));
        }
    }

    if (! failed_tests.empty()) {
        OutputWrapper::print("Failed tests:\n\n");
        for (const auto &[test_name, message] : failed_tests) {
            OutputWrapper::print(std::format("  {}\n    {}\n\n", test_name, message));
        }
    }
}
