#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // compose_, flip_, flop_, swap_
#include <tabula/lake.hpp>              // basic_lake_
#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // add_padding
#include <tabula/vector.hpp>            // basic_vector
#include <utility>                      // pair

namespace tabula {

template<int Width, int Height, int Parity = 0, class Lake = basic_lake_<>>
        requires (0 < Width &&  0 < Height && (Parity == 0 || Parity == 1))
class chequered_rectangle
{
        using square_type = basic_square<chequered_rectangle<Width, Height, Parity, Lake>>;
        using vector_type = basic_vector<chequered_rectangle<Width, Height, Parity, Lake>>;

        [[nodiscard]] static constexpr auto is_within(square_type const& square) noexcept
        {
                return
                        0 <= square.file && square.file < Width &&
                        0 <= square.rank && square.rank < Height
                ;
        }

        [[nodiscard]] static constexpr auto is_colored(square_type const& square) noexcept
        {
                return !((square.file ^ square.rank ^ Parity) % 2);
        }

        [[nodiscard]] static constexpr auto is_lake(square_type const& square) noexcept
        {
                return Lake()(square);
        }

public:
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto parity = Parity;
        static constexpr auto size   = (Width * Height + !Parity) / 2;

        using lake_type = Lake;

        using flipped_type = chequered_rectangle<Width, Height, Parity ^ !(Height % 2), compose_<Lake, flip_>>;
        using flopped_type = chequered_rectangle<Width, Height, Parity ^ !(Width  % 2), compose_<Lake, flop_>>;
        using swapped_type = chequered_rectangle<Height, Width, Parity,                 compose_<Lake, swap_>>;

        enum : unsigned { N, NE, E, SE, S, SW, W, NW };

        static constexpr auto directions = std::array{
                vector_type{ 0,  2},    // N
                vector_type{ 1,  1},    // NE
                vector_type{ 2,  0},    // E
                vector_type{ 1, -1},    // SE
                vector_type{ 0, -2},    // S
                vector_type{-1, -1},    // SW
                vector_type{-2,  0},    // W
                vector_type{-1,  1}     // NW
        };

        [[nodiscard]] static constexpr auto is_valid(square_type const& square) noexcept
        {
                return is_within(square) && is_colored(square) && !is_lake(square);
        }

        [[nodiscard]] static constexpr auto index(auto const& coordinates) noexcept
        {
                auto const [ file, rank ] = coordinates;
                return (file + rank * Width) / 2;
        }

        [[nodiscard]] static constexpr auto square(int index) noexcept
                -> square_type
        {
                index *= 2;
                index += (Width % 2) ? Parity : Parity ^ ((index / Width) % 2);
                return { index % Width, index / Width };
        }
};

template<int Width, int Height, int Parity, class Lake, class Padding>
struct add_padding<chequered_rectangle<Width, Height, Parity, Lake>, Padding>
{
        using type = chequered_rectangle
        <
                Width  + Padding::left + Padding::right + !((Width + Padding::left + Padding::right) % 2),
                Height + Padding::top  + Padding::bottom,
                Parity ^ (Padding::left % 2) ^ (Padding::bottom % 2),
                Lake
        >;
};

}       // namespace tabula
