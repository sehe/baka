#pragma once
#include <baka/io/file_descriptor.hpp>
#include <baka/io/file_stream.hpp>
#include <baka/io/io_error.hpp>
#include <cerrno>
#include <system_error>
#include <unistd.h>
#include <utility>

namespace baka {
    namespace io {
        using pipe_reader = file_stream<unique_fd, operation::read>;
        using pipe_writer = file_stream<unique_fd, operation::write>;

        inline std::pair<pipe_reader, pipe_writer> pipe() {
            int fds[2];
            int err = ::pipe(fds);
            if (err == -1) {
                throw io_error(std::make_error_code(static_cast<std::errc>(errno)));
            }
            return std::make_pair(pipe_reader(unique_fd(fds[0])),
                                  pipe_writer(unique_fd(fds[1])));
        }
    }
}
