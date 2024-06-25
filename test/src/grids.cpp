//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/dihedral.hpp>          // dihedral, is_realized
#include <tabula/grids.hpp>             // basic_chequered, basic_rectangle
#include <tabula/functional.hpp>        // operator*, flip, flop, swap
#include <tabula/square.hpp>            // basic_square
#include <boost/mp11/algorithm.hpp>     // mp_iota_c
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE_TEMPLATE, BOOST_CHECK, BOOST_CHECK_EQUAL
#include <concepts>                     // same_as
#include <ranges>                       // iota
#include <tuple>                        // get, tuple, tuple_size_v

using namespace tabula;

BOOST_AUTO_TEST_SUITE(Compass)

constexpr auto grids = std::tuple
(       basic_rectangle(1, 1)
,       basic_rectangle(1, 2)
,       basic_rectangle(2, 1)
,       basic_rectangle(2, 2)
,       basic_rectangle(2, 3)
,       basic_rectangle(3, 2)
,       basic_rectangle(2, 4)
,       basic_rectangle(4, 2)
,       basic_rectangle(3, 3)
,       basic_rectangle(3, 5)
,       basic_rectangle(5, 3)
,       basic_chequered(1, 1, 0)
,       basic_chequered(1, 2, 0)
,       basic_chequered(2, 1, 0)
,       basic_chequered(2, 2, 0)
,       basic_chequered(2, 3, 0)
,       basic_chequered(3, 2, 0)
,       basic_chequered(2, 4, 0)
,       basic_chequered(4, 2, 0)
,       basic_chequered(3, 3, 0)
,       basic_chequered(3, 5, 0)
,       basic_chequered(5, 3, 0)
,       basic_chequered(1, 1, 1)
,       basic_chequered(1, 2, 1)
,       basic_chequered(2, 1, 1)
,       basic_chequered(2, 2, 1)
,       basic_chequered(2, 3, 1)
,       basic_chequered(3, 2, 1)
,       basic_chequered(2, 4, 1)
,       basic_chequered(4, 2, 1)
,       basic_chequered(3, 3, 1)
,       basic_chequered(3, 5, 1)
,       basic_chequered(5, 3, 1)
);

using Indices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(grids)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(IndexIsInvertible, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        for (auto index : std::views::iota(0, grid.size())) {
                BOOST_CHECK_EQUAL(grid.index(grid.coordinates(index)), index);
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(CoordinatesAreInvertible, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        for (auto coordinates : std::views::cartesian_product(std::views::iota(0, grid.width), std::views::iota(0, grid.height))) {
                BOOST_CHECK(grid.coordinates(grid.index(coordinates)) == coordinates);
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GridTransformationsAreIdempotent, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        static_assert(is_realized(dihedral, grid));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SquareTransformationsAreIdempotent, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        for (auto rank : std::views::iota(0, grid.height)) {
                for (auto file : std::views::iota(0, grid.width)) {
                        auto const square = basic_square<grid>(file, rank);
                        BOOST_CHECK(is_realized(dihedral, square));
                }
        }
}

BOOST_AUTO_TEST_SUITE_END()
