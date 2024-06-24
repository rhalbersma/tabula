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
#include <utility>                      // pair

namespace tabula {

template<int Width, int Height, int Parity = 0>
        requires (0 < Width &&  0 < Height && (Parity == 0 || Parity == 1))
struct basic_chequered
{
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto parity = Parity;
        static constexpr auto size   = (Width * Height + !Parity) / 2;

        using type = basic_chequered<Width, Height, Parity>;

        enum : unsigned { N, NE, E, SE, S, SW, W, NW };

        static constexpr auto directions = std::array
        {
                basic_vector<type>{  0,  2 },   // N
                basic_vector<type>{  1,  1 },   // NE
                basic_vector<type>{  2,  0 },   // E
                basic_vector<type>{  1, -1 },   // SE
                basic_vector<type>{  0, -2 },   // S
                basic_vector<type>{ -1, -1 },   // SW
                basic_vector<type>{ -2,  0 },   // W
                basic_vector<type>{ -1,  1 }    // NW
        };

        [[nodiscard]] static constexpr auto is_valid(basic_square<type> square) noexcept
        {
                return
                        0 <= square.file && square.file < Width &&
                        0 <= square.rank && square.rank < Height &&
                        !((square.file ^ square.rank ^ Parity) % 2)
                ;
        }

        [[nodiscard]] static constexpr auto index(auto coordinates) noexcept
        {
                auto const [ file, rank ] = coordinates;
                return (file + rank * Width) / 2;
        }

        [[nodiscard]] static constexpr auto square(int index) noexcept
                -> basic_square<type>
        {
                index *= 2;
                index += (Width % 2) ? Parity : Parity ^ ((index / Width) % 2);
                return { index % Width, index / Width };
        }

        [[nodiscard]] static constexpr auto flip() noexcept -> flipped_t<type> { return {}; }
        [[nodiscard]] static constexpr auto flop() noexcept -> flopped_t<type> { return {}; }
        [[nodiscard]] static constexpr auto swap() noexcept -> swapped_t<type> { return {}; }
};

template<int Width, int Height, int Parity>
struct flipped<basic_chequered<Width, Height, Parity>>
{
        using type = basic_chequered<Width, Height, Parity ^ !(Height % 2)>;
};

template<int Width, int Height, int Parity>
struct flopped<basic_chequered<Width, Height, Parity>>
{
        using type = basic_chequered<Width, Height, Parity ^ !(Width  % 2)>;
};

template<int Width, int Height, int Parity>
struct swapped<basic_chequered<Width, Height, Parity>>
{
        using type = basic_chequered<Height, Width, Parity>;
};

template<int Width, int Height, int Parity, padding Padding>
struct padded<basic_chequered<Width, Height, Parity>, Padding>
{
        using type = basic_chequered
        <
                Width  + Padding.left + Padding.right + !((Width + Padding.left + Padding.right) % 2),
                Height + Padding.top  + Padding.bottom,
                Parity ^ (Padding.left % 2) ^ (Padding.bottom % 2)
        >;
};

}       // namespace tabula
