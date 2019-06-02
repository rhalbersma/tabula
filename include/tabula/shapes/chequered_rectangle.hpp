#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // flip_, flop_, swap_
#include <tabula/lakes.hpp>             // basic_lakes

namespace tabula {

template<int Width, int Height, bool Coloring = true, class Lakes = basic_lakes<>>
struct chequered_rectangle
{
        static_assert(0 < Width);
        static_assert(0 < Height);

        static constexpr auto width = Width;
        static constexpr auto height = Height;
        static constexpr auto coloring = Coloring;
        static constexpr auto size = (Width * Height + Coloring) / 2;

        using lake_type = Lakes;
        using flip_type = chequered_rectangle<Width, Height, Coloring ^ !(Height % 2), flip_<Lakes>>;
        using flop_type = chequered_rectangle<Width, Height, Coloring ^ !(Width  % 2), flop_<Lakes>>;
        using swap_type = chequered_rectangle<Height, Width, Coloring,                 swap_<Lakes>>;

        template<class Padding>
        using padded_type = chequered_rectangle<
                Width + Padding::left + Padding::right,
                Height + Padding::top + Padding::bottom,
                Coloring ^ (Padding::bottom % 2) ^ (Padding::left % 2),
                Lakes
        >;
};

}       // namespace tabula
