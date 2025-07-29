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
#include "crossedfingers/internals/TestCase.h"

#include "crossedfingers/internals/display/OutputWrapper.h"

#include <utility>

using namespace crossedfingers::internals;

TestCase::TestCase(std::string name, const std::function<void()> &callback)
    : _name(std::move(name)), _callback(callback) {}

auto TestCase::run(const std::string &current_name) const -> void {
    const auto test_fullname = current_name + "::" + _name;
    if (! matchPattern(test_fullname, GlobalState::filter)) {
        return;
    }

    TestStatus::instance().beginCase(test_fullname);
    try {
        try {
            _callback();
        } catch (const std::exception &exception) {
            TestStatus::instance().checkAwaitedException(exception);
        }
    } catch (SkipException &) {
        TestStatus::instance().skip();
    } catch (AssertionException &failure) {
        TestStatus::instance().failure(failure._message);
    } catch (const std::exception &exception) {
        TestStatus::instance().failure(std::format("Uncaught exception: {}", exception.what()));
    }
    TestStatus::instance().endCase();
}

auto TestCase::list(const std::string &current_name) const -> void {
    OutputWrapper::print(current_name + "::" + _name + "\n");
}
