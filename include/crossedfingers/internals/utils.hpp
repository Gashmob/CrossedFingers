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
#ifndef UTILS_HPP
#define UTILS_HPP

#include <optional>
#include <regex>
#include <string>

namespace crossedfingers {
inline auto split(const std::string &str, const std::string &delimiter) -> std::vector<std::string> {
    const std::regex split_regex(delimiter);
    std::sregex_token_iterator iter(str.begin(), str.end(), split_regex, -1);
    const std::sregex_token_iterator end;
    std::vector<std::string> result;
    while (iter != end) {
        std::string current = *iter++;
        if (! current.empty()) {
            result.push_back(current);
        }
    }

    return result;
}

inline auto splitPattern(const std::string &pattern) -> std::vector<std::string> {
    if (pattern.empty()) {
        return {};
    }

    const auto temp = split(pattern, "\\.");
    const auto end  = split(temp[temp.size() - 1], "::");

    std::vector<std::string> result;
    for (int i = 0; i < temp.size() - 1; ++i) {
        result.push_back(temp[i]);
    }
    for (const auto & element : end) {
        result.push_back(element);
    }

    return result;
}

inline auto matchPattern(const std::string &name, const std::optional<std::string> &pattern) -> bool {
    if (! pattern.has_value()) {
        return true;
    }

    const auto name_split    = splitPattern(name);
    const auto pattern_split = splitPattern(pattern.value());

    size_t i = 0;
    while (i < name_split.size() && i < pattern_split.size()) {
        if (pattern_split[i] != "*" && name_split[i] != pattern_split[i]) {
            return false;
        }

        i++;
    }

    return true;
}
} // namespace crossedfingers

#endif // UTILS_HPP
