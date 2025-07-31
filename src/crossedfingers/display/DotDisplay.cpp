/**
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
#include "crossedfingers/internals/display/DotDisplay.h"

#include "crossedfingers/internals/display/OutputWrapper.h"

#include <format>

using namespace crossedfingers::internals;

auto DotDisplay::printBeginSuite(const std::string &suite_name) -> void {
    (void) suite_name;
    // Nothing to do;
}

auto DotDisplay::printBeginCase(const std::string &case_name) -> void {
    (void) case_name;
    // Nothing to do;
}

auto DotDisplay::printEndCase(const std::string &case_name) -> void {
    (void) case_name;
    OutputWrapper::print(".");
}

auto DotDisplay::printEndSuite(const std::string &suite_name) -> void {
    (void) suite_name;
    // Nothing to do;
}

auto DotDisplay::printSkipCase(const std::string &case_name) -> void {
    (void) case_name;
    OutputWrapper::print("S");
}

auto DotDisplay::printWarningCase(const std::string &case_name) -> void {
    (void) case_name;
    OutputWrapper::print("\033[33mW\033[0m");
}

auto DotDisplay::printFailCase(const std::string &case_name, const std::string &message) -> void {
    (void) case_name;
    (void) message;
    OutputWrapper::print("\033[41mF\033[0m");
}

auto DotDisplay::printSummary(
    int test_count,
    int assertion_count,
    const std::vector<std::string> &succeed_tests,
    const std::vector<std::string> &skipped_tests,
    const std::map<std::string, std::string> &warning_tests,
    const std::map<std::string, std::string> &failed_tests
) -> void {
    (void) test_count;
    (void) assertion_count;
    (void) skipped_tests;

    OutputWrapper::print(
        std::format("\n\n{} tests passed, {} tests fails\n\n", succeed_tests.size(), failed_tests.size())
    );

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
