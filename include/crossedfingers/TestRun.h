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
#ifndef TESTRUN_H
#define TESTRUN_H
/**
 * Main class which holds TestSuites
 */

#include "TestSuite.h"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace crossedfingers {
class TestRun final {
    friend class RunCommand;
    friend class ListCommand;

    enum class Mode {
        SETUP,
        RUN,
        LIST,
    };

  public:
    static auto instance() -> TestRun &;

    [[nodiscard]] auto run(int argc, char **argv) -> int;

    auto addSuite(const std::string &name, const std::function<void()> &callback) -> int;

    auto addCase(const std::string &name, const std::function<void()> &callback) const -> void;

  private:
    std::vector<std::string> _suite_context;
    std::map<std::string, std::shared_ptr<TestSuite>> _root_suites;
    Mode _mode;

    TestRun(): _mode(Mode::SETUP) {}

    [[nodiscard]] auto runSuites() -> int;

    [[nodiscard]] auto listSuites() -> int;
};
} // namespace crossedfingers

#endif // TESTRUN_H
