#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/compass.hpp>   // basic_compass
#include <tabula/padding.hpp>   // padding
#include <tabula/vector.hpp>    // basic_vector
#include <array>                // array
#include <utility>              // pair

namespace tabula {

struct basic_chequered
{
        int width;
        int height;
        int parity = 0;

        [[nodiscard]] constexpr auto size() const noexcept
        {
                return (width * height + !parity) / 2;
        }

        bool operator==(const basic_chequered&) const = default;

        [[nodiscard]] constexpr auto is_valid(auto coordinates) const noexcept
        {
                auto const [ file, rank ] = coordinates;
                return
                        0 <= file && file < width &&
                        0 <= rank && rank < height &&
                        !((file ^ rank ^ parity) % 2)
                ;
        }

        [[nodiscard]] constexpr auto index(auto coordinates) const noexcept
        {
                auto const [ file, rank ] = coordinates;
                return (file + rank * width) / 2;
        }

        [[nodiscard]] constexpr auto coordinates(int index) const noexcept
                -> std::pair<int, int>
        {
                index *= 2;
                index += (width % 2) ? parity : parity ^ ((index / width) % 2);
                return { index % width, index / width };
        }

        [[nodiscard]] constexpr auto flip() const noexcept 
                -> basic_chequered
        { 
                return { width, height, parity ^ !(height % 2) }; 
        }
        
        [[nodiscard]] constexpr auto flop() const noexcept 
                -> basic_chequered
        { 
                return { width, height, parity ^ !(width  % 2) }; 
        }

        [[nodiscard]] constexpr auto swap() const noexcept 
                -> basic_chequered
        { 
                return { height, width, parity }; 
        }

        template<padding Padding>
        [[nodiscard]] constexpr auto pad() const noexcept 
                -> basic_chequered
        { 
                return 
                {
                        width  + Padding.left + Padding.right + !((width + Padding.left + Padding.right) % 2),
                        height + Padding.top  + Padding.bottom,
                        parity ^ (Padding.left % 2) ^ (Padding.bottom % 2)
                }; 
        }
};

template<basic_chequered Grid>
struct basic_compass<Grid>
{       
        static constexpr auto grid = Grid;
        enum : unsigned { N, NE, E, SE, S, SW, W, NW };
        static constexpr auto directions = std::array
        {
                basic_vector<Grid>{  0,  2 },   // N
                basic_vector<Grid>{  1,  1 },   // NE
                basic_vector<Grid>{  2,  0 },   // E
                basic_vector<Grid>{  1, -1 },   // SE
                basic_vector<Grid>{  0, -2 },   // S
                basic_vector<Grid>{ -1, -1 },   // SW
                basic_vector<Grid>{ -2,  0 },   // W
                basic_vector<Grid>{ -1,  1 }    // NW
        };
};

}       // namespace tabula
