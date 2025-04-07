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
#ifndef TESTSTATUS_H
#define TESTSTATUS_H
/**
 * Current status of whole tests
 */

#include "display/Display.h"

#include <map>
#include <optional>
#include <stack>
#include <string>
#include <vector>

namespace crossedfingers {
class TestStatus final {
  public:
    static auto instance() -> TestStatus &;

    auto setDisplay(Display *display) -> void;

    auto beginSuite(const std::string &test_suite) -> void;

    auto beginCase(const std::string &test_case) -> void;

    auto endCase() -> void;

    auto endSuite() -> void;

    auto success() -> void;

    auto skip() -> void;

    auto failure(const std::string &message) -> void;

    auto summary() const -> void;

    [[nodiscard]] auto returnValue() const noexcept -> int;

  private:
    int _test_count              = 0;
    int _assertion_count         = 0;
    int _current_assertion_count = 0;
    std::vector<std::string> _succeed_tests;
    std::vector<std::string> _skipped_tests;
    std::map<std::string, std::string> _failed_tests;

    std::stack<std::string> _current_suite;
    std::optional<std::string> _current_case = std::nullopt;
    Display *_display = nullptr;
};
} // namespace crossedfingers

#endif // TESTSTATUS_H
