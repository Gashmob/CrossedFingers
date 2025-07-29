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
#include "crossedfingers/internals/TestStatus.h"

#include "crossedfingers/internals/assert/Assertion.h"
#include "crossedfingers/utilities.h"

#include <stdexcept>

using namespace crossedfingers::internals;

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
    _awaited_exception         = std::nullopt;
    _awaited_exception_message = std::nullopt;
}

auto TestStatus::beginCase(const std::string &test_case) -> void {
    if (_current_case.has_value()) {
        throw std::logic_error("Already in a test case, this should not be the case");
    }

    _display->printBeginCase(test_case);
    _current_case              = test_case;
    _awaited_exception         = std::nullopt;
    _awaited_exception_message = std::nullopt;
    _test_count++;
}

auto TestStatus::endCase() -> void {
    if (! _current_case.has_value()) {
        // The test was probably skipped or failed
        return;
    }

    if (_current_assertion_count == 0) {
        warning("Test did not perform any assertions");
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
    _skipped_tests.push_back(_current_case.value());

    _display->printSkipCase(_current_case.value());
    _current_case = std::nullopt;
}

auto TestStatus::warning(const std::string &message) -> void {
    if (! _current_case.has_value()) {
        throw std::logic_error("Not in a test case, should be the case");
    }

    _assertion_count += _current_assertion_count;
    _current_assertion_count = 0;
    _warning_tests.emplace(_current_case.value(), message);

    _display->printWarningCase(_current_case.value());
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

auto TestStatus::checkAwaitedException(const std::exception &exception) const -> void {
    if (! _awaited_exception.has_value()) {
        throw;
    }

    if (typeid(exception) != *_awaited_exception.value()) {
        Assertion::_fail(
            "Awaited for " + getTypeName(_awaited_exception.value()) + " exception but got " + getTypeName(exception)
        );
    }

    if (_awaited_exception_message.has_value()
        && ! std::string(exception.what()).contains(_awaited_exception_message.value())) {
        Assertion::_fail(
            "Exception message doesn't contains '" + _awaited_exception_message.value() + "', got '"
            + std::string(exception.what()) + "'."
        );
    }

    Assertion::success();
}

auto TestStatus::summary() const -> void {
    _display->printSummary(
        _test_count, _assertion_count, _succeed_tests, _skipped_tests, _warning_tests, _failed_tests
    );
}

auto TestStatus::returnValue() const noexcept -> int {
    return ! _failed_tests.empty();
}
