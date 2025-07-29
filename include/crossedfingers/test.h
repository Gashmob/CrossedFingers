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
#ifndef TEST_H
#define TEST_H
/**
 * Main header file. It includes all sub-headers and define macros
 */

#include "./assert.h"
#include "internals/TestRun.h"

#include <format>

#define describe(name, ...) \
    [[maybe_unused]] const auto t_##name = crossedfingers::internals::TestRun::instance().addSuite(#name, __VA_ARGS__)

inline auto skip() -> void {
    crossedfingers::internals::Assertion::_skip();
}

inline auto fail(const std::string &message) -> void {
    crossedfingers::internals::Assertion::_fail(message);
}

inline auto it(const std::string &name, const std::function<void()> &callback) -> void {
    crossedfingers::internals::TestRun::instance().addCase(name, callback);
}

template<typename Callback, typename... Args>
auto it_each(
    const std::vector<std::tuple<Args...>> &args_list, const std::string &template_name, const Callback *callback
) -> void {
    for (const auto &args : args_list) {
        const auto name = std::apply(
            [&template_name](auto &&...format_args) {
                return std::vformat(template_name, std::make_format_args(format_args...));
            },
            args
        );
        crossedfingers::internals::TestRun::instance().addParameterizedCase(name, args, callback);
    }
}

inline auto before(const std::function<void()> &callback) -> void {
    crossedfingers::internals::TestRun::instance().addBefore(callback);
}

inline auto beforeEach(const std::function<void()> &callback) -> void {
    crossedfingers::internals::TestRun::instance().addBeforeEach(callback);
}

inline auto after(const std::function<void()> &callback) -> void {
    crossedfingers::internals::TestRun::instance().addAfter(callback);
}

inline auto afterEach(const std::function<void()> &callback) -> void {
    crossedfingers::internals::TestRun::instance().addAfterEach(callback);
}

#endif // TEST_H
