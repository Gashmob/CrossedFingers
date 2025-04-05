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
#ifndef LISTCOMMAND_H
#define LISTCOMMAND_H
/**
 * This command list all the tests case line by line
 */

#include "../TestRun.h"

#include <yeschief.h>

namespace crossedfingers {
class ListCommand final : public yeschief::Command {
  public:
    explicit ListCommand(TestRun *test_run): _test_run(test_run) {}

    [[nodiscard]] auto getName() const -> std::string override {
        return "list";
    }

    [[nodiscard]] auto getDescription() const -> std::string override {
        return "List tests contained in the program";
    }

    auto run(const yeschief::CLIResults &results) -> int override;

  private:
    TestRun *_test_run;
};
} // namespace crossedfingers

#endif // LISTCOMMAND_H
