#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <charconv>     // from_chars
#include <cstddef>      // size_t
#include <utility>      // get, pair

namespace tabula {

using square_ = std::pair<int, int>;

template<square_... Squares>
struct basic_lake
{
        [[nodiscard]] constexpr auto operator()(auto square [[maybe_unused]]) const noexcept
        {
                return (... || (square == decltype(square){std::get<0>(Squares), std::get<1>(Squares)}));
        }
};

[[nodiscard]] inline constexpr auto algebraic(char file, int rank) noexcept
        -> square_
{
        return { file - 'a',  rank - 1 };
}

[[nodiscard]] inline constexpr auto algebraic(int file, int rank) noexcept
        -> square_
{
        return { file - 1,  rank - 1 };
}

inline namespace literals {
inline namespace square_literals {

[[nodiscard]] constexpr auto operator""_sq(const char* str, std::size_t n) noexcept
        -> square_
{
        auto file = str[0];
        auto rank = 0;
        std::from_chars(str + 1, str + n, rank);
        return { file - 'a',  rank - 1 };
}

}       // namespace square_literals
}       // namespace literals
}       // namespace tabula
