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
#include "crossedfingers/internals/commands/RunCommand.h"

#include "crossedfingers/internals/GlobalState.h"
#include "crossedfingers/internals/TestStatus.h"
#include "crossedfingers/internals/display/DefaultDisplay.h"
#include "crossedfingers/internals/display/OutputWrapper.h"

using namespace crossedfingers::internals;

auto RunCommand::setup(yeschief::CLI &cli) -> void {
    cli.addOption<int>(
        "random-seed",
        "Seed to shuffle test run order",
        {
          .required   = false,
          .value_help = "<number>",
        }
    );
    cli.addOption<std::string>(
        "filter",
        "Run only the tests matching the pattern. '*' matches any substring",
        {
          .required   = false,
          .value_help = "<pattern>",
        }
    );
}

auto RunCommand::run(const yeschief::CLIResults &results) -> int {
    OutputWrapper::init();
    TestStatus::instance().setDisplay(new DefaultDisplay());

    const auto seed = std::any_cast<int>(results.get("random-seed").value_or(static_cast<int>(std::time(nullptr))));
    OutputWrapper::print("Using seed: " + std::to_string(seed) + "\n");
    GlobalState::random_seed = seed;

    GlobalState::filter = results.get("filter").transform([](std::any value) {
        return std::any_cast<std::string>(value);
    });
    if (GlobalState::filter.has_value()) {
        OutputWrapper::print("Using filter: " + GlobalState::filter.value() + "\n");
    }

    OutputWrapper::print("\n");

    return _test_run->runTests();
}
