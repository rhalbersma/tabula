#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // is_chequered, lake_t, flip_t, flop_t, swap_t
#include <cassert>                      // assert
#include <utility>                      // pair

namespace tabula {

template<class Shape>
class basic_square
{
        int m_file;
        int m_rank;
public:
        constexpr basic_square(int f, int r) // Throws: Nothing.
        :
                m_file{f},
                m_rank{r}
        {
                assert(is_bounded());
        }

        bool operator==(basic_square const&) const = default;

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
                        0 <= file() && file() < Shape::width &&
                        0 <= rank() && rank() < Shape::height
                ;
        }

        constexpr auto is_colored() const noexcept
        {
                if constexpr (is_chequered<Shape>) {
                        return (file() ^ rank() ^ Shape::coloring) % 2;
                } else {
                        return true;
                }
        }

        constexpr auto is_lake() const noexcept
        {
                return lake_t<Shape>{}(*this);
        }

        constexpr auto is_valid() const noexcept
        {
                return is_bounded() && is_colored() && !is_lake();
        }

        constexpr auto index() const noexcept
        {
                constexpr auto d = is_chequered<Shape> ? 2 : 1;
                return (file() + rank() * Shape::width) / d;
        }

        using flip_type = basic_square<flip_t<Shape>>;
        using flop_type = basic_square<flop_t<Shape>>;
        using swap_type = basic_square<swap_t<Shape>>;

        constexpr auto flip() const noexcept
                -> flip_type
        {
                return { file(), Shape::height - 1 - rank() };
        }

        constexpr auto flop() const noexcept
                -> flop_type
        {
                return { Shape::width - 1 - file(), rank() };
        }

        constexpr auto swap() const noexcept
                -> swap_type
        {
                return { rank(), file() };
        }
};

}       // namespace tabula
