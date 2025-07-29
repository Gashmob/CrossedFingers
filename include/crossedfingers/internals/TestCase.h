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
#ifndef TESTCASE_H
#define TESTCASE_H
/**
 * A test itself
 */
#include "GlobalState.h"
#include "TestStatus.h"
#include "assert/AssertionException.h"
#include "utils.hpp"

#include <format>
#include <functional>
#include <string>

namespace crossedfingers::internals {
class TestCase {
  public:
    TestCase(std::string name, const std::function<void()> &callback);

    virtual ~TestCase() = default;

    virtual auto run(const std::string &current_name) const -> void;

    auto list(const std::string &current_name) const -> void;

  protected:
    std::string _name;
    std::function<void()> _callback;
};

template<typename Callback, typename... Args> class ParameterizedTestCase final : public TestCase {
  public:
    ParameterizedTestCase(const std::string &name, const std::tuple<Args...> &args, const Callback &callback)
        : TestCase(name, []() {}), _args(args), _parameterized_callback(callback) {}

    auto run(const std::string &current_name) const -> void override {
        const auto test_fullname = current_name + "::" + _name;
        if (! matchPattern(test_fullname, GlobalState::filter)) {
            return;
        }

        TestStatus::instance().beginCase(test_fullname);
        try {
            try {
                std::apply(_parameterized_callback, _args);
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

  private:
    std::tuple<Args...> _args;
    Callback _parameterized_callback;
};
} // namespace crossedfingers

#endif // TESTCASE_H
