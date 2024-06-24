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

struct basic_rectangle
{
        int width;
        int height;
        
        [[nodiscard]] constexpr auto size() const noexcept
        {
                return width * height;
        }

        bool operator==(const basic_rectangle&) const = default;
        
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
                -> basic_rectangle
        { 
                return { width, height }; 
        }

        [[nodiscard]] constexpr auto flop() const noexcept 
                -> basic_rectangle
        { 
                return { width, height }; 
        }

        [[nodiscard]] constexpr auto swap() const noexcept 
                -> basic_rectangle
        { 
                return { height, width }; 
        }

        template<padding Padding>
        [[nodiscard]] constexpr auto pad() const noexcept
                -> basic_rectangle
        {
                return 
                {
                        width  + Padding.left + Padding.right,
                        height + Padding.top  + Padding.bottom
                };
        }
};

template<basic_rectangle Grid>
struct basic_compass<Grid>
{
        static constexpr auto grid = Grid;
        enum : unsigned { N, NE, E, SE, S, SW, W, NW };
        static constexpr auto directions = std::array
        {
                basic_vector<Grid>{  0,  1 },   // N
                basic_vector<Grid>{  1,  1 },   // NE
                basic_vector<Grid>{  1,  0 },   // E
                basic_vector<Grid>{  1, -1 },   // SE
                basic_vector<Grid>{  0, -1 },   // S
                basic_vector<Grid>{ -1, -1 },   // SW
                basic_vector<Grid>{ -1,  0 },   // W
                basic_vector<Grid>{ -1,  1 }    // NW
        };
};

}       // namespace tabula
