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
#include "../test_tools.hpp"

#include <crossedfingers/internals/assert/Serializer.h>
#include <crossedfingers/test.h>

using namespace crossedfingers;

describe(Serializer, []() {
    it("Serializes type name for non handled ones", []() {
        const SomeObject variable;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("SomeObject..."));
    });

    it("Serializes nullptr", []() {
        assertThat(internals::serialize(nullptr)).isEqualTo(std::string("nullptr"));
    });

    it("Serializes bool", []() {
        assertThat(internals::serialize(true)).isEqualTo(std::string("true"));
        assertThat(internals::serialize(false)).isEqualTo(std::string("false"));
    });

    it("Serializes char", []() {
        const char variable = 'c';
        assertThat(internals::serialize(variable)).isEqualTo(std::string("'c'"));
    });

    it("Serializes char8_t", []() {
        const char8_t variable = 'c';
        assertThat(internals::serialize(variable)).isEqualTo(std::string("'c'"));
    });

    it("Serializes char16_t", []() {
        const char16_t variable = 'c';
        assertThat(internals::serialize(variable)).isEqualTo(std::string("'c'"));
    });

    it("Serializes char32_t", []() {
        const char32_t variable = 'c';
        assertThat(internals::serialize(variable)).isEqualTo(std::string("'c'"));
    });

    it("Serializes wchar_t", []() {
        const wchar_t variable = 'c';
        assertThat(internals::serialize(variable)).isEqualTo(std::string("'c'"));
    });

    it("Serializes short", []() {
        const short variable = 3;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3"));
    });

    it("Serializes int", []() {
        const int variable = 3;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3"));
    });

    it("Serializes long", []() {
        const long variable = 3;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3"));
    });

    it("Serializes long long", []() {
        const long long variable = 3;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3"));
    });

    it("Serializes unsigned char", []() {
        const unsigned char variable = 'c';
        assertThat(internals::serialize(variable)).isEqualTo(std::string("'c'"));
    });

    it("Serializes unsigned short", []() {
        const unsigned short variable = 3;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3"));
    });

    it("Serializes unsigned int", []() {
        const unsigned int variable = 3;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3"));
    });

    it("Serializes unsigned long", []() {
        const unsigned long variable = 3;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3"));
    });

    it("Serializes unsigned long long", []() {
        const unsigned long long variable = 3;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3"));
    });

    it("Serializes float", []() {
        const float variable = 3.14;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3.140000"));
    });

    it("Serializes double", []() {
        const double variable = 3.14;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3.140000"));
    });

    it("Serializes long double", []() {
        const long double variable = 3.14;
        assertThat(internals::serialize(variable)).isEqualTo(std::string("3.140000"));
    });

    it("Serializes array[]", []() {
        const int variable[] = {1, 2, 3};
        assertThat(internals::serialize(variable)).isEqualTo(std::string("[1, 2, 3]"));
    });

    it("Serializes pointer", []() {
        const auto pointer = new int(3);
        std::stringstream ss;
        ss << pointer;
        assertThat(internals::serialize(pointer)).isEqualTo(ss.str());
    });

    it("Serializes char*", []() {
        const char *variable = "Hello";
        assertThat(internals::serialize(variable)).isEqualTo(std::string("Hello"));
    });

    it("Serializes string", []() {
        const std::string variable = "World!";
        assertThat(internals::serialize(variable)).isEqualTo(std::string("World!"));
    });
});
