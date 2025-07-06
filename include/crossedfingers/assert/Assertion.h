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

#include "AssertionException.h"
#include "crossedfingers/TestStatus.h"
#include "crossedfingers/utils.h"

#include <any>
#include <filesystem>
#include <list>
#include <regex>
#include <set>
#include <string>

namespace crossedfingers {
class Assertion final {
  public:
    [[noreturn]] static auto _skip() -> void;

    [[noreturn]] static auto _fail(const std::string &message) -> void;

    static auto success() noexcept -> void;

  private:
    Assertion() = default;

    ~Assertion() = default;
};

template<typename ActualType> class AssertionMatcher final {
  public:
    explicit AssertionMatcher(const ActualType &actual): _actual(std::move(actual)) {}

    auto isTrue() const -> void {
        isEqualTo(true);
    }

    auto isFalse() const -> void {
        isEqualTo(false);
    }

    template<typename ExpectedType> auto isEqualTo(const ExpectedType &expected) const -> void {
        if (_actual != expected) {
            Assertion::_fail("Failed asserting that actual value is equal to expected.");
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isStrictEqualTo(const ExpectedType &expected) const -> void {
        if (typeid(_actual) != typeid(expected)) {
            Assertion::_fail(
                "Failed asserting that actual value is strict equal to expected, they don't have the same type."
            );
        }
        if (_actual != expected) {
            Assertion::_fail("Failed asserting that actual value is equal to expected.");
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isNotEqualTo(const ExpectedType &expected) const -> void {
        if (_actual == expected) {
            Assertion::_fail("Failed asserting that actual value is not equal to expected.");
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isLessThan(const ExpectedType &expected) const -> void {
        if (_actual >= expected) {
            Assertion::_fail("Failed asserting that actual value is less than expected.");
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isLessThanOrEqualTo(const ExpectedType &expected) const -> void {
        if (_actual > expected) {
            Assertion::_fail("Failed asserting that actual value is less than or equal to expected.");
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isGreaterThan(const ExpectedType &expected) const -> void {
        if (_actual <= expected) {
            Assertion::_fail("Failed asserting that actual value is greater than expected.");
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isGreaterThanOrEqualTo(const ExpectedType &expected) const -> void {
        if (_actual < expected) {
            Assertion::_fail("Failed asserting that actual value is greater than or equal to expected.");
        }
        Assertion::success();
    }

    auto matchesRegex(const std::string &pattern) const -> void {
        Assertion::_fail("Cannot match a regex against a '" + getTypeName<ActualType>() + "'.");
    }

    auto hasSubString(const std::string &sub) const -> void {
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' has a sub string.");
    }

    auto startsWith(const std::string &start) const -> void {
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' starts with a string.");
    }

    auto endsWith(const std::string &end) const -> void {
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' ends with a string.");
    }

    template<typename ContainedType> auto contains(const ContainedType &contained) const -> void {
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' contains something.");
    }

    template<typename KeyType> auto hasKey(const KeyType &key) const -> void {
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' has some key.");
    }

    auto count(int number) const -> void {
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' has N elements.");
    }

    auto isEmpty() const -> void {
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' is empty.");
    }

    auto matchPredicate(const std::function<bool(const ActualType &)> predicate) const -> void {
        if (! predicate(_actual)) {
            Assertion::_fail("Predicate returned false.");
        }

        Assertion::success();
    }

    template<typename ExpectedType> auto matchType() const -> void {
        if (typeid(_actual) != typeid(ExpectedType)) {
            Assertion::_fail(
                "Failed asserting that actual type '" + std::string(typeid(_actual).name()) + "' matches expected '"
                + std::string(typeid(ExpectedType).name()) + "'."
            );
        }
        Assertion::success();
    }

    auto isNull() const -> void {
        isEqualTo(nullptr);
    }

    auto isFile() const -> void {
        Assertion::_fail("Need a valid std::string to check if it exists.");
    }

    auto isDirectory() const -> void {
        Assertion::_fail("Need a valid std::string to check if it exists.");
    }

  private:
    const ActualType _actual;
};

template<> inline auto AssertionMatcher<std::string>::matchesRegex(const std::string &pattern) const -> void {
    const std::regex regex(pattern);
    if (! std::regex_match(_actual, regex)) {
        Assertion::_fail("'" + _actual + "' doesn't match '" + pattern + "'.");
    }

    Assertion::success();
}

template<> inline auto AssertionMatcher<std::string>::hasSubString(const std::string &sub) const -> void {
    if (! std::string(_actual).contains(sub)) {
        Assertion::_fail("Failed asserting that '" + std::string(_actual) + "' contains '" + sub + "'");
    }

    Assertion::success();
}

template<> inline auto AssertionMatcher<std::string>::startsWith(const std::string &start) const -> void {
    if (! std::string(_actual).starts_with(start)) {
        Assertion::_fail("Failed asserting that '" + std::string(_actual) + "' starts with '" + start + "'");
    }

    Assertion::success();
}

template<> inline auto AssertionMatcher<std::string>::endsWith(const std::string &end) const -> void {
    if (! std::string(_actual).ends_with(end)) {
        Assertion::_fail("Failed asserting that '" + std::string(_actual) + "' ends with '" + end + "'");
    }

    Assertion::success();
}

#define AssertionMatcher_contains(ContainerType)                                                                  \
    template<typename ContainedType> class AssertionMatcher<ContainerType<ContainedType>> {                       \
      public:                                                                                                     \
        explicit AssertionMatcher(const ContainerType<ContainedType> &actual): _actual(std::move(actual)) {}      \
                                                                                                                  \
        auto contains(const ContainedType &contained) const -> void {                                             \
            if (std::find(_actual.begin(), _actual.end(), contained) == _actual.end()) {                          \
                Assertion::_fail("Failed asserting that container contains value");                               \
            }                                                                                                     \
                                                                                                                  \
            Assertion::success();                                                                                 \
        }                                                                                                         \
                                                                                                                  \
        auto count(int number) const -> void {                                                                    \
            if (_actual.size() != number) {                                                                       \
                Assertion::_fail("Failed asserting that container has " + std::to_string(number) + " elements."); \
            }                                                                                                     \
                                                                                                                  \
            Assertion::success();                                                                                 \
        }                                                                                                         \
                                                                                                                  \
        auto isEmpty() const -> void {                                                                            \
            if (! _actual.empty()) {                                                                              \
                Assertion::_fail("Failed asserting that container is empty.");                                    \
            }                                                                                                     \
                                                                                                                  \
            Assertion::success();                                                                                 \
        }                                                                                                         \
                                                                                                                  \
      private:                                                                                                    \
        const ContainerType<ContainedType> _actual;                                                               \
    }

AssertionMatcher_contains(std::vector);

AssertionMatcher_contains(std::deque);

AssertionMatcher_contains(std::list);

AssertionMatcher_contains(std::set);

template<typename ContainedType, std::size_t Size> class AssertionMatcher<std::array<ContainedType, Size>> {
  public:
    explicit AssertionMatcher(const std::array<ContainedType, Size> &actual): _actual(std::move(actual)) {}

    auto contains(const ContainedType &contained) const -> void {
        if (std::find(_actual.begin(), _actual.end(), contained) == _actual.end()) {
            Assertion::_fail("Failed asserting that container contains value");
        }

        Assertion::success();
    }

  private:
    const std::array<ContainedType, Size> _actual;
};

template<typename KeyType, typename ValueType> class AssertionMatcher<std::map<KeyType, ValueType>> {
  public:
    explicit AssertionMatcher(const std::map<KeyType, ValueType> &actual): _actual(std::move(actual)) {}

    auto hasKey(const KeyType &key) const -> void {
        if (! _actual.contains(key)) {
            Assertion::_fail("Failed asserting that map contains key");
        }

        Assertion::success();
    }

  private:
    const std::map<KeyType, ValueType> _actual;
};

template<> inline auto AssertionMatcher<std::string>::isFile() const -> void {
    if (! std::filesystem::is_regular_file(_actual)) {
        Assertion::_fail("File '" + _actual + "' not found.");
    }

    Assertion::success();
}

template<> inline auto AssertionMatcher<std::string>::isDirectory() const -> void {
    if (! std::filesystem::is_directory(_actual)) {
        Assertion::_fail("File '" + _actual + "' not found.");
    }

    Assertion::success();
}
} // namespace crossedfingers

#endif // ASSERTION_H
