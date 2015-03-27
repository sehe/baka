#pragma once
#include <baka/exception.hpp>
#include <system_error>

namespace baka {
    namespace io {
        BAKA_EXCEPTION(io_error, std::system_error);
        BAKA_EXCEPTION(eof_error, std::runtime_error);
    }
}
