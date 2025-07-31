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

#include "../../utilities.h"
#include "../TestStatus.h"
#include "AssertionException.h"
#include "Diff.h"

#include <any>
#include <filesystem>
#include <list>
#include <regex>
#include <set>
#include <string>

namespace crossedfingers::internals {
class Assertion final {
  public:
    [[noreturn]] static auto _skip() -> void;

    [[noreturn]] static auto _fail(const std::string &message) -> void;

    static auto success() noexcept -> void;

  private:
    Assertion() = default;

    ~Assertion() = default;
};

template<typename ActualType> class AssertionMatcherBase {
  public:
    explicit AssertionMatcherBase(const ActualType &actual): _actual(std::move(actual)) {}

    auto isTrue() const -> void {
        isEqualTo(true);
    }

    auto isFalse() const -> void {
        isEqualTo(false);
    }

    template<typename ExpectedType> auto isEqualTo(const ExpectedType &expected) const -> void {
        if (_actual != expected) {
            Assertion::_fail("Failed asserting that actual value is equal to expected.\n" + diff(expected, _actual));
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isStrictEqualTo(const ExpectedType &expected) const -> void {
        if (typeid(_actual) != typeid(expected)) {
            Assertion::_fail(
                "Failed asserting that actual value is strict equal to expected, they don't have the same type.\n"
                + diff(getTypeName(expected), getTypeName(_actual))
            );
        }
        if (_actual != expected) {
            Assertion::_fail("Failed asserting that actual value is equal to expected.\n" + diff(expected, _actual));
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isNotEqualTo(const ExpectedType &expected) const -> void {
        if (_actual == expected) {
            Assertion::_fail(
                "Failed asserting that actual value is not equal to expected.\n" + diff(expected, _actual)
            );
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isLessThan(const ExpectedType &expected) const -> void {
        if (_actual >= expected) {
            Assertion::_fail("Failed asserting that actual value is less than expected.\n" + diff(expected, _actual));
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isLessThanOrEqualTo(const ExpectedType &expected) const -> void {
        if (_actual > expected) {
            Assertion::_fail(
                "Failed asserting that actual value is less than or equal to expected.\n" + diff(expected, _actual)
            );
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isGreaterThan(const ExpectedType &expected) const -> void {
        if (_actual <= expected) {
            Assertion::_fail(
                "Failed asserting that actual value is greater than expected.\n" + diff(expected, _actual)
            );
        }
        Assertion::success();
    }

    template<typename ExpectedType> auto isGreaterThanOrEqualTo(const ExpectedType &expected) const -> void {
        if (_actual < expected) {
            Assertion::_fail(
                "Failed asserting that actual value is greater than or equal to expected.\n" + diff(expected, _actual)
            );
        }
        Assertion::success();
    }

    auto matchesRegex(const std::string &pattern) const -> void {
        (void) pattern;
        Assertion::_fail("Cannot match a regex against a '" + getTypeName<ActualType>() + "'.");
    }

    auto hasSubString(const std::string &sub) const -> void {
        (void) sub;
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' has a sub string.");
    }

    auto startsWith(const std::string &start) const -> void {
        (void) start;
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' starts with a string.");
    }

    auto endsWith(const std::string &end) const -> void {
        (void) end;
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' ends with a string.");
    }

    template<typename ContainedType> auto contains(const ContainedType &contained) const -> void {
        (void) contained;
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' contains something.");
    }

    template<typename KeyType> auto hasKey(const KeyType &key) const -> void {
        (void) key;
        Assertion::_fail("Cannot check that a '" + getTypeName<ActualType>() + "' has some key.");
    }

    auto count(const unsigned int number) const -> void {
        (void) number;
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

  protected:
    const ActualType _actual;
};

template<typename ActualType> class AssertionMatcher final : public AssertionMatcherBase<ActualType> {
  public:
    explicit AssertionMatcher(const ActualType &actual): AssertionMatcherBase<ActualType>(actual) {}
};

template<> inline auto AssertionMatcherBase<std::string>::matchesRegex(const std::string &pattern) const -> void {
    const std::regex regex(pattern);
    if (! std::regex_match(_actual, regex)) {
        Assertion::_fail("'" + _actual + "' doesn't match '" + pattern + "'.");
    }

    Assertion::success();
}

template<> inline auto AssertionMatcherBase<std::string>::hasSubString(const std::string &sub) const -> void {
    if (! _actual.contains(sub)) {
        Assertion::_fail("Failed asserting that '" + _actual + "' contains '" + sub + "'");
    }

    Assertion::success();
}

template<> inline auto AssertionMatcherBase<std::string>::startsWith(const std::string &start) const -> void {
    if (! _actual.starts_with(start)) {
        Assertion::_fail("Failed asserting that '" + _actual + "' starts with '" + start + "'");
    }

    Assertion::success();
}

template<> inline auto AssertionMatcherBase<std::string>::endsWith(const std::string &end) const -> void {
    if (! _actual.ends_with(end)) {
        Assertion::_fail("Failed asserting that '" + _actual + "' ends with '" + end + "'");
    }

    Assertion::success();
}

#define AssertionMatcher_contains(ContainerType)                                                                       \
    template<typename ContainedType>                                                                                   \
    class AssertionMatcher<ContainerType<ContainedType>> : public AssertionMatcherBase<ContainerType<ContainedType>> { \
      public:                                                                                                          \
        explicit AssertionMatcher(const ContainerType<ContainedType> &actual)                                          \
            : AssertionMatcherBase<ContainerType<ContainedType>>(actual) {}                                            \
                                                                                                                       \
        auto contains(const ContainedType &contained) const -> void {                                                  \
            if (std::find(                                                                                             \
                    AssertionMatcherBase<ContainerType<ContainedType>>::_actual.begin(),                               \
                    AssertionMatcherBase<ContainerType<ContainedType>>::_actual.end(),                                 \
                    contained                                                                                          \
                )                                                                                                      \
                == AssertionMatcherBase<ContainerType<ContainedType>>::_actual.end()) {                                \
                Assertion::_fail("Failed asserting that container contains value " + serialize(contained));            \
            }                                                                                                          \
                                                                                                                       \
            Assertion::success();                                                                                      \
        }                                                                                                              \
                                                                                                                       \
        auto count(const unsigned int number) const -> void {                                                          \
            if (AssertionMatcherBase<ContainerType<ContainedType>>::_actual.size() != number) {                        \
                Assertion::_fail("Failed asserting that container has " + std::to_string(number) + " elements.");      \
            }                                                                                                          \
                                                                                                                       \
            Assertion::success();                                                                                      \
        }                                                                                                              \
                                                                                                                       \
        auto isEmpty() const -> void {                                                                                 \
            if (! AssertionMatcherBase<ContainerType<ContainedType>>::_actual.empty()) {                               \
                Assertion::_fail("Failed asserting that container is empty.");                                         \
            }                                                                                                          \
                                                                                                                       \
            Assertion::success();                                                                                      \
        }                                                                                                              \
    }

AssertionMatcher_contains(std::vector);

AssertionMatcher_contains(std::deque);

AssertionMatcher_contains(std::list);

AssertionMatcher_contains(std::set);

template<typename ContainedType, std::size_t Size>
class AssertionMatcher<std::array<ContainedType, Size>> : public AssertionMatcherBase<std::array<ContainedType, Size>> {
  public:
    explicit AssertionMatcher(const std::array<ContainedType, Size> &actual)
        : AssertionMatcherBase<std::array<ContainedType, Size>>(actual) {}

    auto contains(const ContainedType &contained) const -> void {
        if (std::find(
                AssertionMatcherBase<std::array<ContainedType, Size>>::_actual.begin(),
                AssertionMatcherBase<std::array<ContainedType, Size>>::_actual.end(),
                contained
            )
            == AssertionMatcherBase<std::array<ContainedType, Size>>::_actual.end()) {
            Assertion::_fail("Failed asserting that container contains value " + serialize(contained));
        }

        Assertion::success();
    }

    auto count(const unsigned int number) const -> void {
        if (AssertionMatcherBase<std::array<ContainedType, Size>>::_actual.size() != number) {
            Assertion::_fail("Failed asserting that container has " + std::to_string(number) + " elements.");
        }

        Assertion::success();
    }

    auto isEmpty() const -> void {
        if (! AssertionMatcherBase<std::array<ContainedType, Size>>::_actual.empty()) {
            Assertion::_fail("Failed asserting that container is empty.");
        }

        Assertion::success();
    }
};

template<typename KeyType, typename ValueType>
class AssertionMatcher<std::map<KeyType, ValueType>> : public AssertionMatcherBase<std::map<KeyType, ValueType>> {
  public:
    explicit AssertionMatcher(const std::map<KeyType, ValueType> &actual)
        : AssertionMatcherBase<std::map<KeyType, ValueType>>(actual) {}

    auto hasKey(const KeyType &key) const -> void {
        if (! AssertionMatcherBase<std::map<KeyType, ValueType>>::_actual.contains(key)) {
            Assertion::_fail("Failed asserting that map contains key " + serialize(key));
        }

        Assertion::success();
    }
};

template<> inline auto AssertionMatcherBase<std::string>::isFile() const -> void {
    if (! std::filesystem::is_regular_file(_actual)) {
        Assertion::_fail("File '" + _actual + "' not found.");
    }

    Assertion::success();
}

template<> inline auto AssertionMatcherBase<std::string>::isDirectory() const -> void {
    if (! std::filesystem::is_directory(_actual)) {
        Assertion::_fail("File '" + _actual + "' not found.");
    }

    Assertion::success();
}
} // namespace crossedfingers::internals

#endif // ASSERTION_H
