#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, swapped_t

namespace tabula {

template<class Grid>
struct basic_vector
{
        int file;
        int rank;

        using grid_type = Grid;

        bool operator==(basic_vector const&) const = default;

        constexpr auto& operator+=(basic_vector const& v) noexcept
        {
                file += v.file;
                rank += v.rank;
                return *this;
        }

        constexpr auto& operator-=(basic_vector const& v) noexcept
        {
                file -= v.file;
                rank -= v.rank;
                return *this;
        }

        constexpr auto& operator*=(int n) noexcept
        {
                file *= n;
                rank *= n;
                return *this;
        }

        constexpr auto is_cardinal() const noexcept
        {
                return !file ^ !rank;
        }

        constexpr auto is_ordinal() const noexcept
        {
                return !(file - rank) ^ !(file + rank);
        }

        constexpr auto is_left() const noexcept
        {
                return file < 0;
        }

        constexpr auto is_right() const noexcept
        {
                return 0 < file;
        }

        constexpr auto is_up() const noexcept
        {
                return 0 < rank;
        }

        constexpr auto is_down() const noexcept
        {
                return rank < 0;
        }

        constexpr auto stride() const noexcept
        {
                return Grid::stride(*this);
        }

        using flipped_type = basic_vector<flipped_t<Grid>>;
        using flopped_type = basic_vector<flopped_t<Grid>>;
        using swapped_type = basic_vector<swapped_t<Grid>>;

        constexpr auto flip() const noexcept
                -> flipped_type
        {
                return { file, -rank };
        }

        constexpr auto flop() const noexcept
                -> flopped_type
        {
                return { -file, rank };
        }

        constexpr auto swap() const noexcept
                -> swapped_type
        {
                return { rank, file };
        }

        constexpr auto reverse() const noexcept
                -> basic_vector
        {
                return { -file, -rank };
        }
};

template<class Grid>
constexpr auto operator+(basic_vector<Grid> const& lhs, basic_vector<Grid> const& rhs) noexcept
{
        auto nrv = lhs; nrv += rhs; return nrv;
}

template<class Grid>
constexpr auto operator-(basic_vector<Grid> const& lhs, basic_vector<Grid> const& rhs) noexcept
{
        auto nrv = lhs; nrv -= rhs; return nrv;
}

template<class Grid>
constexpr auto operator*(basic_vector<Grid> const& v, int n) noexcept
{
        auto nrv = v; nrv *= n; return nrv;
}

template<class Grid>
constexpr auto operator*(int n, basic_vector<Grid> const& v) noexcept
{
        auto nrv = v; nrv *= n; return nrv;
}

}       // namespace tabula
