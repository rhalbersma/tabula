#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // is_chequered, lake_t, flip_t, flop_t, swap_t

namespace tabula {

template<class Grid>
struct basic_point
{
        int file;
        int rank;

        bool operator==(basic_point const&) const = default;

        constexpr auto is_within() const noexcept
        {
                return
                        0 <= file && file < Grid::width &&
                        0 <= rank && rank < Grid::height
                ;
        }

        constexpr auto is_colored() const noexcept
        {
                if constexpr (is_chequered<Grid>) {
                        return (file ^ rank ^ Grid::coloring) % 2;
                } else {
                        return true;
                }
        }

        constexpr auto is_lake() const noexcept
        {
                return lake_t<Grid>()(*this);
        }

        constexpr auto is_valid() const noexcept
        {
                return is_within() && is_colored() && !is_lake();
        }

        constexpr auto index() const noexcept
        {
                constexpr auto d = is_chequered<Grid> ? 2 : 1;
                return (file + rank * Grid::width) / d;
        }

        using flipped_type = basic_point<flipped_t<Grid>>;
        using flopped_type = basic_point<flopped_t<Grid>>;
        using swapped_type = basic_point<swapped_t<Grid>>;

        constexpr auto flip() const noexcept
                -> flipped_type
        {
                return { file, Grid::height - 1 - rank };
        }

        constexpr auto flop() const noexcept
                -> flopped_type
        {
                return { Grid::width - 1 - file, rank };
        }

        constexpr auto swap() const noexcept
                -> swapped_type
        {
                return { rank, file };
        }
};

}       // namespace tabula
