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
#ifndef RUNCOMMAND_H
#define RUNCOMMAND_H
/**
 * Main command, it runs the tests
 */

#include "../TestRun.h"

#include <yeschief.h>

namespace crossedfingers::internals {
class RunCommand final : public yeschief::Command {
  public:
    explicit RunCommand(TestRun *test_run): _test_run(test_run) {}

    [[nodiscard]] auto getName() const -> std::string override {
        return "run";
    }

    [[nodiscard]] auto getDescription() const -> std::string override {
        return "Run tests contained in the program";
    }

    auto setup(yeschief::CLI &cli) -> void override;

    auto run(const yeschief::CLIResults &results) -> int override;

  private:
    TestRun *_test_run;
};
} // namespace crossedfingers

#endif // RUNCOMMAND_H
