#pragma once
#include <array>
#include <baka/variadic.hpp>
#include <cstddef>
#include <ffi.h>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace baka {
    namespace detail {
        template<typename T>
        ffi_type* type();

        template<>
        ffi_type* type<int>() {
            return &::ffi_type_sint;
        }
    }

    template<typename T>
    class bound_function;

    template<typename Ret, typename... Args>
    class bound_function<Ret(Args...)> {
        using fptr_t = Ret(*)(Args...);

    public:
        template<typename F>
        explicit bound_function(F&& function_)
            : function(std::forward<F>(function_))
            , closure(nullptr, &::ffi_closure_free) {
            return_type = detail::type<Ret>();
            argument_types = { detail::type<Args>()... };
            ::ffi_prep_cif(&cif, FFI_DEFAULT_ABI, argument_types.size(), return_type, argument_types.data());

            closure.reset(static_cast<::ffi_closure*>(::ffi_closure_alloc(sizeof(::ffi_closure), &thunk)));
            ::ffi_prep_closure_loc(closure.get(), &cif, &call, this, reinterpret_cast<void*>(thunk));
        }

        operator fptr_t() const {
            return reinterpret_cast<fptr_t>(thunk);
        }

    private:
        static void call(ffi_cif*, void* ret, void** args, void* self_void) {
            auto self = static_cast<bound_function*>(self_void);
            self->template call_<0>(static_cast<Ret*>(ret), args);
        }

        template<std::size_t N, typename... CallArgs>
        typename std::enable_if<N != sizeof...(Args)>::type
        call_(Ret* ret, void** args, CallArgs&&... call_args) {
            call_<N + 1>(ret, args, std::forward<CallArgs>(call_args)..., *static_cast<NthType<N, Args...>*>(args[N]));
        }

        template<std::size_t N, typename... CallArgs>
        typename std::enable_if<N == sizeof...(Args)>::type
        call_(Ret* ret, void**, CallArgs&&... call_args) {
            *ret = function(std::forward<CallArgs>(call_args)...);
        }

        std::function<Ret(Args...)> function;
        ::ffi_cif cif;
        ::ffi_type* return_type;
        std::vector<::ffi_type*> argument_types;
        std::unique_ptr<::ffi_closure, decltype(&::ffi_closure_free)> closure;
        void* thunk; // freed by ::ffi_closure_free
    };
}
