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
#include "test_tools.hpp"

#include <algorithm>
#include <crossedfingers/test.h>

using namespace crossedfingers;

describe(test_run, []() {
    it("Should have the same count of test between list and run", []() {
        const auto list      = run_with_args("list");
        const auto test_list = split(list, "\n");
        assertThat(test_list.size()).isGreaterThanOrEqualTo(1);

        const auto run = run_with_args("run");
        assertThat(run).hasSubString("TEST COUNT: " + std::to_string(test_list.size()));
        for (const auto &test : test_list) {
            assertThat(run).hasSubString(test);
        }
    });

    it("Should run only filtered tests", []() {
        auto run = run_with_args("run --filter 'assert.skip::Should skip this test'");
        assertThat(run).hasSubString("Using filter: assert.skip::Should skip this test");
        assertThat(run).hasSubString("> assert.skip::Should skip this test - SKIP");
        assertThat(run).hasSubString("TEST COUNT: 1");

        run = run_with_args("run --filter 'test_run.beforeEach.*'");
        assertThat(run).hasSubString("Using filter: test_run.beforeEach.*");
        assertThat(run).hasSubString("> test_run.beforeEach::Should work 1 - SUCCESS");
        assertThat(run).hasSubString("> test_run.beforeEach::Should work 2 - SUCCESS");
        assertThat(run).hasSubString("> test_run.beforeEach::Should work 3 - SUCCESS");
        assertThat(run).hasSubString("TEST COUNT: 3");
    });
});
