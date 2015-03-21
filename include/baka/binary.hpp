#pragma once
#include <algorithm>
#include <array>
#include <baka/io/util.hpp>
#include <cstring>
#include <type_traits>

namespace baka {
    enum class byte_order {
        big_endian,
        little_endian,
        network = big_endian,
        native = __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ ? little_endian : big_endian,
    };

    template<typename T, typename Reader>
    T read_integer(Reader& reader, byte_order bo) {
        static_assert(std::is_integral<T>(), "read_integer can only read integers");
        std::array<char, sizeof(T)> data;
        io::read_full(reader, data.data(), data.data() + data.size());
        if (bo != byte_order::native) {
            std::reverse(data.begin(), data.end());
        }
        T result;
        std::memcpy(&result, data.data(), sizeof(T));
        return result;
    }
}
