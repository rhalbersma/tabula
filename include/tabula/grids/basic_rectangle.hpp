#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // compose_, flip_, flop_, swap_
#include <tabula/lake.hpp>              // lake_
#include <tabula/padding.hpp>           // padding
#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // add_padding
#include <tabula/vector.hpp>            // basic_vector
#include <array>                        // array
#include <utility>                      // pair

namespace tabula {

template<int Width, int Height, class Lake = lake_<>>
        requires (0 < Width && 0 < Height)
class basic_rectangle
{
        using   grid_type = basic_rectangle<Width, Height, Lake>;
        using square_type = basic_square<grid_type>;
        using vector_type = basic_vector<grid_type>;

        [[nodiscard]] static constexpr auto is_within(square_type const& square) noexcept
        {
                return
                        0 <= square.file && square.file < Width &&
                        0 <= square.rank && square.rank < Height
                ;
        }

        [[nodiscard]] static constexpr auto is_lake(square_type const& square) noexcept
        {
                return Lake()(square);
        }

public:
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto size   = Width * Height;

        using lake_type = Lake;

        using flipped_type = basic_rectangle<Width, Height, compose_<Lake, flip_>>;
        using flopped_type = basic_rectangle<Width, Height, compose_<Lake, flop_>>;
        using swapped_type = basic_rectangle<Height, Width, compose_<Lake, swap_>>;

        enum : unsigned { N, NE, E, SE, S, SW, W, NW };

        static constexpr auto directions = std::array{
                vector_type{ 0,  1},    // N
                vector_type{ 1,  1},    // NE
                vector_type{ 1,  0},    // E
                vector_type{ 1, -1},    // SE
                vector_type{ 0, -1},    // S
                vector_type{-1, -1},    // SW
                vector_type{-1,  0},    // W
                vector_type{-1,  1}     // NW
        };

        [[nodiscard]] static constexpr auto is_valid(square_type const& square) noexcept
        {
                return is_within(square) && !is_lake(square);
        }

        [[nodiscard]] static constexpr auto index(auto const& coordinates) noexcept
        {
                auto const [ file, rank ] = coordinates;
                return file + rank * Width;
        }

        [[nodiscard]] static constexpr auto square(int index) noexcept
                -> square_type
        {
                return { index % Width, index / Width };
        }
};

template<int Width, int Height, class Lake, padding Padding>
struct add_padding<basic_rectangle<Width, Height, Lake>, Padding>
{
        using type = basic_rectangle
        <
                Width  + Padding.left + Padding.right,
                Height + Padding.top  + Padding.bottom,
                Lake
        >;
};

}       // namespace tabula
