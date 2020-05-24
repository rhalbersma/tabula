#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // _compose, _flip, _flop, _swap
#include <tabula/lakes.hpp>             // basic_lakes
#include <tabula/square.hpp>            // basic_square
#include <tabula/vector.hpp>            // basic_vector

namespace tabula {

template<
        int Width,
        int Height,
        bool Coloring = true,
        class Lakes = basic_lakes<>
>
struct chequered_rectangle
{
        static_assert(0 < Width);
        static_assert(0 < Height);

        static constexpr auto width    = Width;
        static constexpr auto height   = Height;
        static constexpr auto coloring = Coloring;
        static constexpr auto area     = (Width * Height + Coloring) / 2;

        using    lake_type = Lakes;

        using flipped_type = chequered_rectangle<Width, Height, Coloring ^ !(Height % 2), _compose<Lakes, _flip>>;
        using flopped_type = chequered_rectangle<Width, Height, Coloring ^ !(Width  % 2), _compose<Lakes, _flop>>;
        using swapped_type = chequered_rectangle<Height, Width, Coloring,                 _compose<Lakes, _swap>>;

        template<class Padding>
        using padded_type = chequered_rectangle<
                Width + Padding::left + Padding::right,
                Height + Padding::top + Padding::bottom,
                Coloring ^ (Padding::left % 2) ^ (Padding::bottom % 2),
                Lakes
        >;

        using square_type = basic_square<chequered_rectangle>;
        using vector_type = basic_vector<chequered_rectangle>;

        static constexpr auto is_within(square_type const& s) noexcept
        {
                return
                        0 <= s.file && s.file < Width &&
                        0 <= s.rank && s.rank < Height
                ;
        }

        static constexpr auto is_colored(square_type const& s) noexcept
        {
                return (s.file ^ s.rank ^ Coloring) % 2;
        }

        static constexpr auto is_lake(square_type const& s) noexcept
        {
                return Lakes()(s);
        }

        static constexpr auto is_valid(square_type const& s) noexcept
        {
                return is_within(s) && is_colored(s) && !is_lake(s);
        }

        static constexpr auto index(square_type const& s) noexcept
        {
                return (s.file + s.rank * Width) / 2;
        }

        static constexpr auto stride(vector_type const& v) noexcept
        {
                return (v.file + v.rank * Width) / 2;
        }
};

}       // namespace tabula
