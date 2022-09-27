//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50

#include <tabula/grids.hpp>             // basic_rectangle, chequered_rectangle
#include <boost/mpl/vector.hpp>         // vector
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE_TEMPLATE, BOOST_CHECK, BOOST_CHECK_EQUAL

using namespace tabula;

BOOST_AUTO_TEST_SUITE(Compass)

using grid_types = boost::mpl::vector
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
,       chequered_rectangle<1, 1, 0>
,       chequered_rectangle<1, 2, 0>
,       chequered_rectangle<2, 1, 0>
,       chequered_rectangle<2, 2, 0>
,       chequered_rectangle<2, 3, 0>
,       chequered_rectangle<3, 2, 0>
,       chequered_rectangle<2, 4, 0>
,       chequered_rectangle<4, 2, 0>
,       chequered_rectangle<3, 3, 0>
,       chequered_rectangle<3, 5, 0>
,       chequered_rectangle<5, 3, 0>
,       chequered_rectangle<1, 1, 1>
,       chequered_rectangle<1, 2, 1>
,       chequered_rectangle<2, 1, 1>
,       chequered_rectangle<2, 2, 1>
,       chequered_rectangle<2, 3, 1>
,       chequered_rectangle<3, 2, 1>
,       chequered_rectangle<2, 4, 1>
,       chequered_rectangle<4, 2, 1>
,       chequered_rectangle<3, 3, 1>
,       chequered_rectangle<3, 5, 1>
,       chequered_rectangle<5, 3, 1>
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(IsCardinal, Grid, grid_types)
{
        for (auto d : { Grid::N, Grid::E, Grid::S, Grid::W }) {
                BOOST_CHECK(Grid::directions[d].is_cardinal());
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(IsOrdinal, Grid, grid_types)
{
        for (auto d : { Grid::NE, Grid::SE, Grid::SW, Grid::NW }) {
                BOOST_CHECK(Grid::directions[d].is_ordinal());
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(IsReverse, Grid, grid_types)
{
        for (auto d : Grid::directions) {
                auto const r = d.reverse();
                BOOST_CHECK((d != r));
                BOOST_CHECK_EQUAL(d.is_left() ,  r.is_right());
                BOOST_CHECK_EQUAL(d.is_right(),  r.is_left() );
                BOOST_CHECK_EQUAL(d.is_up()   ,  r.is_down() );
                BOOST_CHECK_EQUAL(d.is_down() ,  r.is_up()   );
        }
}

BOOST_AUTO_TEST_SUITE_END()
