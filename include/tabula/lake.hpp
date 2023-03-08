#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <utility>      // get, pair

namespace tabula {

// Only works for gcc 12 and above.
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=97930
using square_ = std::pair<int, int>;

template<square_... Squares>
struct lake_
{
        [[nodiscard]] constexpr auto operator()(auto square) const noexcept
        {
                return (... || (square == decltype(square){std::get<0>(Squares), std::get<1>(Squares)}));
        }
};

[[nodiscard]] inline constexpr auto algebraic(char file, int rank) noexcept
{
        return square_{file - 'a',  rank - 1};
}

}       // namespace tabula
