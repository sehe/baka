#include <baka/binary.hpp>
#include <baka/io/pipe.hpp>
#include <catch.hpp>
#include <cstdint>
#include <string>

TEST_CASE("read_integer", "[io::binary]") {
    auto pair = baka::io::pipe();

    std::string input("\x01\x02\x03\x04");
    pair.second.write(input.data(), input.data() + input.size());

    auto output = baka::read_integer<std::uint32_t>(pair.first, baka::byte_order::network);

    REQUIRE(output == 0x01020304);
}

