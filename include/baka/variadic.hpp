#pragma once

namespace baka {
    template<std::size_t N, typename... Ts>
    struct nth_type;

    template<typename T, typename... Ts>
    struct nth_type<0, T, Ts...> {
        using type = T;
    };

    template<std::size_t N, typename T, typename... Ts>
    struct nth_type<N, T, Ts...> {
        using type = typename nth_type<N - 1, Ts...>::type;
    };

    template<std::size_t N, typename... Ts>
    using NthType = typename nth_type<N, Ts...>::type;
}
