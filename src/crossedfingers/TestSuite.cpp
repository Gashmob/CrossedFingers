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
#include "crossedfingers/TestSuite.h"

#include "crossedfingers/GlobalState.h"
#include "crossedfingers/TestStatus.h"
#include "crossedfingers/assert/AssertionException.h"
#include "utils.hpp"

#include <format>
#include <random>
#include <utility>

using namespace crossedfingers;

TestSuite::TestSuite(std::string name): _name(std::move(name)), _before(std::nullopt) {}

auto TestSuite::addSubSuite(const std::string &name) -> TestSuite * {
    auto &test_suite = _sub_suites.emplace_back(name);
    return &test_suite;
}

auto TestSuite::addTestCase(const std::string &name, const std::function<void()> &callback) -> void {
    _test_cases.emplace_back(name, callback);
}

auto TestSuite::setBefore(const std::function<void()> &callback) -> void {
    if (_before.has_value()) {
        throw std::logic_error("Cannot setup two before() in the same test suite");
    }

    _before = callback;
}

auto TestSuite::setBeforeEach(const std::function<void()> &callback) -> void {
    if (_before_each.has_value()) {
        throw std::logic_error("Cannot setup two beforeEach() in the same test suite");
    }

    _before_each = callback;
}

auto TestSuite::setAfter(const std::function<void()> &callback) -> void {
    if (_after.has_value()) {
        throw std::logic_error("Cannot setup two after() in the same test suite");
    }

    _after = callback;
}

auto TestSuite::setAfterEach(const std::function<void()> &callback) -> void {
    if (_after_each.has_value()) {
        throw std::logic_error("Cannot setup two afterEach() in the same test suite");
    }

    _after_each = callback;
}

auto TestSuite::run(const std::string &current_name) -> void {
    const auto suite_fullname = (current_name.empty() ? "" : current_name + ".") + _name;
    if (! matchPattern(suite_fullname, GlobalState::filter)) {
        return;
    }

    TestStatus::instance().beginSuite(suite_fullname);

    if (_before.has_value()) {
        _before.value()();
    }

    std::mt19937_64 generator(GlobalState::random_seed);
    std::shuffle(_sub_suites.begin(), _sub_suites.end(), generator);
    for (auto &suite : _sub_suites) {
        if (_before_each.has_value()) {
            _before_each.value()();
        }

        suite.run(suite_fullname);

        if (_after_each.has_value()) {
            _after_each.value()();
        }
    }

    std::shuffle(_test_cases.begin(), _test_cases.end(), generator);
    for (const auto &test_case : _test_cases) {
        if (_before_each.has_value()) {
            _before_each.value()();
        }

        try {
            test_case.run(suite_fullname);
        } catch (SkipException &) {
            TestStatus::instance().skip();
        } catch (AssertionException &failure) {
            TestStatus::instance().failure(failure._message);
        } catch (const std::exception &exception) {
            TestStatus::instance().failure(std::format("Uncaught exception: {}", exception.what()));
        }

        if (_after_each.has_value()) {
            _after_each.value()();
        }
    }

    if (_after.has_value()) {
        _after.value()();
    }

    TestStatus::instance().endSuite();
}

auto TestSuite::list(const std::string &current_name) const -> void {
    const auto suite_fullname = (current_name.empty() ? "" : current_name + ".") + _name;

    for (const auto &suite : _sub_suites) {
        suite.list(suite_fullname);
    }

    for (const auto &test_case : _test_cases) {
        test_case.list(suite_fullname);
    }
}
