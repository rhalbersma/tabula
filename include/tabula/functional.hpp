#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

template<class UnaryFunction>
struct flip_
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return UnaryFunction()(arg.flip());
        }
};

template<class UnaryFunction>
struct flop_
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return UnaryFunction()(arg.flop());
        }
};

template<class UnaryFunction>
struct swap_
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return UnaryFunction()(arg.swap());
        }
};

inline constexpr auto keep_arg = [](auto arg) { return arg;        };
inline constexpr auto flip_arg = [](auto arg) { return arg.flip(); };
inline constexpr auto flop_arg = [](auto arg) { return arg.flop(); };
inline constexpr auto swap_arg = [](auto arg) { return arg.swap(); };

template<class F>
struct composable
{
        F call;
};

template<class F, class G>
constexpr auto operator>>(composable<F> f, composable<G> g)
{
        return composable([=](auto arg) {
                return f.call(g.call(arg));
        });
}

inline constexpr auto compose = [](auto... funs) {
        return (composable(funs) >> ... >> composable(keep_arg)).call;
};

}       // namespace tabula
