#pragma once
#include <baka/io/io_error.hpp>
#include <stdexcept>

namespace baka {
    namespace io {
        template<typename Reader>
        void read_full(Reader& reader, char* begin, char* end) {
            while (begin != end) {
                begin = reader.read(begin, end);
            }
        }
    }
}
