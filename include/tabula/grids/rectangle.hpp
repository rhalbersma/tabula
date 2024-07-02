#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/compass.hpp>   // basic_compass
#include <tabula/concepts.hpp>  // rectangular
#include <tabula/padding.hpp>   // padding
#include <tabula/vector.hpp>    // basic_vector
#include <array>                // array
#include <utility>              // pair

namespace tabula {

struct rectangle
{
        int width;
        int height;

        [[nodiscard]] constexpr auto operator==(rectangle const&) const noexcept -> bool = default;
        
        [[nodiscard]] constexpr auto size() const noexcept
        {
                return width * height;
        }

        [[nodiscard]] constexpr auto is_valid(auto coordinates) const noexcept
        {
                auto const [ file, rank ] = coordinates;
                return
                        0 <= file && file < width &&
                        0 <= rank && rank < height
                ;        
        }

        [[nodiscard]] constexpr auto index(auto coordinates) const noexcept
        {
                auto const [ file, rank ] = coordinates;
                return file + rank * width;
        }

        [[nodiscard]] constexpr auto coordinates(int index) const noexcept
                -> std::pair<int, int>
        {
                return { index % width, index / width };
        }       

        [[nodiscard]] constexpr auto flip() const noexcept 
                -> rectangle
        { 
                return { width, height }; 
        }

        [[nodiscard]] constexpr auto flop() const noexcept 
                -> rectangle
        { 
                return { width, height }; 
        }

        [[nodiscard]] constexpr auto swap() const noexcept 
                -> rectangle
        { 
                return { height, width }; 
        }

        [[nodiscard]] constexpr auto pad(padding p) const noexcept
                -> rectangle
        {
                return  
                {
                        width  + p.left + p.right,
                        height + p.top  + p.bottom
                };
        }
};

template<rectangle Grid>
struct basic_compass<rectangle, Grid>
{
        static constexpr auto grid = Grid;
        enum : unsigned { N, NE, E, SE, S, SW, W, NW };
        static constexpr auto directions = std::array<basic_vector<Grid>, 8>
        {{
                {  0,  1 },     // N
                {  1,  1 },     // NE
                {  1,  0 },     // E
                {  1, -1 },     // SE
                {  0, -1 },     // S
                { -1, -1 },     // SW
                { -1,  0 },     // W
                { -1,  1 }      // NW
        }};
};

}       // namespace tabula
