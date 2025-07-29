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

#ifndef UTILS_H
#define UTILS_H

#include <cxxabi.h>
#include <regex>
#include <string>
#include <vector>

namespace crossedfingers {
template<typename Type> auto getTypeName() -> std::string {
    return abi::__cxa_demangle(typeid(Type).name(), nullptr, nullptr, nullptr);
}

template<typename Type> auto getTypeName(const Type &_) -> std::string {
    return abi::__cxa_demangle(typeid(Type).name(), nullptr, nullptr, nullptr);
}

inline auto getTypeName(const std::type_info *type) -> std::string {
    return abi::__cxa_demangle(type->name(), nullptr, nullptr, nullptr);
}

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
} // namespace crossedfingers

#endif // UTILS_H
