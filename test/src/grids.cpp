//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/dihedral.hpp>          // dihedral, is_realized
#include <tabula/grids.hpp>             // chequer, rectangle
#include <tabula/functional.hpp>        // operator*, flip, flop, swap
#include <tabula/square.hpp>            // basic_square
#include <boost/mp11/algorithm.hpp>     // mp_iota_c
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE_TEMPLATE, BOOST_CHECK, BOOST_CHECK_EQUAL
#include <concepts>                     // same_as
#include <ranges>                       // cartesian_product iota
#include <tuple>                        // get, tuple, tuple_size_v

using namespace tabula;

BOOST_AUTO_TEST_SUITE(Compass)

constexpr auto grids = std::tuple
{       rectangle{1, 1}
,       rectangle{1, 2}
,       rectangle{2, 1}
,       rectangle{2, 2}
,       rectangle{2, 3}
,       rectangle{3, 2}
,       rectangle{2, 4}
,       rectangle{4, 2}
,       rectangle{3, 3}
,       rectangle{3, 5}
,       rectangle{5, 3}
,       chequer{1, 1, 0}
,       chequer{1, 2, 0}
,       chequer{2, 1, 0}
,       chequer{2, 2, 0}
,       chequer{2, 3, 0}
,       chequer{3, 2, 0}
,       chequer{2, 4, 0}
,       chequer{4, 2, 0}
,       chequer{3, 3, 0}
,       chequer{3, 5, 0}
,       chequer{5, 3, 0}
,       chequer{1, 1, 1}
,       chequer{1, 2, 1}
,       chequer{2, 1, 1}
,       chequer{2, 2, 1}
,       chequer{2, 3, 1}
,       chequer{3, 2, 1}
,       chequer{2, 4, 1}
,       chequer{4, 2, 1}
,       chequer{3, 3, 1}
,       chequer{3, 5, 1}
,       chequer{5, 3, 1}
};

using Indices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(grids)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(IndicesAreInvertible, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        for (auto index : std::views::iota(0, grid.size())) {
                BOOST_CHECK_EQUAL(grid.index(grid.coordinates(index)), index);
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(CoordinatesOfValidSquaresAreInvertible, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        for (auto coordinates : std::views::cartesian_product(
                std::views::iota(0, grid.width), 
                std::views::iota(0, grid.height)
        )) {
                if (auto const [ file, rank ] = coordinates; basic_square<grid>{file, rank}.is_valid()) {
                        BOOST_CHECK(grid.coordinates(grid.index(coordinates)) == coordinates);
                }
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(DihedralGroupActionIsRealizedOnGrids, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        static_assert(is_realized(dihedral, grid));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(DihedralGroupActionIsRealizedOnGridSquares, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        for (auto const [ file, rank ] : std::views::cartesian_product(
                std::views::iota(0, grid.width), 
                std::views::iota(0, grid.height)
        )) {
                auto const square = basic_square<grid>{file, rank};
                BOOST_CHECK(is_realized(dihedral, square));
        }
}

BOOST_AUTO_TEST_SUITE_END()
