#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/compass.hpp>           // basic_compass
#include <tabula/embedding.hpp>         // basic_embedding
#include <tabula/lakes.hpp>             // basic_lakes
#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // square_t, vector_t
#include <tabula/tuple.hpp>             // min_index, transform
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
                        return fun(basic_embedding_v).valid_squares;
                })
        );
        static constexpr auto transform_v = std::get<idx>(orientations);
        static constexpr auto embedding_v = transform_v(basic_embedding_v);

        using     embedding_type = decltype(embedding_v);
        using        square_type = basic_square<Grid>;
        using        vector_type = basic_vector<Grid>;
        using padded_square_type = square_t<embedding_type>;
        using padded_vector_type = vector_t<embedding_type>;

        static constexpr auto sequential(square_type const& sq) noexcept
        {
                return sq.flip();
        }

        static constexpr auto embed(square_type const& s) noexcept
        {
                return embedding_v.embed(transform_v(s));
        }

        static constexpr auto embed(vector_type const& v) noexcept
                -> padded_vector_type
        {
                auto const w = transform_v(v);
                return { w.file, w.rank };
        }

        static constexpr auto padded2sequential_table = []() {
                std::array<std::optional<int>, embedding_v.area> table{};       // zero-initalization
                for (auto r = 0; r < Grid::height; ++r) {
                        for (auto f = 0; f < Grid::width; ++f) {
                                if (auto const sq = square_type(f, r); sq.is_valid()) {
                                        table[static_cast<std::size_t>(embed(sq).index())] = sequential(sq).index();
                                }
                        }
                }
                return table;
        }();

        static constexpr auto sequential2padded_table = []() {
                std::array<std::optional<int>, Grid::area> table{};             // zero-initalization
                for (auto r = 0; r < Grid::height; ++r) {
                        for (auto f = 0; f < Grid::width; ++f) {
                                if (auto const sq = square_type(f, r); sq.is_valid()) {
                                        table[static_cast<std::size_t>(sequential(sq).index())] = embed(sq).index();
                                }
                        }
                }
                return table;
        }();

        static constexpr auto sequential0(int i) // Throws: Nothing.
        {
                assert(0 <= i && i < area);
                auto const seq = padded2sequential_table[static_cast<std::size_t>(i)];
                assert(seq);
                return *seq;
        }

        static constexpr auto sequential1(int i) // Throws: Nothing.
        {
                assert(0 <= i && i < area);
                return sequential0(i) + 1;
        }

        static constexpr auto padded0(int n0) // Throws: Nothing.
        {
                assert(0 <= n0 && n0 < Grid::area);
                auto const pad = sequential2padded_table[static_cast<std::size_t>(n0)];
                assert(pad);
                return *pad;
        }

        static constexpr auto padded1(int n1) // Throws: Nothing.
        {
                assert(1 <= n1 && n1 <= Grid::area);
                return padded0(n1 - 1);
        }

public:
        using    grid_type = Grid;
        using padding_type = Padding;

        static constexpr auto width  = Grid::width;
        static constexpr auto height = Grid::height;
        static constexpr auto area   = Grid::area;

        static constexpr auto padded_width  = embedding_type::width;
        static constexpr auto padded_height = embedding_type::height;
        static constexpr auto padded_area   = embedding_type::area;

        static constexpr auto valid_squares = embedding_type::valid_squares;

        static constexpr auto square(int f, int r) // Throws: Nothing.
                -> square_type
        {
                return { f, r };
        }

        static constexpr auto sequential0(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return sequential0(embed(sq).index());
        }

        static constexpr auto sequential1(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return sequential1(embed(sq).index());
        }

        static constexpr auto padded(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return padded0(sequential(sq).index());
        }

        static constexpr auto strides = []() {
                constexpr auto points = basic_compass<Grid>::points;
                std::array<int, points.size()> table{};
                auto i = std::size_t(0);
                for (auto p : points) {
                        table[i++] = embed(p).stride();
                }
                return table;
        }();
};

}   // namespace tabula
