#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, swapped_t, padded_t
#include <tabula/vector.hpp>            // basic_vector
#include <optional>                     // optional

namespace tabula {

template<class Grid, class Padding>
struct basic_embedding
{
        using grid_type    = Grid;
        using padding_type = Padding;
        using padded_type  = padded_t<Grid, Padding>;

        using        square = basic_square<Grid>;
        using padded_square = basic_square<padded_type>;
        using padded_vector = basic_vector<padded_type>;

        static constexpr auto first_valid = []() -> std::optional<square> {
                for (auto r = 0; r < Grid::height; ++r) {
                        for (auto f = 0; f < Grid::width; ++f) {
                                if (auto const sq = square(f, r); sq.is_valid()) {
                                        return sq;
                                }
                        }
                }
                return {};
        }();
        static_assert(first_valid && first_valid->is_valid());

        static constexpr auto last_valid = []() -> std::optional<square> {
                for (auto r = Grid::height - 1; r >= 0; --r) {
                        for (auto f = Grid::width - 1; f >= 0; --f) {
                                if (auto const sq = square(f, r); sq.is_valid()) {
                                        return sq;
                                }
                        }
                }
                return {};
        }();
        static_assert(last_valid && last_valid->is_valid());

        static constexpr auto size = Grid::area;
        static constexpr auto padded_size = padded_type::area;

        static constexpr auto to_padded(square const& sq)
                -> padded_square
        {
                return { sq.file + Padding::left, sq.rank + Padding::bottom };
        }
        static constexpr auto valid_padded_size = to_padded(*last_valid).index() - to_padded(*first_valid).index() + 1;

        using flipped_type = basic_embedding<flipped_t<Grid>, Padding>;
        using flopped_type = basic_embedding<flopped_t<Grid>, Padding>;
        using swapped_type = basic_embedding<swapped_t<Grid>, Padding>;

        static constexpr auto flip() noexcept -> flipped_type { return {}; }
        static constexpr auto flop() noexcept -> flopped_type { return {}; }
        static constexpr auto swap() noexcept -> swapped_type { return {}; }
};

}   // namespace tabula
