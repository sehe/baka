#include <baka/bound_function.hpp>
#include <catch.hpp>

TEST_CASE("construction", "[bound_function]") {
    baka::bound_function<int(int)> bf([] (int x) { return x * 2; });
}

TEST_CASE("calling", "[bound_function]") {
    int factor = 2;
    baka::bound_function<int(int)> bf([=] (int x) { return x * factor; });
    int(*fp)(int) = bf;
    REQUIRE(fp(4) == 8);
}
