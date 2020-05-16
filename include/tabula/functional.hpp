#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <limits>       // max
#include <tuple>        // apply, get, tuple_size

namespace tabula {

template<class UnaryFunction>
struct flip_
{
        template<class Arg>
        constexpr auto operator()(Arg const& arg) const noexcept
        {
                return UnaryFunction{}(arg.flip());
        }
};

template<class UnaryFunction>
struct flop_
{
        template<class Arg>
        constexpr auto operator()(Arg const& arg) const noexcept
        {
                return UnaryFunction{}(arg.flop());
        }
};

template<class UnaryFunction>
struct swap_
{
        template<class Arg>
        constexpr auto operator()(Arg const& arg) const noexcept
        {
                return UnaryFunction{}(arg.swap());
        }
};

inline constexpr auto keep_arg = [](auto arg) { return arg;        };
inline constexpr auto flip_arg = [](auto arg) { return arg.flip(); };
inline constexpr auto flop_arg = [](auto arg) { return arg.flop(); };
inline constexpr auto swap_arg = [](auto arg) { return arg.swap(); };

constexpr auto operator>>(auto f, auto g)
{
        return [=](auto arg) { return f(g(arg)); };
}

inline constexpr auto compose = [](auto... funs) { return (funs >> ... >> keep_arg); };

template<class Tuple, class UnaryFunction>
constexpr auto min_element_by(Tuple const& tup, UnaryFunction fun)
{
        if constexpr (std::tuple_size_v<Tuple> == 0) {
                return 0;
        } else {
                auto i = 0;
                auto idx = i;
                auto min = std::numeric_limits<decltype(fun(std::get<0>(tup)))>::max();
                std::apply([&](auto... elems){
                        ([&](auto elem) {
                                auto const r = fun(elem);
                                if (r < min) {
                                        idx = i;
                                        min = r;
                                }
                                ++i;
                        }(elems), ...);
                }, tup);
                return idx;
        }
}

}       // namespace tabula
