//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/grids.hpp>             // chequer, rectangle 
#include <boost/mp11/algorithm.hpp>     // mp_iota_c
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE_TEMPLATE, BOOST_CHECK, BOOST_CHECK_EQUAL
#include <algorithm>                    // equal
#include <array>                        // array
#include <ranges>                       // filter, transform
#include <tuple>                        // get, tuple, tuple_size_v

using namespace tabula;

BOOST_AUTO_TEST_SUITE(Compass)

constexpr auto grids = std::tuple
(       rectangle{1, 1}
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
);

using Indices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(grids)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(CardinalDirectionsAreCardinal, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        using compass = basic_compass<grid>;
        auto computed 
                = compass::directions 
                | std::views::filter([](auto d) { return d.is_cardinal(); })
        ;
        auto expected 
                = std::array{ compass::N, compass::E, compass::S, compass::W } 
                | std::views::transform([](auto d) { return compass::directions[d]; })
        ;
        BOOST_CHECK(std::ranges::equal(computed, expected));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(OrdinalDirectionsAreIsOrdinal, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        using compass = basic_compass<grid>;
        auto computed 
                = compass::directions 
                | std::views::filter([](auto d) { return d.is_ordinal(); })
        ;
        auto expected 
                = std::array{ compass::NE, compass::SE, compass::SW, compass::NW } 
                | std::views::transform([](auto d) { return compass::directions[d]; })
        ;
        BOOST_CHECK(std::ranges::equal(computed, expected));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(IsReverse, Index, Indices)
{
        constexpr auto grid = std::get<Index::value>(grids);
        using compass = basic_compass<grid>;
        for (auto d : compass::directions) {
                auto const r = d.reverse();
                BOOST_CHECK((d != r));
                BOOST_CHECK_EQUAL(d.is_left() ,  r.is_right());
                BOOST_CHECK_EQUAL(d.is_right(),  r.is_left() );
                BOOST_CHECK_EQUAL(d.is_up()   ,  r.is_down() );
                BOOST_CHECK_EQUAL(d.is_down() ,  r.is_up()   );
        }
}

BOOST_AUTO_TEST_SUITE_END()
