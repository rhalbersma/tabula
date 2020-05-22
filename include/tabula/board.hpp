#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/compass.hpp>           // basic_compass
#include <tabula/embedding.hpp>         // basic_embedding
#include <tabula/functional.hpp>        // flip_fn, flop_fn, swap_fn
#include <tabula/lakes.hpp>             // basic_lakes
#include <tabula/point.hpp>             // basic_point
#include <tabula/tuple.hpp>             // min_index, transform
#include <tabula/type_traits.hpp>       // is_chequered, flip_t
#include <tabula/vector.hpp>            // basic_vector
#include <array>                        // array
#include <cassert>                      // assert
#include <cstddef>                      // size_t
#include <optional>                     // optional
#include <tuple>                        // get, tuple

namespace tabula {

inline constexpr auto transforms = std::tuple(
        identity,                       // origin at lower-left, left-to-right, bottom-to-top
        swap,                           // origin at lower-left, bottom-to-top, left-to-right
        flip,                           // origin at upper-left, left-to-right, top-to-bottom
        compose(swap, flip),            // origin at upper-left, top-to-bottom, left-to-right
        flop,                           // origin at lower-right, right-to-left, bottom-to-top
        compose(swap, flop),            // origin at lower-right, bottom-to-top, right-to-left
        compose(flop, flip),            // origin at upper-right, right-to-left, top-to-bottom
        compose(swap, flop, flip)       // origin at upper-right, top-to-bottom, right-to-left
);

template<class Grid, class Padding>
struct basic_board
{
        static constexpr auto embedding_v = basic_embedding<Grid, Padding>{};
        static constexpr auto idx = min_index(transform(transforms, [](auto fun) {
                return fun(embedding_v).valid_padded_size;
        }));
        static constexpr auto transform_v = std::get<idx>(transforms);
        static constexpr auto image_v = transform_v(embedding_v);

        using point_type = basic_point<Grid>;
        using vector_type = basic_vector<Grid>;
        using padded_point_type = typename decltype(image_v)::padded_point;
        using padded_vector_type = typename decltype(image_v)::padded_vector;

        static constexpr auto to_sequential(point_type const& sq) noexcept
        {
                return sq.flip();
        }

        static constexpr auto to_padded(point_type const& sq) noexcept
        {
                return image_v.to_padded(transform_v(sq));
        }

        static constexpr auto to_padded(vector_type const& dir) noexcept
                -> padded_vector_type
        {
                auto const t = transform_v(dir);
                return { t.d_file, t.d_rank };
        }

        static constexpr auto padded2sequential_table = []() {
                std::array<std::optional<int>, image_v.padded_size> table{};
                for (auto r = 0; r < Grid::height; ++r) {
                        for (auto f = 0; f < Grid::width; ++f) {
                                if (auto const sq = point_type(f, r); sq.is_valid()) {
                                        table[static_cast<std::size_t>(to_padded(sq).index())] = to_sequential(sq).index();
                                }
                        }
                }
                return table;
        }();

        static constexpr auto sequential2padded_table = []() {
                std::array<std::optional<int>, image_v.size> table{};
                for (auto r = 0; r < Grid::height; ++r) {
                        for (auto f = 0; f < Grid::width; ++f) {
                                if (auto const sq = point_type(f, r); sq.is_valid()) {
                                        table[static_cast<std::size_t>(to_sequential(sq).index())] = to_padded(sq).index();
                                }
                        }
                }
                return table;
        }();
public:
        static constexpr auto width  = Grid::width;
        static constexpr auto height = Grid::height;

        using grid_type    = Grid;
        using padding_type = Padding;

        static constexpr auto size              = image_v.size;
        static constexpr auto padded_size       = image_v.padded_size;
        static constexpr auto valid_padded_size = image_v.valid_padded_size;

        static constexpr auto square(int f, int r) // Throws: Nothing.
                -> point_type
        {
                return { f, r };
        }

        static constexpr auto sequential0(int i) // Throws: Nothing.
        {
                assert(0 <= i && i < padded_size);
                auto const t = padded2sequential_table[static_cast<std::size_t>(i)];
                assert(t);
                return *t;
        }

        static constexpr auto sequential1(int i) // Throws: Nothing.
        {
                assert(0 <= i && i < padded_size);
                return sequential0(i) + 1;
        }

        static constexpr auto sequential0(point_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return sequential0(to_padded(sq).index());
        }

        static constexpr auto sequential1(point_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return sequential1(to_padded(sq).index());
        }

        static constexpr auto padded0(int n0) // Throws: Nothing.
        {
                assert(0 <= n0 && n0 < size);
                auto const t = sequential2padded_table[static_cast<std::size_t>(n0)];
                assert(t);
                return *t;
        }

        static constexpr auto padded1(int n1) // Throws: Nothing.
        {
                assert(1 <= n1 && n1 <= size);
                return padded0(n1 - 1);
        }

        static constexpr auto padded(point_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return padded0(to_sequential(sq).index());
        }

        static constexpr auto strides = []() {
                constexpr auto points = basic_compass<Grid>().points;
                std::array<int, points.size()> table{};
                auto i = std::size_t(0);
                for (auto p : points) {
                        table[i++] = to_padded(p).stride();
                }
                return table;
        }();
};

}   // namespace tabula
