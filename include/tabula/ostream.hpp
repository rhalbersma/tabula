#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>             // basic_board
#include <tabula/type_traits.hpp>       // square_t
#include <cassert>                      // assert
#include <functional>                   // function
#include <iomanip>                      // setw
#include <iosfwd>                       // basic_ostream, ios_base
#include <sstream>                      // stringstream
#include <string>                       // string, to_string

namespace tabula {

class format_axis
{
        enum : long { algebraic_, numeric_ };

        inline const static auto type = std::ios_base::xalloc();
        inline const static auto base = std::ios_base::xalloc();
public:
        static auto& algebraic(std::ios_base& str)
        {
                str.iword(type) = algebraic_;
                str.iword(base) = 'a';
                return str;
        }

        static auto& numeric(std::ios_base& str)
        {
                str.iword(type) = numeric_;
                str.iword(base) = 1;
                return str;
        }

        static auto label(std::ios_base& str)
                -> std::function<std::string(int)>
        {
                return [&str] (int offset) {
                        auto const n = str.iword(base) + offset;
                        switch (str.iword(type)) {
                        case algebraic_: return std::string(1, static_cast<char>(n));
                        case numeric_  : return std::to_string(n);
                        default: throw;         // calls std::terminate
                        }
                };
        }
};

class format_square
{
        enum : long { algebraic_, sequential0_, sequential1_, padded_ };

        inline const static auto index = std::ios_base::xalloc();
public:
        static auto& algebraic(std::ios_base& str)
        {
                str.iword(index) = algebraic_;
                return str;
        }

        static auto& sequential0(std::ios_base& str)
        {
                str.iword(index) = sequential0_;
                return str;
        }

        static auto& sequential1(std::ios_base& str)
        {
                str.iword(index) = sequential1_;
                return str;
        }

        static auto& padded(std::ios_base& str)
        {
                str.iword(index) = padded_;
                return str;
        }

        template<class Shape, class Padding>
        static auto board(std::ios_base& str, basic_board<Shape, Padding> const& b)
                -> std::function<std::string(square_t<basic_board<Shape, Padding>> const&)>
        {
                switch (str.iword(index)) {
                case algebraic_: return [] (auto const& sq) {
                        std::stringstream sstr;
                        auto const format = format_axis::label(sstr);
                        sstr << format_axis::algebraic << format(sq.file());
                        sstr << format_axis::numeric   << format(sq.rank());
                        return sstr.str();
                };
                case sequential0_ : return [&b](auto const& sq) { return std::to_string(b.sequential0(sq));  };
                case sequential1_ : return [&b](auto const& sq) { return std::to_string(b.sequential1(sq));  };
                case padded_      : return [&b](auto const& sq) { return std::to_string(b.padded(sq)); };
                default: throw;         // calls std::terminate
                }
        }
};

template<class CharT, class Traits, class Shape, class Padding>
auto& operator<<(std::basic_ostream<CharT, Traits>& ostr, basic_board<Shape, Padding> const& b)
{
        auto const format = format_square::board(ostr, b);
        for (auto r = b.height - 1; r >= 0; --r) {
                for (auto f = 0; f < b.width; ++f) {
                        if (auto const sq = b.square(f, r); sq.is_valid()) {
                                ostr << std::setw(4) << format(sq);
                        } else {
                                ostr << std::setw(4) << ' ';
                        }
                        if (f == b.width - 1) {
                                ostr << '\n';
                        }
                }
        }
        return ostr;
}

}       // tabula
