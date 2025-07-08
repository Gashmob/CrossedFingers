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

#include "crossedfingers/TestStatus.h"
#include "crossedfingers/assert/AssertionException.h"

#include <format>
#include <utility>

using namespace crossedfingers;

TestSuite::TestSuite(std::string name): _name(std::move(name)) {}

auto TestSuite::addSubSuite(const std::string &name) -> TestSuite * {
    auto test_suite = std::make_shared<TestSuite>(name);
    _sub_suites.emplace_back(test_suite);
    return test_suite.get();
}

auto TestSuite::addTestCase(const std::string &name, const std::function<void()> &callback) -> void {
    _test_cases.emplace_back(std::make_unique<TestCase>(name, callback));
}

auto TestSuite::run(const std::string &current_name) const -> void {
    const auto suite_fullname = (current_name.empty() ? "" : current_name + ".") + _name;
    TestStatus::instance().beginSuite(suite_fullname);

    for (const auto &suite : _sub_suites) {
        suite->run(suite_fullname);
    }

    for (const auto &test_case : _test_cases) {
        try {
            test_case->run(suite_fullname);
        } catch (SkipException &) {
            TestStatus::instance().skip();
        } catch (AssertionException &failure) {
            TestStatus::instance().failure(failure._message);
        } catch (const std::exception &exception) {
            TestStatus::instance().failure(std::format("Uncaught exception: {}", exception.what()));
        }
    }

    TestStatus::instance().endSuite();
}

auto TestSuite::list(const std::string &current_name) const -> void {
    const auto suite_fullname = (current_name.empty() ? "" : current_name + ".") + _name;

    for (const auto &suite : _sub_suites) {
        suite->list(suite_fullname);
    }

    for (const auto &test_case : _test_cases) {
        test_case->list(suite_fullname);
    }
}
