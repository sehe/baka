#pragma once
#include <baka/variadic.hpp>
#include <type_traits>
#include <unistd.h>
#include <utility>

namespace baka {
    namespace io {
        enum class operation { read, write, seek };

        template<typename FD, operation... supported_operations>
        class file_stream {
        public:
            explicit file_stream(FD fd_) : fd(std::move(fd_)) { }

            typename std::enable_if<contains_value<operation, operation::read, supported_operations...>::value, char*>::type
            read(char* begin, char* end) {
                auto n = ::read(fd.native_handle(), begin, end - begin);
                if (n == -1) {
                    throw "fuck";
                }
                return begin + n;
            }

        private:
            FD fd;
        };
    }
}
