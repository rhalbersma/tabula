#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, square_t, swapped_t
#include <tabula/valid.hpp>             //
#include <optional>                     // optional, nullopt
#include <utility>                      // pair

namespace tabula {

template<class Grid, class Padding>
struct basic_embedding
{
        using    grid_type = Grid;
        using padding_type = Padding;

        using padded_grid = padded_t<Grid, Padding>;
        using square_type = square_t<Grid>;

        static constexpr auto pad(square_type const& sq) noexcept
        {
                return sq.template pad<Padding>();
        }

        static constexpr auto valid_range = []() {
                auto const first = first_valid_square<Grid>();
                auto const last = last_valid_square<Grid>();
                return std::pair(pad(*first), pad(*last));
        }();

        static constexpr auto valid_size = []() {
                auto const [ first, last ] = valid_range;
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
