#include <baka/io/file_descriptor.hpp>
#include <baka/io/file_stream.hpp>
#include <catch.hpp>
#include <cstring>
#include <utility>

TEST_CASE("read reads from the file stream and write writes to it", "[io::file_stream]") {
    int fds[2];
    pipe(fds);
    baka::io::unique_fd read_end(fds[0]);
    baka::io::unique_fd write_end(fds[1]);

    baka::io::file_stream<decltype(write_end), baka::io::operation::write> wstream(std::move(write_end));
    baka::io::file_stream<decltype(read_end), baka::io::operation::read> rstream(std::move(read_end));

    char data[] = "the great baka";
    wstream.write(data, data + sizeof(data));

    std::vector<char> result(sizeof(data));
    rstream.read(result.data(), result.data() + result.size());

    REQUIRE(std::strcmp(data, result.data()) == 0);
}
