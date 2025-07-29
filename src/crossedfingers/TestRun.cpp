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
#include "crossedfingers/internals/TestRun.h"

#include "crossedfingers/internals/GlobalState.h"
#include "crossedfingers/internals/TestStatus.h"
#include "crossedfingers/internals/commands/ListCommand.h"
#include "crossedfingers/internals/commands/RunCommand.h"

#include <iostream>
#include <random>
#include <yeschief.h>

using namespace crossedfingers::internals;

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

    RunCommand run_command(this);
    cli.addCommand(&run_command);
    ListCommand list_command(this);
    cli.addCommand(&list_command);
    yeschief::HelpCommand help_command(&cli);
    cli.addCommand(&help_command);

    if (const auto results = cli.run(argc, argv); ! results.has_value()) {
        cli.help(std::cout);
        return 1;
    }

    return run_command.run(yeschief::CLIResults({}));
}

auto TestRun::addSuite(const std::string &name, const std::function<void()> &callback) -> int {
    const auto previous = _current_suite;

    if (_current_suite == nullptr) {
        auto &test_suite = _root_suites.emplace_back(name);
        _current_suite   = &test_suite;
    } else {
        _current_suite = _current_suite->addSubSuite(name);
    }

    callback();
    _current_suite = previous;

    return 0;
}

auto TestRun::addCase(const std::string &name, const std::function<void()> &callback) const -> void {
    if (_current_suite == nullptr) {
        throw std::logic_error("Hmmm, there is something strange : a test case were added in global context");
    }

    _current_suite->addTestCase(name, callback);
}

auto TestRun::addBefore(const std::function<void()> &callback) const -> void {
    if (_current_suite == nullptr) {
        throw std::logic_error("Hmmm, there is something strange : a before() were added in global context");
    }

    _current_suite->setBefore(callback);
}

auto TestRun::addBeforeEach(const std::function<void()> &callback) const -> void {
    if (_current_suite == nullptr) {
        throw std::logic_error("Hmmm, there is something strange : a beforeEach() were added in global context");
    }

    _current_suite->setBeforeEach(callback);
}

auto TestRun::addAfter(const std::function<void()> &callback) const -> void {
    if (_current_suite == nullptr) {
        throw std::logic_error("Hmmm, there is something strange : an after() were added in global context");
    }

    _current_suite->setAfter(callback);
}

auto TestRun::addAfterEach(const std::function<void()> &callback) const -> void {
    if (_current_suite == nullptr) {
        throw std::logic_error("Hmmm, there is something strange : an afterEach() were added in global context");
    }

    _current_suite->setAfterEach(callback);
}

auto TestRun::runTests() -> int {
    std::mt19937_64 generator(GlobalState::random_seed);
    std::shuffle(_root_suites.begin(), _root_suites.end(), generator);
    for (auto &suite : _root_suites) {
        suite.run("");
    }

    TestStatus::instance().summary();

    return TestStatus::instance().returnValue();
}

auto TestRun::listTests() const -> int {
    for (const auto &suite : _root_suites) {
        suite.list("");
    }
    return 0;
}
