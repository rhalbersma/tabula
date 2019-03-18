//          Copyright Rein Halbersma 2014-2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/compass.hpp>                   // basic_compass
#include <tabula/shapes.hpp>                    // basic_rectangle
#include <boost/mpl/vector.hpp>                 // vector
#include <boost/test/test_case_template.hpp>    // BOOST_AUTO_TEST_CASE_TEMPLATE
#include <boost/test/unit_test.hpp>             // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END

using namespace tabula;

BOOST_AUTO_TEST_SUITE(Compass)

using shape_types = boost::mpl::vector<
        basic_rectangle<2, 2>,
        basic_rectangle<2, 4>,
        basic_rectangle<4, 2>,
        basic_rectangle<2, 3>,
        basic_rectangle<3, 2>,
        basic_rectangle<3, 3>,
        basic_rectangle<3, 5>,
        basic_rectangle<5, 3>,
        chequered_rectangle<2, 2>
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(Reverse, T, shape_types)
{
        constexpr auto compass = basic_compass<T>{};
        for (auto p : compass.points) {
                auto const r = p.reverse();
                BOOST_CHECK(p != r);
                BOOST_CHECK_EQUAL(p.stride()  , -r.stride()  );
                BOOST_CHECK_EQUAL(p.is_left() ,  r.is_right());
                BOOST_CHECK_EQUAL(p.is_right(),  r.is_left() );
                BOOST_CHECK_EQUAL(p.is_up()   ,  r.is_down() );
                BOOST_CHECK_EQUAL(p.is_down() ,  r.is_up()   );
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Cardinal, T, shape_types)
{
        constexpr auto compass = basic_compass<T>{};
        for (auto p : { compass.N, compass.E, compass.S, compass.W }) {
                BOOST_CHECK(compass.points[p].is_cardinal());
        }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Ordinal, T, shape_types)
{
        constexpr auto compass = basic_compass<T>{};
        for (auto p : { compass.NE, compass.SE, compass.SW, compass.NW }) {
                BOOST_CHECK(compass.points[p].is_ordinal());
        }
}

BOOST_AUTO_TEST_SUITE_END()

