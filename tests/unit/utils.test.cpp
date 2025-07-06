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
#include "../../src/crossedfingers/utils.hpp"

#include <crossedfingers/test.h>

using namespace crossedfingers;

describe(utils, []() {
    describe(join, []() {
        it("Should returns empty if vector is empty", []() {
            assertThat(join({}, ", ")).isEqualTo("");
        });

        it("Should join with empty string", []() {
            assertThat(join({"a", "b", "c"}, "")).isEqualTo("abc");
        });

        it("Should join with given delimiter", []() {
            assertThat(join({"a", "b", "c"}, ", ")).isEqualTo("a, b, c");
        });
    });

    describe(getTypeName, []() {
        it("Should return type name when given by template", []() {
            assertThat(getTypeName<int>()).isEqualTo("int");
            assertThat(getTypeName<bool>()).isEqualTo("bool");
            assertThat(getTypeName<char>()).isEqualTo("char");
            assertThat(getTypeName<std::string>()).hasSubString("string");
            assertThat(getTypeName<AssertionException>()).isEqualTo("crossedfingers::AssertionException");
        });

        it("Should return type name when given by value", []() {
            assertThat(getTypeName(3)).isEqualTo("int");
            assertThat(getTypeName(true)).isEqualTo("bool");
            assertThat(getTypeName('c')).isEqualTo("char");
            assertThat(getTypeName(std::string("hello"))).hasSubString("string");
            assertThat(getTypeName(AssertionException("hello"))).isEqualTo("crossedfingers::AssertionException");
        });

        it("Should return type name when given by typeid", []() {
            assertThat(getTypeName(&typeid(int))).isEqualTo("int");
            assertThat(getTypeName(&typeid(3))).isEqualTo("int");
            assertThat(getTypeName(&typeid(bool))).isEqualTo("bool");
            assertThat(getTypeName(&typeid(true))).isEqualTo("bool");
            assertThat(getTypeName(&typeid(char))).isEqualTo("char");
            assertThat(getTypeName(&typeid('c'))).isEqualTo("char");
            assertThat(getTypeName<std::string>()).hasSubString("string");
            assertThat(getTypeName(std::string("hello"))).hasSubString("string");
            assertThat(getTypeName(&typeid(AssertionException))).isEqualTo("crossedfingers::AssertionException");
            assertThat(getTypeName(&typeid(AssertionException("hello"))))
                .isEqualTo("crossedfingers::AssertionException");
        });
    });
});
