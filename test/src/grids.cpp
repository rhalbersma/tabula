//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/dihedral.hpp>          // d4, is_realized
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

constexpr auto d4_grids = std::tuple
{       rectangle{1, 1}
,       rectangle{2, 2}
,       rectangle{3, 3}
,       rectangle{4, 4}
,       rectangle{5, 5}
,       rectangle{6, 6}
,       rectangle{7, 7}
,       rectangle{8, 8}
,       chequer{1, 1, 0}
,       chequer{1, 1, 1}
,       chequer{3, 3, 0}
,       chequer{3, 3, 1}
,       chequer{5, 5, 0}
,       chequer{5, 5, 1}
,       chequer{7, 7, 0}
,       chequer{7, 7, 1}
};

using D4Indices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(d4_grids)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(D4GridsAreInvariantUnderD4, Index, D4Indices)
{
        constexpr auto grid = std::get<Index::value>(d4_grids);
        static_assert(group::is_invariant(grid, group::d4));
        static_assert(group::is_invariant(grid, group::z4));
        static_assert(group::is_invariant(grid, group::d2o));
        static_assert(group::is_invariant(grid, group::d2c));
        static_assert(group::is_invariant(grid, group::z2d));
        static_assert(group::is_invariant(grid, group::z2a));
        static_assert(group::is_invariant(grid, group::d1r));
        static_assert(group::is_invariant(grid, group::d1v));
        static_assert(group::is_invariant(grid, group::d1h));
}

constexpr auto d2o_grids = std::tuple
{       chequer{2, 2, 0}
,       chequer{2, 2, 1}
,       chequer{4, 4, 0}
,       chequer{4, 4, 1}
,       chequer{6, 6, 0}
,       chequer{6, 6, 1}
,       chequer{8, 8, 0}
,       chequer{8, 8, 1}
};

using D2OIndices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(d2o_grids)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(D2OGridsAreInvariantUnderD2O, Index, D2OIndices)
{
        constexpr auto grid = std::get<Index::value>(d2o_grids);
        static_assert(not group::is_invariant(grid, group::d4));
        static_assert(not group::is_invariant(grid, group::z4));
        static_assert(    group::is_invariant(grid, group::d2o));
        static_assert(not group::is_invariant(grid, group::d2c));
        static_assert(    group::is_invariant(grid, group::z2d));
        static_assert(    group::is_invariant(grid, group::z2a));
        static_assert(    group::is_invariant(grid, group::d1r));
        static_assert(not group::is_invariant(grid, group::d1v));
        static_assert(not group::is_invariant(grid, group::d1h));
}

constexpr auto d2c_grids = std::tuple
{       rectangle{1, 2}
,       rectangle{1, 2}
,       rectangle{1, 3}
,       rectangle{1, 3}
,       rectangle{2, 1}
,       rectangle{2, 1}
,       rectangle{2, 3}
,       rectangle{2, 3}
,       chequer{1, 3, 0}
,       chequer{1, 3, 1}
,       chequer{1, 5, 0}
,       chequer{1, 5, 1}
,       chequer{3, 1, 0}
,       chequer{3, 1, 1}
,       chequer{3, 5, 0}
,       chequer{3, 5, 1}
};

using D2CIndices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(d2c_grids)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(D2CGridsAreInvariantUnderD2C, Index, D2CIndices)
{
        constexpr auto grid = std::get<Index::value>(d2c_grids);
        static_assert(not group::is_invariant(grid, group::d4));
        static_assert(not group::is_invariant(grid, group::z4));
        static_assert(not group::is_invariant(grid, group::d2o));
        static_assert(    group::is_invariant(grid, group::d2c));
        static_assert(not group::is_invariant(grid, group::z2d));
        static_assert(not group::is_invariant(grid, group::z2a));
        static_assert(    group::is_invariant(grid, group::d1r));
        static_assert(    group::is_invariant(grid, group::d1v));
        static_assert(    group::is_invariant(grid, group::d1h));
}

constexpr auto d1r_grids = std::tuple
{       chequer{2, 4, 0}
,       chequer{2, 4, 1}
,       chequer{2, 6, 0}
,       chequer{2, 6, 1}
,       chequer{4, 2, 0}
,       chequer{4, 2, 1}
,       chequer{4, 6, 0}
,       chequer{4, 6, 1}
};

using D1RIndices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(d1r_grids)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(D1RGridsAreInvariantUnderD1R, Index, D1RIndices)
{
        constexpr auto grid = std::get<Index::value>(d1r_grids);
        static_assert(not group::is_invariant(grid, group::d4));
        static_assert(not group::is_invariant(grid, group::z4));
        static_assert(not group::is_invariant(grid, group::d2o));
        static_assert(not group::is_invariant(grid, group::d2c));
        static_assert(not group::is_invariant(grid, group::z2d));
        static_assert(not group::is_invariant(grid, group::z2a));
        static_assert(    group::is_invariant(grid, group::d1r));
        static_assert(not group::is_invariant(grid, group::d1v));
        static_assert(not group::is_invariant(grid, group::d1h));
}

constexpr auto d1v_grids = std::tuple
{       chequer{2, 1, 0}
,       chequer{2, 1, 1}
,       chequer{2, 3, 0}
,       chequer{2, 3, 1}
,       chequer{4, 1, 0}
,       chequer{4, 1, 1}
,       chequer{4, 3, 0}
,       chequer{4, 3, 1}
};

using D1VIndices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(d1v_grids)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(D1VGridsAreInvariantUnderD1V, Index, D1VIndices)
{
        constexpr auto grid = std::get<Index::value>(d1v_grids);
        static_assert(not group::is_invariant(grid, group::d4));
        static_assert(not group::is_invariant(grid, group::z4));
        static_assert(not group::is_invariant(grid, group::d2o));
        static_assert(not group::is_invariant(grid, group::d2c));
        static_assert(not group::is_invariant(grid, group::z2d));
        static_assert(not group::is_invariant(grid, group::z2a));
        static_assert(not group::is_invariant(grid, group::d1r));
        static_assert(    group::is_invariant(grid, group::d1v));
        static_assert(not group::is_invariant(grid, group::d1h));
}

constexpr auto d1h_grids = std::tuple
{       chequer{1, 2, 0}
,       chequer{1, 2, 1}
,       chequer{1, 4, 0}
,       chequer{1, 4, 1}
,       chequer{3, 2, 0}
,       chequer{3, 2, 1}
,       chequer{3, 4, 0}
,       chequer{3, 4, 1}
};

using D1HIndices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(d1h_grids)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(D1HGridsAreInvariantUnderD1H, Index, D1HIndices)
{
        constexpr auto grid = std::get<Index::value>(d1h_grids);
        static_assert(not group::is_invariant(grid, group::d4));
        static_assert(not group::is_invariant(grid, group::z4));
        static_assert(not group::is_invariant(grid, group::d2o));
        static_assert(not group::is_invariant(grid, group::d2c));
        static_assert(not group::is_invariant(grid, group::z2d));
        static_assert(not group::is_invariant(grid, group::z2a));
        static_assert(not group::is_invariant(grid, group::d1r));
        static_assert(not group::is_invariant(grid, group::d1v));
        static_assert(    group::is_invariant(grid, group::d1h));
}

BOOST_AUTO_TEST_SUITE_END()
