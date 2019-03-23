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
        bool Coloring = true,
        bool IsOrthogonalJumps = false,
        class Lakes = basic_lakes<>
>
struct chequered_rectangle
{
        static_assert(0 < Width);
        static_assert(0 < Height);

        constexpr static auto width = Width;
        constexpr static auto height = Height;
        constexpr static auto coloring = Coloring;
        constexpr static auto is_orthogonal_jumps = IsOrthogonalJumps;
        using lake_type = Lakes;

        constexpr static auto size = (Width * Height + Coloring) / 2;
        constexpr static auto padding = (Width % 2) ? 2 : (IsOrthogonalJumps ? 3 : 1);

        using wrap_type = chequered_rectangle<Width + padding, Height, Coloring                , IsOrthogonalJumps,       Lakes >;
        using flip_type = chequered_rectangle<Width          , Height, Coloring ^ !(Height % 2), IsOrthogonalJumps, flip_<Lakes>>;
        using flop_type = chequered_rectangle<Width          , Height, Coloring ^ !(Width  % 2), IsOrthogonalJumps, flop_<Lakes>>;
        using swap_type = chequered_rectangle<Height         , Width , Coloring                , IsOrthogonalJumps, swap_<Lakes>>;
};

}       // namespace tabula
