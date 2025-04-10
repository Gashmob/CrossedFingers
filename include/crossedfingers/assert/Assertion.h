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
#ifndef ASSERTION_H
#define ASSERTION_H
/**
 * Assertion class, it contains assertions logic
 */

#include <format>
#include <functional>
#include <string>

/**
 * TODO list:
 * - [x] true
 * - [x] false
 * - [x] equals
 * - [x] same
 * - [x] notEquals
 * - [x] lessThan
 * - [x] lessThanOrEquals
 * - [x] greaterThan
 * - [x] greaterThanOrEquals
 * - [x] throw
 * - [x] notThrow
 * - [ ] exit
 * - [ ] matchesRegex
 * - [ ] hasSubString
 * - [ ] startsWith
 * - [ ] endsWith
 * - [ ] contains
 * - [ ] containsKey
 * - [ ] equalsCanonicalizing
 * - [ ] count
 * - [ ] isEmpty
 * - [ ] isSorted
 * - [ ] pair
 * - [ ] predicate
 * - [ ] type
 * - [ ] null
 * - [ ] fileExists
 * - [ ] directoryExists
 */

namespace crossedfingers {
class Assertion final {
  public:
    [[noreturn]] static auto _skip() -> void;

    [[noreturn]] static auto _fail(const std::string &message) -> void;

    template<typename Expected, typename Value>
    static auto _assertEquals(const Expected &expected, const Value &value) -> void {
        if (value != expected) {
            _fail("Failed asserting that operands are equals");
        }
        success();
    }

    template<typename Expected, typename Value>
    static auto _assertSame(const Expected &expected, const Value &value) -> void {
        if (typeid(value) != typeid(expected)) {
            _fail("Failed asserting that operands are same (don't have the same type)");
        }

        if (value != expected) {
            _fail("Failed asserting that operands are same");
        }
        success();
    }

    template<typename Expected, typename Value>
    static auto _assertNotEquals(const Expected &expected, const Value &value) -> void {
        if (value == expected) {
            _fail("Failed asserting that operands are not equals");
        }
        success();
    }

    template<typename Expected, typename Value>
    static auto _assertLessThan(const Expected &expected, const Value &value) -> void {
        if (value >= expected) {
            _fail("Failed asserting that value is less than expected");
        }
        success();
    }

    template<typename Expected, typename Value>
    static auto _assertLessThanOrEquals(const Expected &expected, const Value &value) -> void {
        if (value > expected) {
            _fail("Failed asserting that value is less than or equals expected");
        }
        success();
    }

    template<typename Expected, typename Value>
    static auto _assertGreaterThan(const Expected &expected, const Value &value) -> void {
        if (value <= expected) {
            _fail("Failed asserting that value is greater than expected");
        }
        success();
    }

    template<typename Expected, typename Value>
    static auto _assertGreaterThanOrEquals(const Expected &expected, const Value &value) -> void {
        if (value < expected) {
            _fail("Failed asserting that value is greater than or equals expected");
        }
        success();
    }

    template<typename Exception> static auto _assertThrow(const std::function<void()> &expression) -> void {
        try {
            expression();
            _fail(std::format("Expression didn't throw {}", typeid(Exception).name()));
        } catch (const Exception &) {
            success();
        } catch (const std::exception &exception) {
            _fail(std::format("Expression didn't throw {} but {}", typeid(Exception).name(), typeid(exception).name()));
        }
    }

    static auto _assertNotThrow(const std::function<void()> &expression) -> void {
        try {
            expression();
            success();
        } catch (const std::exception &exception) {
            _fail(std::format("Expression throws {}", typeid(exception).name()));
        }
    }

  private:
    Assertion() = default;

    ~Assertion() = default;

    static auto success() noexcept -> void;
};
} // namespace crossedfingers

#endif // ASSERTION_H
