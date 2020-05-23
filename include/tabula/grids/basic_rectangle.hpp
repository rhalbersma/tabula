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
        class Lakes = basic_lakes<>
>
struct basic_rectangle
{
        static_assert(0 < Width);
        static_assert(0 < Height);

        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto area   = Width * Height;

        using   lake_type = Lakes;

        using flipped_type = basic_rectangle<Width, Height, _compose<Lakes, _flip>>;
        using flopped_type = basic_rectangle<Width, Height, _compose<Lakes, _flop>>;
        using swapped_type = basic_rectangle<Height, Width, _compose<Lakes, _swap>>;

        template<class Padding>
        using padded_type = basic_rectangle<
                Width + Padding::left + Padding::right,
                Height + Padding::top + Padding::bottom,
                Lakes
        >;

        using square_type = basic_square<basic_rectangle>;
        using vector_type = basic_vector<basic_rectangle>;

        static constexpr auto is_within(square_type const& s) noexcept
        {
                return
                        0 <= s.file && s.file < Width &&
                        0 <= s.rank && s.rank < Height
                ;
        }

        static constexpr auto is_lake(square_type const& s) noexcept
        {
                return Lakes()(s);
        }

        static constexpr auto is_valid(square_type const& s) noexcept
        {
                return is_within(s) && !is_lake(s);
        }

        static constexpr auto index(square_type const& s) noexcept
        {
                return s.file + s.rank * Width;
        }

        static constexpr auto stride(vector_type const& v) noexcept
        {
                return v.file + v.rank * Width;
        }
};

}       // namespace tabula
