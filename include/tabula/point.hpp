#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // is_chequered, lake_t, flip_t, flop_t, swap_t
#include <cassert>                      // assert

namespace tabula {

template<class Grid>
class basic_point
{
        int m_file;
        int m_rank;
public:
        constexpr basic_point(int f, int r) // Throws: Nothing.
        :
                m_file(f),
                m_rank(r)
        {
                assert(is_bounded());
        }

        bool operator==(basic_point const&) const = default;

        constexpr auto file() const noexcept
        {
                return m_file;
        }

        constexpr auto rank() const noexcept
        {
                return m_rank;
        }

        constexpr auto is_bounded() const noexcept
        {
                return
                        0 <= file() && file() < Grid::width &&
                        0 <= rank() && rank() < Grid::height
                ;
        }

        constexpr auto is_colored() const noexcept
        {
                if constexpr (is_chequered<Grid>) {
                        return (file() ^ rank() ^ Grid::coloring) % 2;
                } else {
                        return true;
                }
        }

        constexpr auto is_lake() const noexcept
        {
                return lake_t<Grid>{}(*this);
        }

        constexpr auto is_valid() const noexcept
        {
                return is_bounded() && is_colored() && !is_lake();
        }

        constexpr auto index() const noexcept
        {
                constexpr auto d = is_chequered<Grid> ? 2 : 1;
                return (file() + rank() * Grid::width) / d;
        }

        using flip_type = basic_point<flip_t<Grid>>;
        using flop_type = basic_point<flop_t<Grid>>;
        using swap_type = basic_point<swap_t<Grid>>;

        constexpr auto flip() const noexcept
                -> flip_type
        {
                return { file(), Grid::height - 1 - rank() };
        }

        constexpr auto flop() const noexcept
                -> flop_type
        {
                return { Grid::width - 1 - file(), rank() };
        }

        constexpr auto swap() const noexcept
                -> swap_type
        {
                return { rank(), file() };
        }
};

}       // namespace tabula
