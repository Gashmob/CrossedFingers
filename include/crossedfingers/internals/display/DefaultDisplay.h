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
#ifndef DEFAULTDISPLAY_H
#define DEFAULTDISPLAY_H
/**
 * Default simple display
 */

#include "Display.h"

namespace crossedfingers::internals {
class DefaultDisplay final : public Display {
  public:
    auto printBeginSuite(const std::string &suite_name) -> void override;

    auto printBeginCase(const std::string &case_name) -> void override;

    auto printEndCase(const std::string &case_name) -> void override;

    auto printEndSuite(const std::string &suite_name) -> void override;

    auto printSkipCase(const std::string &case_name) -> void override;

    auto printWarningCase(const std::string &case_name) -> void override;

    auto printFailCase(const std::string &case_name, const std::string &message) -> void override;

    auto printSummary(
        int test_count,
        int assertion_count,
        const std::vector<std::string> &succeed_tests,
        const std::vector<std::string> &skipped_tests,
        const std::map<std::string, std::string> &warning_tests,
        const std::map<std::string, std::string> &failed_tests
    ) -> void override;
};
} // namespace crossedfingers

#endif // DEFAULTDISPLAY_H
