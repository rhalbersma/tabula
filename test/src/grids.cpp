//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/grids.hpp>             // basic_chequered, basic_rectangle
#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, swapped_t
#include <boost/mp11/list.hpp>          // mp_list
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE_TEMPLATE, BOOST_CHECK, BOOST_CHECK_EQUAL
#include <concepts>                     // same_as
#include <ranges>                       // iota

using namespace tabula;

BOOST_AUTO_TEST_SUITE(Compass)

using GridTypes = boost::mp11::mp_list
<       basic_rectangle<1, 1>
,       basic_rectangle<1, 2>
,       basic_rectangle<2, 1>
,       basic_rectangle<2, 2>
,       basic_rectangle<2, 3>
,       basic_rectangle<3, 2>
,       basic_rectangle<2, 4>
,       basic_rectangle<4, 2>
,       basic_rectangle<3, 3>
,       basic_rectangle<3, 5>
,       basic_rectangle<5, 3>
,       basic_chequered<1, 1, 0>
,       basic_chequered<1, 2, 0>
,       basic_chequered<2, 1, 0>
,       basic_chequered<2, 2, 0>
,       basic_chequered<2, 3, 0>
,       basic_chequered<3, 2, 0>
,       basic_chequered<2, 4, 0>
,       basic_chequered<4, 2, 0>
,       basic_chequered<3, 3, 0>
,       basic_chequered<3, 5, 0>
,       basic_chequered<5, 3, 0>
,       basic_chequered<1, 1, 1>
,       basic_chequered<1, 2, 1>
,       basic_chequered<2, 1, 1>
,       basic_chequered<2, 2, 1>
,       basic_chequered<2, 3, 1>
,       basic_chequered<3, 2, 1>
,       basic_chequered<2, 4, 1>
,       basic_chequered<4, 2, 1>
,       basic_chequered<3, 3, 1>
,       basic_chequered<3, 5, 1>
,       basic_chequered<5, 3, 1>
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(IndexIsInvertible, Grid, GridTypes)
{
        for (auto index : std::views::iota(0, Grid::size)) {
                BOOST_CHECK_EQUAL(index, Grid::index(Grid::square(index)));
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SquareIsInvertible, Grid, GridTypes)
{
        for (auto rank : std::views::iota(0, Grid::height)) {
                for (auto file : std::views::iota(0, Grid::width)) {
                        if (auto const square = basic_square<Grid>{file, rank}; square.is_valid()) {
                                BOOST_CHECK(square == Grid::square(Grid::index(square)));
                        }
                }
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(TransformationsAreIdempotent, Grid, GridTypes)
{
        static_assert(std::same_as<flipped_t<flipped_t<Grid>>, Grid>);
        static_assert(std::same_as<flopped_t<flopped_t<Grid>>, Grid>);
        static_assert(std::same_as<swapped_t<swapped_t<Grid>>, Grid>);
}

BOOST_AUTO_TEST_SUITE_END()
