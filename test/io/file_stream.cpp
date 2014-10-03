#include <baka/io/file_descriptor.hpp>
#include <baka/io/file_stream.hpp>
#include <catch.hpp>
#include <cstring>
#include <utility>

TEST_CASE("read reads from the file stream", "[io::file_stream]") {
    int fds[2];
    pipe(fds);
    baka::io::unique_fd read_end(fds[0]);
    baka::io::unique_fd write_end(fds[1]);

    char data[] = "the great baka";
    write(write_end.native_handle(), data, sizeof(data));

    baka::io::file_stream<decltype(read_end), baka::io::operation::read> stream(std::move(read_end));
    std::vector<char> result(sizeof(data));
    stream.read(result.data(), result.data() + result.size());
    REQUIRE(std::strcmp(data, result.data()) == 0);
}
