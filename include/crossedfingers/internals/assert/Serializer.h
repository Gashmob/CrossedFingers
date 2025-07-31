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

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "crossedfingers/internals/utils.hpp"
#include "crossedfingers/utilities.h"

#include <string>

namespace crossedfingers::internals {
template<typename T> class Serializer final {
  public:
    Serializer() = default;

    static auto _serialize(const T &value) -> std::string {
        (void) value;
        return getTypeName<T>() + "...";
    }
};

template<typename T> auto serialize(const T &value) -> std::string {
    return Serializer<T>::_serialize(value);
}

template<> class Serializer<std::nullptr_t> final {
  public:
    static auto _serialize(const std::nullptr_t &value) -> std::string {
        (void) value;
        return "nullptr";
    }
};

template<> class Serializer<bool> final {
  public:
    static auto _serialize(const bool &value) -> std::string {
        return value ? "true" : "false";
    }
};

template<> class Serializer<char> final {
  public:
    static auto _serialize(const char &value) -> std::string {
        return "'" + std::string(1, value) + "'";
    }
};

template<> class Serializer<unsigned char> final {
  public:
    static auto _serialize(const unsigned char &value) -> std::string {
        return "'" + std::string(1, value) + "'";
    }
};

template<> class Serializer<char8_t> final {
  public:
    static auto _serialize(const char8_t &value) -> std::string {
        return "'" + std::string(1, value) + "'";
    }
};

template<> class Serializer<char16_t> final {
  public:
    static auto _serialize(const char16_t &value) -> std::string {
        return "'" + std::string(1, value) + "'";
    }
};

template<> class Serializer<char32_t> final {
  public:
    static auto _serialize(const char32_t &value) -> std::string {
        return "'" + std::string(1, value) + "'";
    }
};

template<> class Serializer<wchar_t> final {
  public:
    static auto _serialize(const wchar_t &value) -> std::string {
        return "'" + std::string(1, value) + "'";
    }
};

template<> class Serializer<short> final {
  public:
    static auto _serialize(const short &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<int> final {
  public:
    static auto _serialize(const int &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<long> final {
  public:
    static auto _serialize(const long &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<long long> final {
  public:
    static auto _serialize(const long long &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<unsigned short> final {
  public:
    static auto _serialize(const unsigned short &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<unsigned int> final {
  public:
    static auto _serialize(const unsigned int &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<unsigned long> final {
  public:
    static auto _serialize(const unsigned long &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<unsigned long long> final {
  public:
    static auto _serialize(const unsigned long long &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<float> final {
  public:
    static auto _serialize(const float &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<double> final {
  public:
    static auto _serialize(const double &value) -> std::string {
        return std::to_string(value);
    }
};

template<> class Serializer<long double> final {
  public:
    static auto _serialize(const long double &value) -> std::string {
        return std::to_string(value);
    }
};

template<typename SubType, std::size_t Size> class Serializer<SubType[Size]> final {
  public:
    static auto _serialize(const SubType value[Size]) -> std::string {
        std::string result = "[";
        for (std::size_t i = 0; i < Size; i++) {
            result += serialize(value[i]);
            if (i + 1 < Size) {
                result += ", ";
            }
        }
        return result + "]";
    }
};

template<typename T> class Serializer<T *> final {
  public:
    static auto _serialize(const T *value) -> std::string {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
};

template<> class Serializer<std::string> final {
  public:
    static auto _serialize(const std::string &value) -> std::string {
        return value;
    }
};
} // namespace crossedfingers::internals

#endif // SERIALIZER_H
