#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

template<class... Squares>
struct basic_lake_;

template<int File, int Rank>
        requires (0 <= File && 0 <= Rank)
struct basic_square_;

template<char File, int Rank>
        requires ('a' <= File && 1 <= Rank)
using algebraic_ = basic_square_<File - 'a', Rank - 1>;

template<int... Files, int... Ranks>
struct basic_lake_<basic_square_<Files, Ranks>...>
{
        [[nodiscard]] constexpr auto operator()(auto square) const noexcept
        {
                return (... || (square == decltype(square){Files, Ranks}));
        }
};

}       // namespace tabula
