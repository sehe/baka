#include <baka/io/null_stream.hpp>
#include <catch.hpp>
#include <vector>

TEST_CASE("writing to a null_stream succeeds", "[io::null_stream]") {
    baka::io::null_stream stream;
    std::vector<char> data(64);
    auto result = stream.write(data.data(), data.data() + data.size());
    REQUIRE(result == data.data() + data.size());
}

TEST_CASE("reading from a null_stream does nothing", "[io::null_stream]") {
    baka::io::null_stream stream;
    std::vector<char> data(64);
    auto result = stream.read(data.data(), data.data() + data.size());
    REQUIRE(data == std::vector<char>(64));
    REQUIRE(result == data.data());
}
