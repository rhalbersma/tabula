#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // compose, identity, flip, flop, swap
#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, swapped_t
#include <tabula/vector.hpp>            // basic_vector
#include <optional>                     // optional
#include <tuple>                        // tuple

namespace tabula {

template<class Grid, class Padding>
class basic_embedding
{
        using padded_grid = typename Grid::template padded_type<Padding>;
        using grid_square = basic_square<Grid>;

        static constexpr auto first_valid = []() -> std::optional<grid_square> {
                for (auto r = 0; r < Grid::height; ++r) {
                        for (auto f = 0; f < Grid::width; ++f) {
                                if (auto const sq = grid_square(f, r); sq.is_valid()) {
                                        return sq;
                                }
                        }
                }
                return {};
        }();
        static_assert(first_valid && first_valid->is_valid());

        static constexpr auto last_valid = []() -> std::optional<grid_square> {
                for (auto r = Grid::height - 1; r >= 0; --r) {
                        for (auto f = Grid::width - 1; f >= 0; --f) {
                                if (auto const sq = grid_square(f, r); sq.is_valid()) {
                                        return sq;
                                }
                        }
                }
                return {};
        }();
        static_assert(last_valid && last_valid->is_valid());

public:
        using    grid_type = Grid;
        using padding_type = Padding;

        using  square_type = basic_square<padded_grid>;
        using  vector_type = basic_vector<padded_grid>;

        static constexpr auto width  = padded_grid::width;
        static constexpr auto height = padded_grid::height;
        static constexpr auto area   = padded_grid::area;

        static constexpr auto embed(grid_square const& sq)
                -> square_type
        {
                return { sq.file + Padding::left, sq.rank + Padding::bottom };
        }

        static constexpr auto valid_squares = embed(*last_valid).index() - embed(*first_valid).index() + 1;

        using flipped_type = basic_embedding<flipped_t<Grid>, Padding>;
        using flopped_type = basic_embedding<flopped_t<Grid>, Padding>;
        using swapped_type = basic_embedding<swapped_t<Grid>, Padding>;

        static constexpr auto flip() noexcept -> flipped_type { return {}; }
        static constexpr auto flop() noexcept -> flopped_type { return {}; }
        static constexpr auto swap() noexcept -> swapped_type { return {}; }
};

}   // namespace tabula
