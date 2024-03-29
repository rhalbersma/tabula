#pragma once

//          Copyright Rein Halbersma 2019-2023.
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

inline constexpr auto orientations = std::tuple(
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
        static constexpr auto basic_embedding_v = basic_embedding<Grid, Padding>();
        static constexpr auto idx = min_index(
                transform(orientations, [](auto fun) {
                        return fun(basic_embedding_v).valid_range;
                })
        );
        static constexpr auto transform_v = std::get<idx>(orientations);
        static constexpr auto embedding_v = transform_v(basic_embedding_v);

        using embedding_type = decltype(embedding_v);
        using    padded_type = padded_t<embedding_type>;
        using    square_type = basic_square<Grid>;

        [[nodiscard]] static constexpr auto pad(auto const& coordinates) noexcept
        {
                return embedding_v.pad(transform_v(coordinates));
        }

        static constexpr auto padded_table = []() {
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

        static constexpr auto valid_range = embedding_type::valid_range;

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
                -> square_type
        {
                return { file, rank };
        }

        static constexpr auto sequential0(square_type const& s) noexcept
        {
                return s.flip().index();
        }

        static constexpr auto sequential1(square_type const& s) noexcept
        {
                return sequential0(s) + 1;
        }

        static constexpr auto padded(square_type const& s) noexcept
        {
                assert(s.is_valid());
                return *padded_table[static_cast<std::size_t>(s.index())];
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
