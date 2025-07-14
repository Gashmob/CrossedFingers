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

#include "TestRun.h"
#include "assert/assert.h"

#define describe(name, callback) \
    [[maybe_unused]] const auto t_##name = crossedfingers::TestRun::instance().addSuite(#name, callback)

inline auto it(const std::string &name, const std::function<void()> &callback) -> void {
    crossedfingers::TestRun::instance().addCase(name, callback);
}

inline auto before(const std::function<void()> &callback) -> void {
    crossedfingers::TestRun::instance().addBefore(callback);
}

inline auto beforeEach(const std::function<void()> &callback) -> void {
    crossedfingers::TestRun::instance().addBeforeEach(callback);
}

inline auto after(const std::function<void()> &callback) -> void {
    crossedfingers::TestRun::instance().addAfter(callback);
}

#endif // TEST_H
