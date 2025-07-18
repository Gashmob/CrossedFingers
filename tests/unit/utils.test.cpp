/**
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
#include "../../src/crossedfingers/utils.hpp"

#include <crossedfingers/test.h>

using namespace crossedfingers;

describe(utils, []() {
    describe(split, []() {
        it("Should returns empty for empty input", []() {
            assertThat(split("", " ")).isEmpty();
        });

        it("Should return one item when delimiter not present", []() {
            assertThat(split("abc", " ")).isEqualTo(std::vector<std::string>({"abc"}));
        });

        it("Can split on space", []() {
            assertThat(split("a b c", " ")).isEqualTo(std::vector<std::string>({"a", "b", "c"}));
        });

        it("Skips empty tokens", []() {
            assertThat(split("a b      c", " ")).isEqualTo(std::vector<std::string>({"a", "b", "c"}));
        });

        it("Can split on long delimiter", []() {
            assertThat(split("ahellobhelloc", "hello")).isEqualTo(std::vector<std::string>({"a", "b", "c"}));
        });
    });

    describe(splitPattern, []() {
        it("Should return empty for empty", []() {
            assertThat(splitPattern("")).isEmpty();
        });

        it("Should return one item if simple case", []() {
            assertThat(splitPattern("hello")).isEqualTo(std::vector<std::string>({"hello"}));
        });

        it("Should split on .", []() {
            assertThat(splitPattern("hello.world.foo.bar"))
                .isEqualTo(std::vector<std::string>({"hello", "world", "foo", "bar"}));
        });

        it("Should split with the ::", []() {
            assertThat(splitPattern("test.suite::test case"))
                .isEqualTo(std::vector<std::string>({"test", "suite", "test case"}));
        });
    });

    describe(matchFilter, []() {
        it("Should return true whenever pattern is std::nullopt", []() {
            assertThat(matchPattern("", std::nullopt)).isTrue();
            assertThat(matchPattern("foobar", std::nullopt)).isTrue();
            assertThat(matchPattern("test.a.b.c::case", std::nullopt)).isTrue();
            assertThat(matchPattern("blabla", std::nullopt)).isTrue();
            assertThat(matchPattern("Lorem ipsum dolor sit amet", std::nullopt)).isTrue();
            assertThat(matchPattern("Hello World!", std::nullopt)).isTrue();
        });

        it("Should return true for empty pattern", []() {
            assertThat(matchPattern("", "")).isTrue();
            assertThat(matchPattern("foobar", "")).isTrue();
            assertThat(matchPattern("test.a.b.c::case", "")).isTrue();
            assertThat(matchPattern("blabla", "")).isTrue();
            assertThat(matchPattern("Lorem ipsum dolor sit amet", "")).isTrue();
            assertThat(matchPattern("Hello World!", "")).isTrue();
        });

        it("Should return true for exact match", []() {
            assertThat(matchPattern("test.subtest::case", "test.subtest::case")).isTrue();
        });

        it("Should return true for start of pattern", []() {
            assertThat(matchPattern("test", "test.subtest::case")).isTrue();
            assertThat(matchPattern("test.subtest", "test.subtest::case")).isTrue();
        });

        it("Should return true for * pattern", []() {
            assertThat(matchPattern("test", "test.subtest.*")).isTrue();
            assertThat(matchPattern("test.subtest", "test.subtest.*")).isTrue();
            assertThat(matchPattern("test.subtest::case", "test.subtest.*")).isTrue();

            assertThat(matchPattern("test", "test.*::case")).isTrue();
            assertThat(matchPattern("test.subtest", "test.*::case")).isTrue();
            assertThat(matchPattern("test.subtest::case", "test.*::case")).isTrue();

            assertThat(matchPattern("test", "test.*.subsubtest::case")).isTrue();
            assertThat(matchPattern("test.subtest", "test.*.subsubtest::case")).isTrue();
            assertThat(matchPattern("test.subtest.subsubtest", "test.*.subsubtest::case")).isTrue();
            assertThat(matchPattern("test.subtest.subsubtest::case", "test.*.subsubtest::case")).isTrue();
        });

        it("Should return true for incomplete pattern", []() {
            assertThat(matchPattern("test", "test.subtest")).isTrue();
            assertThat(matchPattern("test.subtest", "test.subtest")).isTrue();
            assertThat(matchPattern("test.subtest::case", "test.subtest")).isTrue();
        });

        it("Should return false otherwise", []() {
            assertThat(matchPattern("abc", "test")).isFalse();
            assertThat(matchPattern("test.subtest", "test.foo")).isFalse();
            assertThat(matchPattern("test.subtest::bar", "test.subtest::foo")).isFalse();
        });
    });
});
