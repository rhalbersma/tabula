#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

inline constexpr auto idem = [](auto arg) { return arg;        };
inline constexpr auto flip = [](auto arg) { return arg.flip(); };
inline constexpr auto flop = [](auto arg) { return arg.flop(); };
inline constexpr auto swap = [](auto arg) { return arg.swap(); };

[[nodiscard]] constexpr auto operator*(auto f, auto g) noexcept
{
        return [=](auto arg) { return f(g(arg)); };
}

}       // namespace tabula
