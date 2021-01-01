#pragma once

//          Copyright Rein Halbersma 2019-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

// CSS padding Property: https://www.w3schools.com/cssref/pr_padding.asp

template<int...>
struct basic_padding;

template<int Top, int Right, int Bottom, int Left>
struct basic_padding<Top, Right, Bottom, Left>
{
        static_assert(0 <= Top && 0 <= Right && 0 <= Bottom && 0 <= Left);

        static constexpr auto top       = Top;
        static constexpr auto right     = Right;
        static constexpr auto bottom    = Bottom;
        static constexpr auto left      = Left;
};

template<int Top, int RightLeft, int Bottom>
struct basic_padding<Top, RightLeft, Bottom>
{
        static_assert(0 <= Top && 0 <= RightLeft && 0 <= Bottom);

        static constexpr auto top       = Top;
        static constexpr auto right     = RightLeft;
        static constexpr auto bottom    = Bottom;
        static constexpr auto left      = RightLeft;
};

template<int TopBottom, int RightLeft>
struct basic_padding<TopBottom, RightLeft>
{
        static_assert(0 <= TopBottom && 0 <= RightLeft);

        static constexpr auto top       = TopBottom;
        static constexpr auto right     = RightLeft;
        static constexpr auto bottom    = TopBottom;
        static constexpr auto left      = RightLeft;
};

template<int TopRightBottomLeft>
struct basic_padding<TopRightBottomLeft>
{
        static_assert(0 <= TopRightBottomLeft);

        static constexpr auto top       = TopRightBottomLeft;
        static constexpr auto right     = TopRightBottomLeft;
        static constexpr auto bottom    = TopRightBottomLeft;
        static constexpr auto left      = TopRightBottomLeft;
};

template<int Right>
using right_padding = basic_padding<0, Right, 0, 0>;

}       // namespace tabula
