#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // compose_, flip_, flop_, swap_
#include <tabula/lake.hpp>              // basic_lake
#include <tabula/padding.hpp>           // padding
#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // flipped, flopped, swapped, padded
#include <tabula/vector.hpp>            // basic_vector
#include <array>                        // array
#include <utility>                      // pair

namespace tabula {

template<int Width, int Height, class Lake = basic_lake<>>
        requires (0 < Width && 0 < Height)
class basic_rectangle
{
public:
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto size   = Width * Height;

        using lake_type = Lake;
        using      type = basic_rectangle<Width, Height, Lake>;

        enum : unsigned { N, NE, E, SE, S, SW, W, NW };

        static constexpr auto directions = std::array
        {
                basic_vector<type>{  0,  1 },   // N
                basic_vector<type>{  1,  1 },   // NE
                basic_vector<type>{  1,  0 },   // E
                basic_vector<type>{  1, -1 },   // SE
                basic_vector<type>{  0, -1 },   // S
                basic_vector<type>{ -1, -1 },   // SW
                basic_vector<type>{ -1,  0 },   // W
                basic_vector<type>{ -1,  1 }    // NW
        };

        [[nodiscard]] static constexpr auto is_valid(basic_square<type> square) noexcept
        {
                return is_within(square) && !is_lake(square);
        }

        [[nodiscard]] static constexpr auto index(auto coordinates) noexcept
        {
                auto const [ file, rank ] = coordinates;
                return file + rank * Width;
        }

        [[nodiscard]] static constexpr auto square(int index) noexcept
                -> basic_square<type>
        {
                return { index % Width, index / Width };
        }       

        [[nodiscard]] static constexpr auto flip() noexcept -> flipped_t<type> { return {}; }
        [[nodiscard]] static constexpr auto flop() noexcept -> flopped_t<type> { return {}; }
        [[nodiscard]] static constexpr auto swap() noexcept -> swapped_t<type> { return {}; }  

private:
        [[nodiscard]] static constexpr auto is_within(basic_square<type> square) noexcept
        {
                return
                        0 <= square.file && square.file < Width &&
                        0 <= square.rank && square.rank < Height
                ;
        }

        [[nodiscard]] static constexpr auto is_lake(basic_square<type> square) noexcept
        {
                return Lake()(square);
        }
};

template<int Width, int Height, class Lake>
struct flipped<basic_rectangle<Width, Height, Lake>>
{
        using type = basic_rectangle<Width, Height, compose_<Lake, flip_>>;
};

template<int Width, int Height, class Lake>
struct flopped<basic_rectangle<Width, Height, Lake>>
{
        using type = basic_rectangle<Width, Height, compose_<Lake, flop_>>;
};

template<int Width, int Height, class Lake>
struct swapped<basic_rectangle<Width, Height, Lake>>
{
        using type = basic_rectangle<Height, Width, compose_<Lake, swap_>>;
};

template<int Width, int Height, class Lake, padding Padding>
struct padded<basic_rectangle<Width, Height, Lake>, Padding>
{
        using type = basic_rectangle
        <
                Width  + Padding.left + Padding.right,
                Height + Padding.top  + Padding.bottom,
                Lake
        >;
};

}       // namespace tabula
