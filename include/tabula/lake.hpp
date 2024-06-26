#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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

}       // namespace tabula
