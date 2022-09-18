#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // compose_, flip_, flop_, swap_
#include <tabula/lakes.hpp>             // basic_lakes
#include <tabula/square.hpp>            // basic_square
#include <tabula/vector.hpp>            // basic_vector
#include <concepts>                     // regular_invocable

namespace tabula {

template<int Width, int Height, class Lakes = basic_lakes<>>
requires (0 < Width && 0 < Height)
struct basic_rectangle
{
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto size   = Width * Height;

        using lake_type = Lakes;

        using flipped_type = basic_rectangle<Width, Height, compose_<Lakes, flip_>>;
        using flopped_type = basic_rectangle<Width, Height, compose_<Lakes, flop_>>;
        using swapped_type = basic_rectangle<Height, Width, compose_<Lakes, swap_>>;

        template<class Padding>
        using padded_type = basic_rectangle<
                Width  + Padding::left + Padding::right,
                Height + Padding::top  + Padding::bottom,
                Lakes
        >;

        using square_type = basic_square<basic_rectangle>;
        using vector_type = basic_vector<basic_rectangle>;

        [[nodiscard]] static constexpr auto is_within(square_type const& s) noexcept
        {
                return
                        0 <= s.file && s.file < Width &&
                        0 <= s.rank && s.rank < Height
                ;
        }

        [[nodiscard]] static constexpr auto is_lake(square_type const& s) noexcept
                requires std::regular_invocable<Lakes, square_type>
        {
                return Lakes()(s);
        }

        [[nodiscard]] static constexpr auto is_valid(square_type const& s) noexcept
        {
                return is_within(s) && !is_lake(s);
        }

        [[nodiscard]] static constexpr auto square(int const i) noexcept
                -> square_type
        {
                return { i % Width, i / Width };
        }

        [[nodiscard]] static constexpr auto index(square_type const& s) noexcept
        {
                return s.file + s.rank * Width;
        }

        [[nodiscard]] static constexpr auto stride(vector_type const& v) noexcept
        {
                return v.file + v.rank * Width;
        }
};

}       // namespace tabula
