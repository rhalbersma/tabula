#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // compose_, flip_, flop_, swap_
#include <tabula/lake.hpp>              // basic_lake
#include <tabula/square.hpp>            // basic_square
#include <tabula/vector.hpp>            // basic_vector
#include <concepts>                     // regular_invocable

namespace tabula {

template<int Width, int Height, class Lake = basic_lake<>>
        requires (0 < Width && 0 < Height)
struct basic_rectangle
{
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto size   = Width * Height;

        using lake_type = Lake;

        using flipped_type = basic_rectangle<Width, Height, compose_<Lake, flip_>>;
        using flopped_type = basic_rectangle<Width, Height, compose_<Lake, flop_>>;
        using swapped_type = basic_rectangle<Height, Width, compose_<Lake, swap_>>;

        template<class Padding>
        using padded = basic_rectangle<
                Width  + Padding::left + Padding::right,
                Height + Padding::top  + Padding::bottom,
                Lake
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
                requires std::regular_invocable<Lake, square_type>
        {
                return Lake()(s);
        }

        [[nodiscard]] static constexpr auto is_valid(square_type const& s) noexcept
        {
                return is_within(s) && !is_lake(s);
        }

        [[nodiscard]] static constexpr auto square(int index) noexcept
                -> square_type
        {
                return { index % Width, index / Width };
        }

        [[nodiscard]] static constexpr auto index(auto arg) noexcept
        {
                return arg.file + arg.rank * Width;
        }
};

}       // namespace tabula
