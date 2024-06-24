#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // compose_, flip_, flop_, swap_
#include <tabula/padding.hpp>           // padding
#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // flipped, flopped, swapped, padded
#include <tabula/vector.hpp>            // basic_vector
#include <array>                        // array
#include <utility>                      // pair

namespace tabula {

template<int Width, int Height>
        requires (0 < Width && 0 < Height)
struct basic_rectangle
{
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto size   = Width * Height;

        using type = basic_rectangle<Width, Height>;

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
                return
                        0 <= square.file && square.file < Width &&
                        0 <= square.rank && square.rank < Height
                ;        
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
};

template<int Width, int Height>
struct flipped<basic_rectangle<Width, Height>>
{
        using type = basic_rectangle<Width, Height>;
};

template<int Width, int Height>
struct flopped<basic_rectangle<Width, Height>>
{
        using type = basic_rectangle<Width, Height>;
};

template<int Width, int Height>
struct swapped<basic_rectangle<Width, Height>>
{
        using type = basic_rectangle<Height, Width>;
};

template<int Width, int Height, padding Padding>
struct padded<basic_rectangle<Width, Height>, Padding>
{
        using type = basic_rectangle
        <
                Width  + Padding.left + Padding.right,
                Height + Padding.top  + Padding.bottom
        >;
};

}       // namespace tabula
