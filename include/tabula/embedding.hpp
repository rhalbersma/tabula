#pragma once

//          Copyright Rein Halbersma 2019-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, swapped_t
#include <utility>                      // pair

namespace tabula {

template<class Grid>
inline constexpr auto valid_range = []() {
        using square = basic_square<Grid>;

        constexpr auto first = []() {
                for (auto r = 0; r < Grid::height; ++r) {
                        for (auto f = 0; f < Grid::width; ++f) {
                                if (auto const sq = square(f, r); sq.is_valid()) {
                                        return sq;
                                }
                        }
                }
        }();

        constexpr auto last = []() {
                for (auto r = Grid::height - 1; r >= 0; --r) {
                        for (auto f = Grid::width - 1; f >= 0; --f) {
                                if (auto const sq = square(f, r); sq.is_valid()) {
                                        return sq;
                                }
                        }
                }
        }();

        return std::pair(first, last);
}();

template<class Grid, class Padding>
struct basic_embedding
{
        using    grid_type = Grid;
        using padding_type = Padding;

        using padded_grid = typename Grid::template padded_type<Padding>;
        using square_type = basic_square<Grid>;

        static constexpr auto pad(square_type const& sq) noexcept
        {
                return sq.template pad<Padding>();
        }

        static constexpr auto valid_range = []() {
                auto const [first, last] = valid_range<Grid>;
                return std::pair(pad(first), pad(last));
        }();

        static constexpr auto valid_size = []() {
                auto const [first, last] = valid_range;
                return last.index() - first.index() + 1;
        }();

        using flipped_type = basic_embedding<flipped_t<Grid>, Padding>;
        using flopped_type = basic_embedding<flopped_t<Grid>, Padding>;
        using swapped_type = basic_embedding<swapped_t<Grid>, Padding>;

        static constexpr auto flip() noexcept -> flipped_type { return {}; }
        static constexpr auto flop() noexcept -> flopped_type { return {}; }
        static constexpr auto swap() noexcept -> swapped_type { return {}; }
};

}   // namespace tabula
