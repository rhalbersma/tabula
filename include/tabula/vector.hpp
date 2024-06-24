#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/padding.hpp>   // padding

namespace tabula {

template<auto Grid>
struct basic_vector
{
        int file;
        int rank;

        static constexpr auto grid = Grid;

        friend bool operator==(basic_vector, basic_vector) = default;

        [[nodiscard]] constexpr auto& operator+=(basic_vector other) noexcept
        {
                this->file += other.file;
                this->rank += other.rank;
                return *this;
        }

        [[nodiscard]] constexpr auto& operator-=(basic_vector other) noexcept
        {
                this->file -= other.file;
                this->rank -= other.rank;
                return *this;
        }

        [[nodiscard]] constexpr auto& operator*=(int n) noexcept
        {
                file *= n;
                rank *= n;
                return *this;
        }

        [[nodiscard]] constexpr auto reverse() const noexcept
                -> basic_vector
        {
                return { -file, -rank };
        }

        [[nodiscard]] constexpr auto flip() const noexcept
                -> basic_vector<Grid.flip()>
        {
                return { file, -rank };
        }

        [[nodiscard]] constexpr auto flop() const noexcept
                -> basic_vector<Grid.flop()>
        {
                return { -file, rank };
        }

        [[nodiscard]] constexpr auto swap() const noexcept
                -> basic_vector<Grid.swap()>
        {
                return { rank, file };
        }

        template<padding Padding>
        [[nodiscard]] constexpr auto pad() const noexcept
                -> basic_vector<Grid.template pad<Padding>()>
        {
                return { file, rank };
        }

        [[nodiscard]] constexpr auto is_cardinal() const noexcept
        {
                return !file ^ !rank;
        }

        [[nodiscard]] constexpr auto is_ordinal() const noexcept
        {
                return !(file - rank) ^ !(file + rank);
        }

        [[nodiscard]] constexpr auto is_left() const noexcept
        {
                return file < 0;
        }

        [[nodiscard]] constexpr auto is_right() const noexcept
        {
                return 0 < file;
        }

        [[nodiscard]] constexpr auto is_up() const noexcept
        {
                return 0 < rank;
        }

        [[nodiscard]] constexpr auto is_down() const noexcept
        {
                return rank < 0;
        }

        [[nodiscard]] constexpr auto stride() const noexcept
        {
                return Grid.index(*this);
        }
};

template<auto Grid>
[[nodiscard]] constexpr auto operator+(basic_vector<Grid> lhs, basic_vector<Grid> rhs) noexcept
{
        auto nrv = lhs; nrv += rhs; return nrv;
}

template<auto Grid>
[[nodiscard]] constexpr auto operator-(basic_vector<Grid> lhs, basic_vector<Grid> rhs) noexcept
{
        auto nrv = lhs; nrv -= rhs; return nrv;
}

template<auto Grid>
[[nodiscard]] constexpr auto operator*(basic_vector<Grid> v, int n) noexcept
{
        auto nrv = v; nrv *= n; return nrv;
}

template<auto Grid>
[[nodiscard]] constexpr auto operator*(int n, basic_vector<Grid> v) noexcept
{
        auto nrv = v; nrv *= n; return nrv;
}

}       // namespace tabula
