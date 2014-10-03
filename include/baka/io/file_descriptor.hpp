#pragma once
#include <unistd.h>

namespace baka {
    namespace io {
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
                    close(fd);
                }
            }

            native_handle_type native_handle() {
                return fd;
            }

        private:
            native_handle_type fd;
        };
    }
}
