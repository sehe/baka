#include <baka/io/memory_stream.hpp>
#include <catch.hpp>
#include <vector>

TEST_CASE("read reads from the memory stream and write writes to it", "[io::memory_stream]") {
    baka::io::memory_stream stream;

    std::vector<char> data{'a', 'b', 'c'};
    REQUIRE(stream.write(data.data(), data.data() + data.size()) == data.data() + data.size());

    stream.seek_begin(0);
    data = {'\0', '\0', '\0'};
    REQUIRE(stream.read(data.data(), data.data() + data.size() - 1) == data.data() + data.size() - 1);
    REQUIRE(data == (std::vector<char>{'a', 'b', '\0'}));

    stream.seek_begin(0);
    data = {'\0', '\0', '\0', '\0'};
    REQUIRE(stream.read(data.data(), data.data() + data.size()) == data.data() + data.size() - 1);
    REQUIRE(data == (std::vector<char>{'a', 'b', 'c', '\0'}));
}
