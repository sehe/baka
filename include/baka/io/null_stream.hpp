#pragma once

namespace baka {
    namespace io {
        class null_stream {
        public:
            char const* write(char const*, char const* end) {
                return end;
            }

            char* read(char* begin, char*) {
                return begin;
            }
        };
    }
}
