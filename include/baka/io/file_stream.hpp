#pragma once
#include <baka/variadic.hpp>
#include <type_traits>
#include <unistd.h>
#include <utility>

namespace baka {
    namespace io {
        enum class operation { read, write, seek };

        namespace detail {
            template<typename Self>
            class file_stream_reader {
            public:
                char* read(char* begin, char* end) {
                    auto& fd = static_cast<Self*>(this)->fd;
                    auto n = ::read(fd.native_handle(), begin, end - begin);
                    if (n == -1) {
                        throw "fuck";
                    }
                    return begin + n;
                }
            };

            template<typename Self>
            class file_stream_writer {
            public:
                char const* write(char const* begin, char const* end) {
                    auto& fd = static_cast<Self*>(this)->fd;
                    auto n = ::write(fd.native_handle(), begin, end - begin);
                    if (n == -1) {
                        throw "fuck";
                    }
                    return begin + n;
                }
            };

            template<typename Self>
            class file_stream_seeker {
                // TODO
            };

            template<operation op, typename... Args>
            struct mixin_for_operation;

            template<typename... Args>
            struct mixin_for_operation<operation::read, Args...> {
                using type = file_stream_reader<Args...>;
            };

            template<typename... Args>
            struct mixin_for_operation<operation::write, Args...> {
                using type = file_stream_writer<Args...>;
            };

            template<typename... Args>
            struct mixin_for_operation<operation::seek, Args...> {
                using type = file_stream_seeker<Args...>;
            };
        }

        template<typename FD, operation... supported_operations>
        class file_stream : public detail::mixin_for_operation<supported_operations, file_stream<FD, supported_operations...>>::type... {
        public:
            explicit file_stream(FD fd_) : fd(std::move(fd_)) { }

        private:
            FD fd;

            friend class detail::file_stream_reader<file_stream>;
            friend class detail::file_stream_writer<file_stream>;
            friend class detail::file_stream_seeker<file_stream>;
        };
    }
}
