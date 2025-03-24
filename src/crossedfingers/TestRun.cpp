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
#include "crossedfingers/TestRun.h"

#include "crossedfingers/commands/RunCommand.h"

#include <iostream>
#include <yeschief.h>

using namespace crossedfingers;

auto TestRun::instance() -> TestRun & {
    static TestRun instance;
    return instance;
}

auto TestRun::run(const int argc, char **argv) -> int {
    if (argc < 1) {
        throw std::runtime_error("Bad argument count given");
    }
    const auto program_name = std::string(argv[0]);
    yeschief::CLI cli(program_name, "This program contains tests written with CrossedFingers 🤞");

    RunCommand run;
    cli.addCommand(&run);
    yeschief::HelpCommand help(&cli);
    cli.addCommand(&help);

    const auto results = cli.run(argc, argv);
    if (! results.has_value()) {
        cli.help(std::cout);
        return 1;
    }

    return run.run(yeschief::CLIResults({}));
}
