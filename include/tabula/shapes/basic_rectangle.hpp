#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // flip_, flop_, swap_
#include <tabula/lakes.hpp>             // basic_lakes

namespace tabula {

template
<
        int Width,
        int Height,
        class Lakes = basic_lakes<>,
        int Separation = 1
>
struct basic_rectangle
{
        static_assert(0 < Width);
        static_assert(0 < Height);
        static_assert(0 < Separation);

        constexpr static auto width = Width;
        constexpr static auto height = Height;
        using lake_type = Lakes;
        constexpr static auto separation = Separation;

        constexpr static auto size = Width * Height;

        using wrap_type = basic_rectangle<Width + Separation, Height,       Lakes >;
        using flip_type = basic_rectangle<Width             , Height, flip_<Lakes>>;
        using flop_type = basic_rectangle<Width             , Height, flop_<Lakes>>;
        using swap_type = basic_rectangle<Height            , Width , swap_<Lakes>>;
};

}       // namespace tabula
