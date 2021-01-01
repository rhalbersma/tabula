#pragma once

//          Copyright Rein Halbersma 2019-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/compass.hpp>           // basic_compass
#include <tabula/embedding.hpp>         // basic_embedding
#include <tabula/functional.hpp>        // compose, identity, flip, flop, swap
#include <tabula/lakes.hpp>             // basic_lakes
#include <tabula/square.hpp>            // basic_square
#include <tabula/tuple.hpp>             // min_index, transform
#include <tabula/type_traits.hpp>       // square_t, vector_t
#include <tabula/vector.hpp>            // basic_vector
#include <array>                        // array
#include <cassert>                      // assert
#include <cstddef>                      // size_t
#include <optional>                     // optional
#include <tuple>                        // get, tuple

namespace tabula {

inline constexpr auto orientations = std::tuple(
        identity,                       // origin at bottom-left,  left-to-right, bottom-to-top
        swap,                           // origin at bottom-left,  bottom-to-top, left-to-right
        flip,                           // origin at top-left,     left-to-right, top-to-bottom
        compose(swap, flip),            // origin at top-left,     top-to-bottom, left-to-right
        flop,                           // origin at bottom-right, right-to-left, bottom-to-top
        compose(swap, flop),            // origin at bottom-right, bottom-to-top, right-to-left
        compose(flop, flip),            // origin at top-right,    right-to-left, top-to-bottom
        compose(swap, flop, flip)       // origin at top-right,    top-to-bottom, right-to-left
);

template<class Grid, class Padding>
class basic_board
{
        static constexpr auto basic_embedding_v = basic_embedding<Grid, Padding>();
        static constexpr auto idx = min_index(
                transform(orientations, [](auto fun) {
                        return fun(basic_embedding_v).valid_size;
                })
        );
        static constexpr auto transform_v = std::get<idx>(orientations);
        static constexpr auto embedding_v = transform_v(basic_embedding_v);

        using     embedding_type = decltype(embedding_v);
        using        padded_grid = typename embedding_type::padded_grid;
        using        square_type = basic_square<Grid>;
        using        vector_type = basic_vector<Grid>;
        using padded_square_type = square_t<padded_grid>;
        using padded_vector_type = vector_t<padded_grid>;

        static constexpr auto pad(square_type const& s) noexcept
        {
                return embedding_v.pad(transform_v(s));
        }

        static constexpr auto pad(vector_type const& v) noexcept
                -> padded_vector_type
        {
                auto const w = transform_v(v);
                return { w.file, w.rank };
        }

        static constexpr auto padded_table = []() {
                std::array<std::optional<int>, Grid::size> table{};
                for (auto r = 0; r < Grid::height; ++r) {
                        for (auto f = 0; f < Grid::width; ++f) {
                                if (auto const sq = square_type(f, r); sq.is_valid()) {
                                        table[static_cast<std::size_t>(sq.index())] = pad(sq).index();
                                }
                        }
                }
                return table;
        }();

public:
        using    grid_type = Grid;
        using padding_type = Padding;

        static constexpr auto width  = Grid::width;
        static constexpr auto height = Grid::height;
        static constexpr auto size   = Grid::size;

        static constexpr auto padded_width  = padded_grid::width;
        static constexpr auto padded_height = padded_grid::height;
        static constexpr auto padded_size   = padded_grid::size;

        static constexpr auto valid_range = embedding_type::valid_range;
        static constexpr auto valid_size  = embedding_type::valid_size;

        static constexpr auto is_chequered = is_chequered_v<Grid>;

        static constexpr auto coloring() noexcept
                requires is_chequered
        {
                return Grid::coloring;
        }

        static constexpr auto padded_coloring() noexcept
                requires is_chequered
        {
                return padded_grid::coloring;
        }

        static constexpr auto square(int f, int r) noexcept
                -> square_type
        {
                return { f, r };
        }

        static constexpr auto sequential0(square_type const& sq) noexcept
        {
                return sq.flip().index();
        }

        static constexpr auto sequential1(square_type const& sq) noexcept
        {
                return sequential0(sq) + 1;
        }

        static constexpr auto padded(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return *padded_table[static_cast<std::size_t>(sq.index())];
        }

        static constexpr auto strides = []() {
                constexpr auto points = basic_compass<Grid>::points;
                std::array<int, points.size()> table;                
                for (auto i = std::size_t(0); auto p : points) {
                        table[i++] = pad(p).stride();
                }
                return table;
        }();
};

}   // namespace tabula
