#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <functional>   // identity

namespace tabula {

template<class F>
struct composable
{
        F call;
};

// Explicit deduction guide to support Clang 13, 14, 15, 16-SVN
// https://stackoverflow.com/a/70660785/819272
template<class F>
composable(F) -> composable<F>;

template<class F, class G>
constexpr auto operator>>(composable<F> f, composable<G> g) noexcept
{
        return composable{[=](auto arg) { return f.call(g.call(arg)); }};
}

inline constexpr auto identity = std::identity();
inline constexpr auto composed = [](auto... fs) {
        return (composable{fs} >> ... >> composable{identity}).call;
};

template<class... Fs>
inline constexpr auto compose = [](auto arg) { return composed(Fs()...)(arg); };

template<class... Fs>
using compose_ = decltype(compose<Fs...>);

inline constexpr auto flip = [](auto arg) { return arg.flip(); };
inline constexpr auto flop = [](auto arg) { return arg.flop(); };
inline constexpr auto swap = [](auto arg) { return arg.swap(); };

using flip_ = decltype(flip);
using flop_ = decltype(flop);
using swap_ = decltype(swap);

}       // namespace tabula
