#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <functional>   // identity
#include <utility>      // forward

namespace tabula {

#define FWD(arg) std::forward<decltype(arg)>(arg)

constexpr auto operator*(auto&& f, auto&& g) noexcept
{
        return [f = FWD(f), g = FWD(g)](auto&&... args) { return f(g(FWD(args)...)); };
}

template<class... Fs>
inline constexpr auto compose = [](auto&&... args) { return (Fs() * ... * std::identity())(FWD(args)...); };

template<class... Fs>
using compose_ = decltype(compose<Fs...>);

inline constexpr auto flip = [](auto&& arg) { return FWD(arg).flip(); };
inline constexpr auto flop = [](auto&& arg) { return FWD(arg).flop(); };
inline constexpr auto swap = [](auto&& arg) { return FWD(arg).swap(); };

using flip_ = decltype(flip);
using flop_ = decltype(flop);
using swap_ = decltype(swap);

}       // namespace tabula
