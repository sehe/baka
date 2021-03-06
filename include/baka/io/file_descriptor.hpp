#pragma once
#include <baka/exception.hpp>
#include <baka/io/io_error.hpp>
#include <stdexcept>
#include <unistd.h>

namespace baka {
    namespace io {
        BAKA_EXCEPTION(bad_fd, std::logic_error);

        class unique_fd {
        public:
            using native_handle_type = int;

            explicit unique_fd(native_handle_type fd_) : fd(fd_) { }

            unique_fd(unique_fd&& other) : fd(other.fd) {
                other.fd = -1;
            }

            unique_fd& operator=(unique_fd&& other) {
                this->~unique_fd();
                fd = other.fd;
                other.fd = -1;
                return *this;
            }

            ~unique_fd() {
                if (fd != -1) {
                    ::close(fd);
                }
            }

            native_handle_type native_handle() {
                if (fd == -1) {
                    throw bad_fd("attempt to acquire native handle of moved-from file descriptor");
                }
                return fd;
            }

        private:
            native_handle_type fd;
        };
    }
}
