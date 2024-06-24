#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <functional>   // identity
#include <utility>      // forward

namespace tabula {

#define FWD(arg) std::forward<decltype(arg)>(arg)

constexpr auto operator*(auto&& f, auto&& g) noexcept
{
        return [f_ = FWD(f), g_ = FWD(g)](auto&&... args) { return f_(g_(FWD(args)...)); };
}

inline constexpr auto id   = std::identity();
inline constexpr auto flip = [](auto&& arg) { return FWD(arg).flip(); };
inline constexpr auto flop = [](auto&& arg) { return FWD(arg).flop(); };
inline constexpr auto swap = [](auto&& arg) { return FWD(arg).swap(); };

#undef FWD

}       // namespace tabula
