#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "board.hpp"            // basic_board
#include "type_traits.hpp"      // square_t
#include <cassert>              // assert
#include <functional>           // function
#include <iomanip>              // setw
#include <iosfwd>               // basic_ostream, ios_base
#include <sstream>              // stringstream
#include <string>               // string, to_string

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
        enum : long { algebraic_, numeric0_, numeric1_, embedding_ };

        inline const static auto index = std::ios_base::xalloc();
public:
        static auto& algebraic(std::ios_base& str)
        {
                str.iword(index) = algebraic_;
                return str;
        }

        static auto& numeric0(std::ios_base& str)
        {
                str.iword(index) = numeric0_;
                return str;
        }

        static auto& numeric1(std::ios_base& str)
        {
                str.iword(index) = numeric1_;
                return str;
        }

        static auto& embedding(std::ios_base& str)
        {
                str.iword(index) = embedding_;
                return str;
        }

        template<class Shape>
        static auto board(std::ios_base& str, basic_board<Shape> const& b)
                -> std::function<std::string(square_t<basic_board<Shape>> const&)>
        {
                switch (str.iword(index)) {
                case algebraic_: return [] (auto const& sq) {
                        std::stringstream sstr;
                        auto const format = format_axis::label(sstr);
                        sstr << format_axis::algebraic << format(sq.file());
                        sstr << format_axis::numeric   << format(sq.rank());
                        return sstr.str();
                };
                case numeric0_ : return [&b](auto const& sq) { return std::to_string(b.numeric0(sq));  };
                case numeric1_ : return [&b](auto const& sq) { return std::to_string(b.numeric1(sq));  };
                case embedding_: return [&b](auto const& sq) { return std::to_string(b.embedding(sq)); };
                default: throw;         // calls std::terminate
                }
        }
};

template<class CharT, class Traits, class Shape>
auto& operator<<(std::basic_ostream<CharT, Traits>& ostr, basic_board<Shape> const& b)
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
