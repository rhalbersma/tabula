#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // flip_, flop_, swap_
#include <tabula/lakes.hpp>             // basic_lakes

namespace tabula {

template<int Width, int Height, class Lakes = basic_lakes<>>
struct basic_rectangle
{
        static_assert(0 < Width);
        static_assert(0 < Height);

        static constexpr auto width = Width;
        static constexpr auto height = Height;
        static constexpr auto area = Width * Height;

        using lake_type = Lakes;
        using flip_type = basic_rectangle<Width, Height, flip_<Lakes>>;
        using flop_type = basic_rectangle<Width, Height, flop_<Lakes>>;
        using swap_type = basic_rectangle<Height, Width, swap_<Lakes>>;

        template<class Padding>
        using padded_type = basic_rectangle<
                Width + Padding::left + Padding::right,
                Height + Padding::top + Padding::bottom,
                Lakes
        >;
};

}       // namespace tabula
