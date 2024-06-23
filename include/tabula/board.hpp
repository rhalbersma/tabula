#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/concepts.hpp>          // chequered
#include <tabula/embedding.hpp>         // basic_embedding
#include <tabula/functional.hpp>        // operator*, flip, flop, swap
#include <tabula/padding.hpp>           // padding
#include <tabula/square.hpp>            // basic_square
#include <tabula/tuple.hpp>             // min_index, transform
#include <array>                        // array
#include <cassert>                      // assert
#include <cstddef>                      // size_t
#include <functional>                   // identity
#include <optional>                     // optional
#include <ranges>                       // views
#include <tuple>                        // get, tuple

namespace tabula {

inline constexpr auto orientations = std::tuple
(
        std::identity(),        // origin at bottom-left,  left-to-right, bottom-to-top
        swap,                   // origin at bottom-left,  bottom-to-top, left-to-right
        flip,                   // origin at top-left,     left-to-right, top-to-bottom
        swap * flip,            // origin at top-left,     top-to-bottom, left-to-right
        flop,                   // origin at bottom-right, right-to-left, bottom-to-top
        swap * flop,            // origin at bottom-right, bottom-to-top, right-to-left
        flop * flip,            // origin at top-right,    right-to-left, top-to-bottom
        swap * flop * flip      // origin at top-right,    top-to-bottom, right-to-left
);

template<class Grid, padding Padding>
class basic_board
{
        static constexpr auto min = min_element(
                transform(orientations, [](auto orientation [[maybe_unused]]) {                        
                        return basic_embedding<std::remove_cvref_t<decltype(orientation(Grid()))>, Padding>::valid_size;
                })
        );        
        static constexpr auto orientation = std::get<min>(orientations);
        using embedding = basic_embedding<std::remove_cvref_t<decltype(orientation(Grid()))>, Padding>;

        using    padded_type = padded_t<typename embedding::grid_type, Padding>;

        [[nodiscard]] static constexpr auto pad(auto coordinates) noexcept
        {
                return embedding::pad(orientation(coordinates));
        }

        static constexpr auto embedding_table = []() {
                auto table = std::array<std::optional<int>, Grid::size>{};
                for (auto index : std::views::iota(0, Grid::size)) {
                        if (auto const square = Grid::square(index); square.is_valid()) {
                                table[static_cast<std::size_t>(index)] = pad(square).index();
                        }
                }
                return table;
        }();

public:
        using    grid_type = Grid;

        static constexpr auto width  = Grid::width;
        static constexpr auto height = Grid::height;
        static constexpr auto size   = Grid::size;

        static constexpr auto padded_width  = padded_type::width;
        static constexpr auto padded_height = padded_type::height;
        static constexpr auto padded_size   = padded_type::size;

        static constexpr auto valid_size = embedding::valid_size;

        static constexpr auto is_chequered = chequered<Grid>;

        static constexpr auto parity() noexcept
                requires is_chequered
        {
                return Grid::parity;
        }

        static constexpr auto padded_parity() noexcept
                requires is_chequered
        {
                return padded_type::parity;
        }

        static constexpr auto square(int file, int rank) noexcept
                -> basic_square<Grid>
        {
                return { file, rank };
        }

        static constexpr auto sequential0(basic_square<Grid> square) noexcept
        {
                return square.flip().index();
        }

        static constexpr auto sequential1(basic_square<Grid> square) noexcept
        {
                return sequential0(square) + 1;
        }

        static constexpr auto embedded(basic_square<Grid> square) noexcept
        {
                assert(square.is_valid());
                return *embedding_table[static_cast<std::size_t>(square.index())];
        }

        static constexpr auto strides = []() {
                std::array<int, Grid::directions.size()> table;
                for (auto index = std::size_t(0); auto direction : Grid::directions) {
                        table[index++] = pad(direction).stride();
                }
                return table;
        }();
};

}   // namespace tabula
