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

describe(assert, []() {
    describe(skip, []() {
        it("Should skip this test", []() {
            skip();
        });
    });

    describe(fail, []() {
        it("Should throw an AssertionException", []() {
            assertThrow(fail(""), crossedfingers::AssertionException);
        });
    });

    describe(assertTrue, []() {
        it("Success on true", []() {
            assertTrue(true);
        });

        it("Fail on false", []() {
            assertThrow(assertTrue(false), crossedfingers::AssertionException);
        });
    });

    describe(assertFalse, []() {
        it("Success on false", []() {
            assertFalse(false);
        });

        it("Fail on true", []() {
            assertThrow(assertFalse(true), crossedfingers::AssertionException);
        });
    });

    describe(assertEquals, []() {
        it("Can compare same types", []() {
            assertEquals(2, 2);
            assertEquals(3.14, 3.14);
            assertEquals(true, true);
            assertEquals('c', 'c');
            assertEquals("hello", "hello");
        });

        it("Can compare same value but different type", []() {
            assertEquals(2, 2.0);
            assertEquals('A', 65);
            assertEquals(0, false);
        });

        it("Fail on comparing different values but same type", []() {
            assertThrow(assertEquals(2, 3), crossedfingers::AssertionException);
            assertThrow(assertEquals(3.14, 9.81), crossedfingers::AssertionException);
            assertThrow(assertEquals(true, false), crossedfingers::AssertionException);
            assertThrow(assertEquals('a', 'b'), crossedfingers::AssertionException);
            assertThrow(assertEquals("hello", "world"), crossedfingers::AssertionException);
        });

        it("Fail on comparing different types", []() {
            assertThrow(assertEquals(2, 3.0), crossedfingers::AssertionException);
            assertThrow(assertEquals('A', 96), crossedfingers::AssertionException);
            assertThrow(assertEquals(0, true), crossedfingers::AssertionException);
        });
    });

    describe(assertSame, []() {
        it("Can compare same types", []() {
            assertSame(2, 2);
            assertSame(3.14, 3.14);
            assertSame(true, true);
            assertSame('c', 'c');
            assertSame("hello", "hello");
        });

        it("Fail on comparing same value but different type", []() {
            assertThrow(assertSame(2, 2.0), crossedfingers::AssertionException);
            assertThrow(assertSame('A', 65), crossedfingers::AssertionException);
            assertThrow(assertSame(0, false), crossedfingers::AssertionException);
        });

        it("Fail on comparing different values but same type", []() {
            assertThrow(assertSame(2, 3), crossedfingers::AssertionException);
            assertThrow(assertSame(3.14, 9.81), crossedfingers::AssertionException);
            assertThrow(assertSame(true, false), crossedfingers::AssertionException);
            assertThrow(assertSame('a', 'b'), crossedfingers::AssertionException);
            assertThrow(assertSame("hello", "world"), crossedfingers::AssertionException);
        });
    });

    describe(assertNotEquals, []() {
        it("Can compare same types", []() {
            assertNotEquals(2, 3);
            assertNotEquals(3.14, 9.81);
            assertNotEquals(true, false);
            assertNotEquals('a', 'b');
            assertNotEquals("hello", "world");
        });

        it("Can compare different type", []() {
            assertNotEquals(2, 3.0);
            assertNotEquals('A', 96);
            assertNotEquals(0, true);
        });

        it("Fail on comparing same values", []() {
            assertThrow(assertNotEquals(2, 2), crossedfingers::AssertionException);
            assertThrow(assertNotEquals(3.14, 3.14), crossedfingers::AssertionException);
            assertThrow(assertNotEquals(true, true), crossedfingers::AssertionException);
            assertThrow(assertNotEquals('c', 'c'), crossedfingers::AssertionException);
            assertThrow(assertNotEquals("hello", "hello"), crossedfingers::AssertionException);
        });

        it("Fail on comparing same values different types", []() {
            assertThrow(assertNotEquals(2, 2.0), crossedfingers::AssertionException);
            assertThrow(assertNotEquals('A', 65), crossedfingers::AssertionException);
            assertThrow(assertNotEquals(0, false), crossedfingers::AssertionException);
        });
    });

    describe(assertLessThan, []() {
        it("Can compare same type", []() {
            assertLessThan(3, 2);
            assertLessThan(9.81, 3.14);
            assertLessThan('b', 'a');
        });

        it("Can compare different type", []() {
            assertLessThan(3, 2.0);
            assertLessThan(9.81, 3);
            assertLessThan('b', 0);
        });

        it("Fail on comparing expected gte value", []() {
            assertThrow(assertLessThan(2, 3), crossedfingers::AssertionException);
            assertThrow(assertLessThan(3.14, 9.81), crossedfingers::AssertionException);
            assertThrow(assertLessThan('a', 'b'), crossedfingers::AssertionException);
        });

        it("Fail on comparing expected gte value different type", []() {
            assertThrow(assertLessThan(2, 3.0), crossedfingers::AssertionException);
            assertThrow(assertLessThan(3.14, 10), crossedfingers::AssertionException);
            assertThrow(assertLessThan('a', 345), crossedfingers::AssertionException);
        });
    });

    describe(assertThrow, []() {
        it("Should catch the wanted exception", []() {
            assertThrow(throw std::runtime_error(""), std::runtime_error);
        });

        it("Should fail if exception not thrown", []() {
            assertThrow(true, crossedfingers::AssertionException);
        });

        it("Should fail if wrong exception is thrown", []() {
            assertThrow(
                assertThrow(throw std::runtime_error(""), std::logic_error), crossedfingers::AssertionException
            );
        });
    });

    describe(assertNotThrow, []() {
        it("Should success on no throw", []() {
            assertNotThrow(1 + 1);
        });

        it("Should fail if it throw", []() {
            assertThrow(assertNotThrow(throw std::runtime_error("")), crossedfingers::AssertionException);
        });
    });
});
