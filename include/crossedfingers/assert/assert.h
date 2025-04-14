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
#ifndef ASSERT_H
#define ASSERT_H
/**
 * Collection of assertions
 */

#include "Assertion.h"

#define skip() crossedfingers::Assertion::_skip()

#define fail(message) crossedfingers::Assertion::_fail(message)

#define assertTrue(value) assertEquals(true, value)

#define assertFalse(value) assertEquals(false, value)

#define assertEquals(expected, value) crossedfingers::Assertion::_assertEquals(expected, value)

#define assertSame(expected, value) crossedfingers::Assertion::_assertSame(expected, value)

#define assertNotEquals(expected, value) crossedfingers::Assertion::_assertNotEquals(expected, value)

#define assertLessThan(expected, value) crossedfingers::Assertion::_assertLessThan(expected, value)

#define assertLessThanOrEquals(expected, value) crossedfingers::Assertion::_assertLessThanOrEquals(expected, value)

#define assertGreaterThan(expected, value) crossedfingers::Assertion::_assertGreaterThan(expected, value)

#define assertGreaterThanOrEquals(expected, value) crossedfingers::Assertion::_assertGreaterThanOrEquals(expected, value)

#define assertThrow(expression, exception)                            \
    crossedfingers::Assertion::_assertThrow<exception>([]() -> void { \
        expression;                                                   \
    })

#define assertNotThrow(expression)                            \
    crossedfingers::Assertion::_assertNotThrow([]() -> void { \
        expression;                                           \
    })

#endif // ASSERT_H
