#pragma once
#include <baka/exception.hpp>
#include <system_error>

namespace baka {
    BAKA_EXCEPTION(io_error, std::system_error);
}
