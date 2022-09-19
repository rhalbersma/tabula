#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

template<class... Squares>
struct basic_lake;

template<char File, int Rank>
        requires (File >= 'a' && Rank >= 1)
struct square_;

template<char... Files, int... Ranks>
struct basic_lake<square_<Files, Ranks>...>
{
        template<class Square>
        [[nodiscard]] constexpr auto operator()(Square const& s) const noexcept
        {
                return (... || (s == Square(Files - 'a', Ranks - 1)));
        }
};

}       // namespace tabula
