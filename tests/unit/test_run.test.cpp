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
#include "crossedfingers/test.h"

using namespace crossedfingers;

static int i  = 2;
static bool b = true;
static char c = 'd';

static int some_value = 0;

static int nb_run_1 = 0;
static int nb_run_2 = 0;

describe(test_run, []() {
    describe(context, []() {
        it("Should work with global context", []() {
            assertThat(i).isEqualTo(2);
            assertThat(b).isEqualTo(true);
            assertThat(c).isEqualTo('d');
        });
    });

    describe(before, []() {
        before([]() {
            some_value = 2;
        });

        it("Should call before and set some_value to 2", []() {
            assertThat(some_value).isEqualTo(2);
        });
    });

    describe(beforeEach, []() {
        beforeEach([]() {
            nb_run_2++;
        });

        it("Should work 1", []() {
            nb_run_1++;
            assertThat(nb_run_1).isEqualTo(nb_run_2);
        });

        it("Should work 2", []() {
            nb_run_1++;
            assertThat(nb_run_1).isEqualTo(nb_run_2);
        });

        it("Should work 3", []() {
            nb_run_1++;
            assertThat(nb_run_1).isEqualTo(nb_run_2);
        });
    });
});
