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
#include "crossedfingers/TestStatus.h"

#include <stdexcept>

using namespace crossedfingers;

auto TestStatus::instance() -> TestStatus & {
    static TestStatus instance;
    return instance;
}

auto TestStatus::setDisplay(Display *display) -> void {
    _display = display;
}

auto TestStatus::beginSuite(const std::string &test_suite) -> void {
    _display->printBeginSuite(test_suite);
    _current_suite.push(test_suite);
}

auto TestStatus::beginCase(const std::string &test_case) -> void {
    if (_current_case.has_value()) {
        throw std::logic_error("Already in a test case, this should not be the case");
    }

    _display->printBeginCase(test_case);
    _current_case = test_case;
    _test_count++;
}

auto TestStatus::endCase() -> void {
    if (! _current_case.has_value()) {
        // Test was probably skipped or failed
        return;
    }

    _assertion_count += _current_assertion_count;
    _current_assertion_count = 0;
    _succeed_tests.push_back(_current_case.value());

    _display->printEndCase(_current_case.value());
    _current_case = std::nullopt;
}

auto TestStatus::endSuite() -> void {
    if (_current_suite.empty()) {
        throw std::logic_error("Not in a test suite, should be the case");
    }

    const auto suite = _current_suite.top();
    _current_suite.pop();
    _display->printEndSuite(suite);
}

auto TestStatus::success() -> void {
    if (! _current_case.has_value()) {
        throw std::logic_error("Not in a test case, should be the case");
    }

    _current_assertion_count++;
}

auto TestStatus::skip() -> void {
    if (! _current_case.has_value()) {
        throw std::logic_error("Not in a test case, should be the case");
    }

    _assertion_count += _current_assertion_count;
    _current_assertion_count = 0;
    _succeed_tests.push_back(_current_case.value());

    _display->printSkipCase(_current_case.value());
    _current_case = std::nullopt;
}

auto TestStatus::failure(const std::string &message) -> void {
    if (! _current_case.has_value()) {
        throw std::logic_error("Not in a test case, should be the case");
    }

    _assertion_count += _current_assertion_count;
    _current_assertion_count = 0;
    _failed_tests.emplace(_current_case.value(), message);

    _display->printFailCase(_current_case.value(), message);
    _current_case = std::nullopt;
}

auto TestStatus::summary() const -> void {
    _display->printSummary(_test_count, _assertion_count, _succeed_tests, _skipped_tests, _failed_tests);
}

auto TestStatus::returnValue() const noexcept -> int {
    return ! _failed_tests.empty();
}
