#pragma once

//          Copyright Rein Halbersma 2019-2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/compass.hpp>   // basic_compass
#include <tabula/concepts.hpp>  // chequered
#include <tabula/padding.hpp>   // padding
#include <tabula/vector.hpp>    // basic_vector
#include <array>                // array
#include <utility>              // pair

namespace tabula {

struct chequer
{
        int width;
        int height;
        bool parity;

        [[nodiscard]] constexpr auto operator==(chequer const&) const noexcept -> bool = default;

        [[nodiscard]] constexpr auto size() const noexcept
        {
                return (width * height + !parity) / 2;
        }

        [[nodiscard]] constexpr auto is_valid(auto coordinates) const noexcept
        {
                auto const [ file, rank ] = coordinates;
                return
                        0 <= file && file < width &&
                        0 <= rank && rank < height &&
                        (file + rank) % 2 == parity
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
                index += (width % 2) ? parity : parity != (index / width) % 2;
                return { index % width, index / width };
        }

        [[nodiscard]] constexpr auto flip() const noexcept 
                -> chequer
        { 
                return { width, height, parity == height % 2 }; 
        }
        
        [[nodiscard]] constexpr auto flop() const noexcept 
                -> chequer
        { 
                return { width, height, parity == width % 2 }; 
        }

        [[nodiscard]] constexpr auto swap() const noexcept 
                -> chequer
        { 
                return { height, width, parity }; 
        }

        [[nodiscard]] constexpr auto pad(padding p) const noexcept 
                -> chequer
        { 
                return 
                {
                        width  + p.left + p.right + (width + p.left + p.right + 1) % 2,
                        height + p.top  + p.bottom,
                        parity != (p.left + p.bottom) % 2
                }; 
        }
};

template<chequer Grid>
struct basic_compass<Grid>
{       
        static constexpr auto grid = Grid;
        enum : unsigned { N, NE, E, SE, S, SW, W, NW };
        static constexpr auto directions = std::array<basic_vector<Grid>, 8>
        {{
                {  0,  2 },     // N
                {  1,  1 },     // NE
                {  2,  0 },     // E
                {  1, -1 },     // SE
                {  0, -2 },     // S
                { -1, -1 },     // SW
                { -2,  0 },     // W
                { -1,  1 }      // NW
        }};
};

}       // namespace tabula
