#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tuple>        // apply, tuple_size

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
        requires (std::tuple_size_v<Tuple> > 0)
constexpr auto min_index_by(Tuple const& tup, UnaryFunction fun)
{
        return std::apply([=](auto head, auto... tail){
                auto min = fun(head);
                auto index = 0;
                auto i = 1;
                ([&](auto elem) {
                        if (auto const result = fun(elem); result < min) {
                                min = result;
                                index = i;
                        }
                        ++i;
                }(tail), ...);
                assert(index < static_cast<int>(std::tuple_size_v<Tuple>));
                return index;
        }, tup);
}

template<class Tuple, class UnaryFunction>
constexpr auto for_each(Tuple const& tup, UnaryFunction fun)
{
        return std::apply([=](auto... elems){
                return (fun(elems), ...);
        }, tup);
}

}       // namespace tabula
