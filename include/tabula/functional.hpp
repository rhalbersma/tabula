#pragma once

//          Copyright Rein Halbersma 2019-2021.
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

inline constexpr auto compose = [](auto... fs) {
        return (composable(fs) >> ... >> composable(identity)).call;
};

template<class... Fs>
struct compose_
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return compose(Fs()...)(arg);
        }
};

struct flip_
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return arg.flip();
        }
};

struct flop_
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return arg.flop();
        }
};

struct swap_
{
        constexpr auto operator()(auto arg) const noexcept
        {
                return arg.swap();
        }
};

inline constexpr auto flip = flip_();
inline constexpr auto flop = flop_();
inline constexpr auto swap = swap_();

}       // namespace tabula
