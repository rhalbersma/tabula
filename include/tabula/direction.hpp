#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // is_chequered, is_equal_coloring, lake_t, flip_t, flop_t, swap_t
#include <type_traits>                  // enable_if_t, is_same_v
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

        template<class Embedded, std::enable_if_t<
                Embedded::width  <  Shape::width &&
                Embedded::height == Shape::height &&
                is_equal_coloring<Embedded, Shape> &&
                std::is_same_v<lake_t<Embedded>, lake_t<Shape>>
        >...>
        constexpr /* explicit(false) */ basic_direction(basic_direction<Embedded> const& dir) noexcept
        :
                m_delta_file{dir.delta_file()},
                m_delta_rank{dir.delta_rank()}
        {}

        constexpr auto delta_file() const noexcept
        {
                return m_delta_file;
        }

        constexpr auto delta_rank() const noexcept
        {
                return m_delta_rank;
        }

        constexpr auto stride() const noexcept
        {
                constexpr auto d = is_chequered<Shape> ? 2 : 1;
                return (delta_file() + delta_rank() * Shape::width) / d;
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

template<class Shape>
constexpr auto operator==(basic_direction<Shape> const& lhs, basic_direction<Shape> const& rhs) noexcept
{
        constexpr auto as_pair = [](auto const& sq) { return std::pair{sq.delta_file(), sq.delta_rank()}; };
        return as_pair(lhs) == as_pair(rhs);
}

template<class Shape>
constexpr auto operator!=(basic_direction<Shape> const& lhs, basic_direction<Shape> const& rhs) noexcept
{
        return !(lhs == rhs);
}

}       // namespace tabula
