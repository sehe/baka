#include <baka/io/pipe.hpp>
#include <catch.hpp>
#include <string>

TEST_CASE("pipe", "[io::pipe]") {
    auto pair = baka::io::pipe();

    std::string input("Hello, world!");
    pair.second.write(input.data(), input.data() + input.size());

    std::string output(input.size(), '\0');
    pair.first.read(&output[0], &output[0] + output.size());

    REQUIRE(input == output);
}
