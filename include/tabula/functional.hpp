#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

template<class F>
struct composable
{
        F call;
};

template<class F, class G>
constexpr auto operator>>(composable<F> f, composable<G> g) noexcept
{
        return composable([=](auto arg) {
                return f.call(g.call(arg));
        });
}

inline constexpr auto identity = [](auto arg) { return arg; };

inline constexpr auto compose = [](auto... funs) {
        return (composable(funs) >> ... >> composable(identity)).call;
};

template<class... Fs>
struct _compose
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return compose(Fs()...)(arg);
        }
};

struct _flip
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return arg.flip();
        }
};

struct _flop
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return arg.flop();
        }
};

struct _swap
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return arg.swap();
        }
};

inline constexpr auto flip = _flip();
inline constexpr auto flop = _flop();
inline constexpr auto swap = _swap();

}       // namespace tabula
