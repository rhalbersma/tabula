#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // is_chequered, flip_t, flop_t, swap_t

namespace tabula {

template<class Grid>
struct basic_vector
{
        int d_file;
        int d_rank;

        bool operator==(basic_vector const&) const = default;

        constexpr auto is_cardinal() const noexcept
        {
                return !d_file ^ !d_rank;
        }

        constexpr auto is_ordinal() const noexcept
        {
                return !(d_file - d_rank) ^ !(d_file + d_rank);
        }

        constexpr auto is_left() const noexcept
        {
                return d_file < 0;
        }

        constexpr auto is_right() const noexcept
        {
                return 0 < d_file;
        }

        constexpr auto is_up() const noexcept
        {
                return 0 < d_rank;
        }

        constexpr auto is_down() const noexcept
        {
                return d_rank < 0;
        }

        constexpr auto stride() const noexcept
        {
                constexpr auto d = is_chequered<Grid> ? 2 : 1;
                return (d_file + d_rank * Grid::width) / d;
        }

        using flipped_type = basic_vector<flipped_t<Grid>>;
        using flopped_type = basic_vector<flopped_t<Grid>>;
        using swapped_type = basic_vector<swapped_t<Grid>>;

        constexpr auto flip() const noexcept
                -> flipped_type
        {
                return { d_file, -d_rank };
        }

        constexpr auto flop() const noexcept
                -> flopped_type
        {
                return { -d_file, d_rank };
        }

        constexpr auto swap() const noexcept
                -> swapped_type
        {
                return { d_rank, d_file };
        }

        constexpr auto reverse() const noexcept
                -> basic_vector
        {
                return { -d_file, -d_rank };
        }
};

}       // namespace tabula
