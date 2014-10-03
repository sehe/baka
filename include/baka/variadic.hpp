#pragma once
#include <type_traits>

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

    namespace detail {
        template<typename T>
        bool constexpr contains_value(T) {
            return false;
        }

        template<typename T, typename... U>
        bool constexpr contains_value(T needle, T head, U... tail) {
            return needle == head || contains_value(needle, tail...);
        }
    }

    template<typename T, T Needle, T... Haystack>
    struct contains_value : std::integral_constant<bool, detail::contains_value(Needle, Haystack...)> { };
}
