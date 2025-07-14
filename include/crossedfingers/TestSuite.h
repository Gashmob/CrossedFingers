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
#ifndef TESTSUITE_H
#define TESTSUITE_H
/**
 * Holds test cases
 */

#include "TestCase.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace crossedfingers {
class TestSuite final {
  public:
    explicit TestSuite(std::string name);

    auto addSubSuite(const std::string &name) -> TestSuite *;

    auto addTestCase(const std::string &name, const std::function<void()> &callback) -> void;

    auto setBefore(const std::function<void()> &callback) -> void;

    auto setBeforeEach(const std::function<void()> &callback) -> void;

    auto setAfter(const std::function<void()> &callback) -> void;

    auto run(const std::string &current_name) -> void;

    auto list(const std::string &current_name) const -> void;

  private:
    std::string _name;
    std::optional<std::function<void()>> _before;
    std::optional<std::function<void()>> _before_each;
    std::optional<std::function<void()>> _after;
    std::vector<TestSuite> _sub_suites;
    std::vector<TestCase> _test_cases;
};
} // namespace crossedfingers

#endif // TESTSUITE_H
