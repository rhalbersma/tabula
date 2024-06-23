#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/padding.hpp>           // padding
#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, swapped_t, add_padding_t
#include <tabula/vector.hpp>            // basic_vector

namespace tabula {

template<class Grid>
struct basic_square
{
        int file;
        int rank;

        using grid_type = Grid;

        friend bool operator==(basic_square, basic_square) = default;

        [[nodiscard]] constexpr auto& operator+=(basic_vector<Grid> v) noexcept
        {
                this->file += v.file;
                this->rank += v.rank;
                return *this;
        }

        [[nodiscard]] constexpr auto& operator-=(basic_vector<Grid> v) noexcept
        {
                this->file -= v.file;
                this->rank -= v.rank;
                return *this;
        }

        [[nodiscard]] constexpr auto flip() const noexcept
                -> basic_square<flipped_t<Grid>>
        {
                return { file, Grid::height - 1 - rank };
        }

        [[nodiscard]] constexpr auto flop() const noexcept
                -> basic_square<flopped_t<Grid>>
        {
                return { Grid::width - 1 - file, rank };
        }

        [[nodiscard]] constexpr auto swap() const noexcept
                -> basic_square<swapped_t<Grid>>
        {
                return { rank, file };
        }

        template<padding Padding>
        [[nodiscard]] constexpr auto pad() const noexcept
                -> basic_square<padded_t<Grid, Padding>>
        {
                return { file + Padding.left, rank + Padding.bottom };
        }

        [[nodiscard]] constexpr auto is_valid() const noexcept
        {
                return Grid::is_valid(*this);
        }

        [[nodiscard]] constexpr auto index() const noexcept
        {
                return Grid::index(*this);
        }
};

template<class Grid>
[[nodiscard]] constexpr auto operator+(basic_square<Grid> s, basic_vector<Grid> v) noexcept
{
        auto nrv = s; nrv += v; return nrv;
}

template<class Grid>
[[nodiscard]] constexpr auto operator+(basic_vector<Grid> v, basic_square<Grid> s) noexcept
{
        auto nrv = s; nrv += v; return nrv;
}

template<class Grid>
[[nodiscard]] constexpr auto operator-(basic_square<Grid> s, basic_vector<Grid> v) noexcept
{
        auto nrv = s; nrv -= v; return nrv;
}

template<class Grid>
[[nodiscard]] constexpr auto operator-(basic_square<Grid> lhs, basic_square<Grid> rhs) noexcept
        -> basic_vector<Grid>
{
        return { lhs.file - rhs.file, lhs.rank - rhs.rank };
}

}       // namespace tabula
