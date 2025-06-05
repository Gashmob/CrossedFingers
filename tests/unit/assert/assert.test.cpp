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
#include <crossedfingers/assert/AssertionException.h>
#include <crossedfingers/test.h>
#include <list>
#include <set>

using namespace crossedfingers;

describe(assert, []() {
    describe(skip, []() {
        it("Should skip this test", []() {
            skip();
        });
    });

    describe(fail, []() {
        it("Should throw an AssertionException", []() {
            expectException<crossedfingers::AssertionException>();
            fail("");
        });
    });

    describe(assertTrue, []() {
        it("Success on true", []() {
            assertThat(true).isTrue();
        });

        it("Fail on false", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(false).isTrue();
        });
    });

    describe(assertFalse, []() {
        it("Success on false", []() {
            assertThat(false).isFalse();
        });

        it("Fail on true", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(true).isFalse();
        });
    });

    describe(assertEquals, []() {
        it("Can compare same types", []() {
            assertThat(2).isEqualTo(2);
            assertThat(3.14).isEqualTo(3.14);
            assertThat(true).isEqualTo(true);
            assertThat('c').isEqualTo('c');
            assertThat(std::string("hello")).isEqualTo("hello");
        });

        it("Can compare same value but different type", []() {
            assertThat(2).isEqualTo(2.0);
            assertThat('A').isEqualTo(65);
            assertThat(0).isEqualTo(false);
        });

        it("Fail on comparing different values but same type", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isEqualTo(3);
            // assertThrow(assertEquals(3.14, 9.81), crossedfingers::AssertionException);
            // assertThrow(assertEquals(true, false), crossedfingers::AssertionException);
            // assertThrow(assertEquals('a', 'b'), crossedfingers::AssertionException);
            // assertThrow(assertEquals("hello", "world"), crossedfingers::AssertionException);
        });

        it("Fail on comparing different types", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isEqualTo(3.0);
            // assertThrow(assertEquals('A', 96), crossedfingers::AssertionException);
            // assertThrow(assertEquals(0, true), crossedfingers::AssertionException);
        });
    });

    describe(assertSame, []() {
        it("Can compare same types", []() {
            assertThat(2).isStrictEqualTo(2);
            assertThat(3.14).isStrictEqualTo(3.14);
            assertThat(true).isStrictEqualTo(true);
            assertThat('c').isStrictEqualTo('c');
            assertThat(std::string("hello")).isStrictEqualTo(std::string("hello"));
        });

        it("Fail on comparing same value but different type", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isStrictEqualTo(2.0);
            // assertThrow(assertSame('A', 65), crossedfingers::AssertionException);
            // assertThrow(assertSame(0, false), crossedfingers::AssertionException);
        });

        it("Fail on comparing different values but same type", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isStrictEqualTo(3);
            // assertThrow(assertSame(3.14, 9.81), crossedfingers::AssertionException);
            // assertThrow(assertSame(true, false), crossedfingers::AssertionException);
            // assertThrow(assertSame('a', 'b'), crossedfingers::AssertionException);
            // assertThrow(assertSame("hello", "world"), crossedfingers::AssertionException);
        });
    });

    describe(assertNotEquals, []() {
        it("Can compare same types", []() {
            assertThat(2).isNotEqualTo(3);
            assertThat(3.14).isNotEqualTo(9.81);
            assertThat(true).isNotEqualTo(false);
            assertThat('a').isNotEqualTo('b');
            assertThat(std::string("hello")).isNotEqualTo("world");
        });

        it("Can compare different type", []() {
            assertThat(2).isNotEqualTo(3.0);
            assertThat('A').isNotEqualTo(96);
            assertThat(0).isNotEqualTo(true);
        });

        it("Fail on comparing same values", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isNotEqualTo(2);
            // assertThrow(assertNotEquals(3.14, 3.14), crossedfingers::AssertionException);
            // assertThrow(assertNotEquals(true, true), crossedfingers::AssertionException);
            // assertThrow(assertNotEquals('c', 'c'), crossedfingers::AssertionException);
            // assertThrow(assertNotEquals("hello", "hello"), crossedfingers::AssertionException);
        });

        it("Fail on comparing same values different types", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isNotEqualTo(2.0);
            // assertThrow(assertNotEquals('A', 65), crossedfingers::AssertionException);
            // assertThrow(assertNotEquals(0, false), crossedfingers::AssertionException);
        });
    });

    describe(assertLessThan, []() {
        it("Can compare same type", []() {
            assertThat(2).isLessThan(3);
            assertThat(3.14).isLessThan(9.81);
            assertThat('a').isLessThan('b');
        });

        it("Can compare different type", []() {
            assertThat(2.0).isLessThan(3);
            assertThat(3).isLessThan(9.81);
            assertThat(0).isLessThan('b');
        });

        it("Fail on comparing expected gte value", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isLessThan(3);
            // assertThrow(assertLessThan(3.14, 9.81), crossedfingers::AssertionException);
            // assertThrow(assertLessThan('a', 'b'), crossedfingers::AssertionException);
        });

        it("Fail on comparing expected gte value different type", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isLessThan(3.0);
            // assertThrow(assertLessThan(3.14, 10), crossedfingers::AssertionException);
            // assertThrow(assertLessThan('a', 345), crossedfingers::AssertionException);
        });
    });

    describe(assertLessThanOrEquals, []() {
        it("Can compare same type", []() {
            assertThat(2).isLessThanOrEqualTo(3);
            assertThat(3).isLessThanOrEqualTo(3);
            assertThat(3.14).isLessThanOrEqualTo(9.81);
            assertThat(9.81).isLessThanOrEqualTo(9.81);
            assertThat('a').isLessThanOrEqualTo('b');
            assertThat('b').isLessThanOrEqualTo('b');
        });

        it("Can compare different type", []() {
            assertThat(2.0).isLessThanOrEqualTo(3);
            assertThat(3.0).isLessThanOrEqualTo(3);
            assertThat(3).isLessThanOrEqualTo(9.81);
            assertThat(0).isLessThanOrEqualTo('b');
            assertThat(97).isLessThanOrEqualTo('b');
        });

        it("Fail on comparing expected gt value", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isLessThanOrEqualTo(3);
            // assertThrow(assertLessThanOrEquals(3.14, 9.81), crossedfingers::AssertionException);
            // assertThrow(assertLessThanOrEquals('a', 'b'), crossedfingers::AssertionException);
        });

        it("Fail on comparing expected gt value different type", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(2).isLessThanOrEqualTo(3.0);
            // assertThrow(assertLessThanOrEquals(3.14, 10), crossedfingers::AssertionException);
            // assertThrow(assertLessThanOrEquals('a', 345), crossedfingers::AssertionException);
        });
    });

    describe(assertGreaterThan, []() {
        it("Can compare same type", []() {
            assertThat(3).isGreaterThan(2);
            assertThat(9.81).isGreaterThan(3.14);
            assertThat('b').isGreaterThan('a');
        });

        it("Can compare different type", []() {
            assertThat(3.0).isGreaterThan(2);
            assertThat(10).isGreaterThan(3.14);
            assertThat(345).isGreaterThan('a');
        });

        it("Fail on comparing expected lte value", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(3).isGreaterThan(2);
            // assertThrow(assertGreaterThan(9.81, 3.14), crossedfingers::AssertionException);
            // assertThrow(assertGreaterThan('b', 'a'), crossedfingers::AssertionException);
        });

        it("Fail on comparing expected lte value different type", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(3.0).isGreaterThan(2);
            // assertThrow(assertGreaterThan(10, 3.14), crossedfingers::AssertionException);
            // assertThrow(assertGreaterThan(345, 'a'), crossedfingers::AssertionException);
        });
    });

    describe(assertGreaterThanOrEquals, []() {
        it("Can compare same type", []() {
            assertThat(3).isGreaterThanOrEqualTo(2);
            assertThat(3).isGreaterThanOrEqualTo(3);
            assertThat(9.81).isGreaterThanOrEqualTo(3.14);
            assertThat(9.81).isGreaterThanOrEqualTo(9.81);
            assertThat('b').isGreaterThanOrEqualTo('a');
            assertThat('b').isGreaterThanOrEqualTo('b');
        });

        it("Can compare different type", []() {
            assertThat(3).isGreaterThanOrEqualTo(2.0);
            assertThat(3).isGreaterThanOrEqualTo(3.0);
            assertThat(9.81).isGreaterThanOrEqualTo(3);
            assertThat('b').isGreaterThanOrEqualTo(0);
            assertThat('b').isGreaterThanOrEqualTo(97);
        });

        it("Fail on comparing expected lt value", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(3).isGreaterThanOrEqualTo(2);
            // assertThrow(assertGreaterThanOrEquals(9.81, 3.14), crossedfingers::AssertionException);
            // assertThrow(assertGreaterThanOrEquals('b', 'a'), crossedfingers::AssertionException);
        });

        it("Fail on comparing expected lt value different type", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(3.0).isGreaterThanOrEqualTo(2);
            // assertThrow(assertGreaterThanOrEquals(10, 3.14), crossedfingers::AssertionException);
            // assertThrow(assertGreaterThanOrEquals(345, 'a'), crossedfingers::AssertionException);
        });
    });

    describe(assertThrow, []() {
        it("Should catch the wanted exception", []() {
            expectException<std::runtime_error>("My error");
            throw std::runtime_error("My error");
        });
    });

    describe(assertMatchesRegex, []() {
        it("Should match", []() {
            assertThat(std::string("Hello")).matchesRegex("\\w*");
            assertThat(std::string("file.txt")).matchesRegex("^[a-z]+\\.txt$");
        });

        it("Should not match", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(std::string("foo.bar")).matchesRegex("^[a-z]+\\.txt$");
        });

        it("Should fail when is not a string", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(3).matchesRegex("Cannot match a regex against a 'int'.");
        });
    });

    describe(assertHasSubString, []() {
        it("Should success", []() {
            assertThat(std::string("Hello World!")).hasSubString("llo");
            assertThat(std::string("Foo Bar")).hasSubString("o Bar");
        });

        it("Should fail", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(std::string("Bonjour !")).hasSubString("llo");
        });

        it("Should fail when is not a string", []() {
            expectException<crossedfingers::AssertionException>("Cannot check that a 'int' has a sub string.");
            assertThat(3).hasSubString("llo");
        });
    });

    describe(assertStartsWith, []() {
        it("Should success", []() {
            assertThat(std::string("Hello World")).startsWith("Hell");
        });

        it("Should fail", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(std::string("bar")).startsWith("foo");
        });

        it("Should fail when is not a string", []() {
            expectException<crossedfingers::AssertionException>("Cannot check that a 'int' starts with a string.");
            assertThat(3).startsWith("foo");
        });
    });

    describe(assertEndsWith, []() {
        it("Should success", []() {
            assertThat(std::string("Hello World")).endsWith("rld");
        });

        it("Should fail", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(std::string("bar")).endsWith("foo");
        });

        it("Should fail when is not a string", []() {
            expectException<crossedfingers::AssertionException>("Cannot check that a 'int' ends with a string.");
            assertThat(3).endsWith("foo");
        });
    });

    describe(assertContains, []() {
        it("Should works with vector", []() {
            const std::vector container({1, 2, 3});
            assertThat(container).contains(2);
        });

        it("Should works with array", []() {
            constexpr std::array<int, 3> container({1, 2, 3});
            assertThat(container).contains(2);
        });

        it("Should works with deque", []() {
            const std::deque container({1, 2, 3});
            assertThat(container).contains(2);
        });

        it("Should works with list", []() {
            const std::list container({1, 2, 3});
            assertThat(container).contains(2);
        });

        it("Should works with set", []() {
            const std::set container({1, 2, 3});
            assertThat(container).contains(2);
        });

        it("Should fail", []() {
            const std::vector container({1, 3});
            expectException<crossedfingers::AssertionException>();
            assertThat(container).contains(2);
        });

        it("Should fail when is not a container", []() {
            expectException<crossedfingers::AssertionException>("Cannot check that a 'int' contains something.");
            assertThat(3).contains("foo");
        });
    });

    describe(assertHasKey, []() {
        it("Should find the key", []() {
            const std::map<std::string, int> container({
              {"a", 1},
              {"b", 2},
              {"c", 3},
            });
            assertThat(container).hasKey("a");
            assertThat(container).hasKey("b");
            assertThat(container).hasKey("c");
        });

        it("Should fail", []() {
            const std::map<std::string, int> container({
              {"a", 1},
              {"b", 2},
              {"c", 3},
            });
            expectException<crossedfingers::AssertionException>("Failed asserting that map contains key");
            assertThat(container).hasKey("d");
        });

        it("Should fail when not a map", []() {
            expectException<crossedfingers::AssertionException>("Cannot check that a 'int' has some key.");
            assertThat(3).hasKey("a");
        });
    });

    describe(assertCount, []() {
        it("Should works with vector", []() {
            const std::vector container({1, 2, 3});
            assertThat(container).count(3);
        });

        it("Should works with deque", []() {
            const std::deque container({1, 2, 3});
            assertThat(container).count(3);
        });

        it("Should works with list", []() {
            const std::list container({1, 2, 3});
            assertThat(container).count(3);
        });

        it("Should works with set", []() {
            const std::set container({1, 2, 3});
            assertThat(container).count(3);
        });

        it("Should fail", []() {
            const std::vector container({1, 2, 3});
            expectException<crossedfingers::AssertionException>();
            assertThat(container).count(2);
        });

        it("Should fail when is not a container", []() {
            expectException<crossedfingers::AssertionException>("Cannot check that a 'int' has N elements.");
            assertThat(3).count(1);
        });
    });

    describe(isEmpty, []() {
        it("Should works with vector", []() {
            constexpr std::vector<int> container;
            assertThat(container).isEmpty();
        });

        it("Should works with deque", []() {
            const std::deque<int> container;
            assertThat(container).isEmpty();
        });

        it("Should works with list", []() {
            const std::list<int> container;
            assertThat(container).isEmpty();
        });

        it("Should works with set", []() {
            const std::set<int> container;
            assertThat(container).isEmpty();
        });

        it("Should fail", []() {
            const std::vector container({1, 2, 3});
            expectException<crossedfingers::AssertionException>();
            assertThat(container).isEmpty();
        });

        it("Should fail when is not a container", []() {
            expectException<crossedfingers::AssertionException>("Cannot check that a 'int' is empty.");
            assertThat(3).isEmpty();
        });
    });

    describe(matchPredicate, []() {
        it("Should success", []() {
            assertThat('c').matchPredicate([](const char &_) {
                return true;
            });
            assertThat(3).matchPredicate([](const int &n) {
                return n == 3;
            });
        });

        it("Should fail", []() {
            expectException<crossedfingers::AssertionException>("Predicate returned false.");
            assertThat(3).matchPredicate([](const int &_) {
                return false;
            });
        });
    });

    describe(assertType, []() {
        it("Should success", []() {
            assertThat(3).matchType<int>();
            assertThat(true).matchType<bool>();
            assertThat('c').matchType<char>();
        });

        it("Should fail", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(3).matchType<char>();
        });
    });

    describe(isNull, []() {
        it("Should success", []() {
            assertThat(nullptr).isNull();
        });

        it("Should fail", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(new int(3)).isNull();
        });
    });

    describe(isFile, []() {
        it("Should success", []() {
            assertThat(std::string(FIXTURES_PATH "/some_file")).isFile();
        });

        it("Should fail", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(std::string(FIXTURES_PATH "/not_existing")).isFile();
        });

        it("Should fail when not a string", []() {
            expectException<crossedfingers::AssertionException>("Need a valid std::string to check if it exists.");
            assertThat(3).isFile();
        });
    });

    describe(isDirectory, []() {
        it("Should success", []() {
            assertThat(std::string(FIXTURES_PATH)).isDirectory();
        });

        it("Should fail", []() {
            expectException<crossedfingers::AssertionException>();
            assertThat(std::string(FIXTURES_PATH "/some_file")).isDirectory();
        });

        it("Should fail when not a string", []() {
            expectException<crossedfingers::AssertionException>("Need a valid std::string to check if it exists.");
            assertThat(3).isDirectory();
        });
    });
});
