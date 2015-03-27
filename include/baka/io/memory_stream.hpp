#pragma once
#include <baka/io/io_error.hpp>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace baka {
    namespace io {
        class memory_stream {
        public:
            memory_stream() : offset(0) { }

            char const* write(char const* begin, char const* end) {
                while (begin != end) {
                    if (data.size() == offset) {
                        data.push_back(*begin);
                    } else {
                        data[offset] = *begin;
                    }
                    ++offset;
                    ++begin;
                }
                return end;
            }

            char* read(char* begin, char* end) {
                if (offset == data.size()) {
                    throw eof_error("eof");
                }
                while (begin != end) {
                    if (data.size() == offset) {
                        return begin;
                    }
                    *begin = data[offset];
                    ++offset;
                    ++begin;
                }
                return end;
            }

            void seek_begin(std::size_t offset_) {
                if (offset_ > data.size()) {
                    throw std::runtime_error("bad seek");
                }
                offset = offset_;
            }

        private:
            std::vector<char> data;
            std::size_t offset;
        };
    }
}
