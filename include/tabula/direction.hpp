#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // is_chequered, lake_t, flip_t, flop_t, swap_t
#include <utility>                      // pair

namespace tabula {

template<class Shape>
class basic_direction
{
        int m_delta_file;
        int m_delta_rank;
public:
        constexpr basic_direction(int df, int dr) // Throws: Nothing.
        :
                m_delta_file{df},
                m_delta_rank{dr}
        {}

        constexpr bool operator==(basic_direction const& other) const noexcept
        {
                constexpr auto as_pair = [](auto const& d) {
                        return std::pair{d.m_delta_file, d.m_delta_rank};
                };
                return as_pair(*this) == as_pair(other);
        }

        constexpr auto delta_file() const noexcept
        {
                return m_delta_file;
        }

        constexpr auto delta_rank() const noexcept
        {
                return m_delta_rank;
        }

        constexpr auto is_bounded() const noexcept
        {
                return
                        -Shape::width  < delta_file() && delta_file() < Shape::width &&
                        -Shape::height < delta_rank() && delta_rank() < Shape::height
                ;
        }

        constexpr auto is_cardinal() const noexcept
        {
                return !delta_file() ^ !delta_rank();
        }

        constexpr auto is_ordinal() const noexcept
        {
                return !(delta_file() - delta_rank()) ^ !(delta_file() + delta_rank());
        }

        constexpr auto is_left() const noexcept
        {
                return delta_file() < 0;
        }

        constexpr auto is_right() const noexcept
        {
                return 0 < delta_file();
        }

        constexpr auto is_up() const noexcept
        {
                return 0 < delta_rank();
        }

        constexpr auto is_down() const noexcept
        {
                return delta_rank() < 0;
        }

        constexpr auto stride() const noexcept
        {
                constexpr auto d = is_chequered<Shape> ? 2 : 1;
                return (delta_file() + delta_rank() * Shape::width) / d;
        }

        using flip_type = basic_direction<flip_t<Shape>>;
        using flop_type = basic_direction<flop_t<Shape>>;
        using swap_type = basic_direction<swap_t<Shape>>;

        constexpr auto flip() const noexcept
                -> flip_type
        {
                return { delta_file(), -delta_rank() };
        }

        constexpr auto flop() const noexcept
                -> flop_type
        {
                return { -delta_file(), delta_rank() };
        }

        constexpr auto swap() const noexcept
                -> swap_type
        {
                return { delta_rank(), delta_file() };
        }

        constexpr auto reverse() const noexcept
                -> basic_direction
        {
                return { -delta_file(), -delta_rank() };
        }
};

}       // namespace tabula
