#pragma once
#include <utility>

#define BAKA_EXCEPTION(name, base)                    \
    class name : public base {                        \
    public:                                           \
        template<typename... Args>                    \
        explicit name(Args&&... args)                 \
            : base(::std::forward<Args>(args)...) { } \
    }
