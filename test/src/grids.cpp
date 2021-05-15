//          Copyright Rein Halbersma 2019-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50

#include <tabula/grids.hpp>             // basic_rectangle, chequered_rectangle
#include <tabula/type_traits.hpp>       // square_t
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
,       chequered_rectangle<1, 1>
,       chequered_rectangle<1, 2>
,       chequered_rectangle<2, 1>
,       chequered_rectangle<2, 2>
,       chequered_rectangle<2, 3>
,       chequered_rectangle<3, 2>
,       chequered_rectangle<2, 4>
,       chequered_rectangle<4, 2>
,       chequered_rectangle<3, 3>
,       chequered_rectangle<3, 5>
,       chequered_rectangle<5, 3>
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
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(IndexIsInvertable, Grid, grid_types)
{
        for (auto i = 0; i < Grid::size; ++i) {
                auto const s = Grid::square(i);
                BOOST_CHECK_EQUAL(i, Grid::index(s));
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SquareIsInvertable, Grid, grid_types)
{
        for (auto r = 0; r < Grid::height; ++r) {
                for (auto f = 0; f < Grid::width; ++f) {
                        if (auto const s = square_t<Grid>(f, r); s.is_valid()) {
                                auto const i = Grid::index(s);
                                BOOST_CHECK(s == Grid::square(i));
                        }
                }
        }
}

BOOST_AUTO_TEST_SUITE_END()
