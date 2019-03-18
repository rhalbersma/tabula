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
        class Lakes = basic_lakes<>
>
struct basic_rectangle
{
        static_assert(0 < Width);
        static_assert(0 < Height);

        constexpr static auto width = Width;
        constexpr static auto height = Height;
        using lake_type = Lakes;

        constexpr static auto size = Width * Height;
        constexpr static auto padding = 1;

        using wrap_type = basic_rectangle<Width + padding, Height,       Lakes >;
        using flip_type = basic_rectangle<Width          , Height, flip_<Lakes>>;
        using flop_type = basic_rectangle<Width          , Height, flop_<Lakes>>;
        using swap_type = basic_rectangle<Height         , Width , swap_<Lakes>>;
};

}       // namespace tabula

