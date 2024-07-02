//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/concepts.hpp>          // chequered, rectangular
#include <tabula/grids.hpp>             // chequer, rectangle 
#include <tabula/padding.hpp>           // padding
#include <boost/mp11/algorithm.hpp>     // mp_iota_c
#include <boost/mp11/list.hpp>          // mp_list
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE_TEMPLATE
#include <concepts>                     // regular
#include <tuple>                        // get, tuple, tuple_size_v

using namespace tabula;

BOOST_AUTO_TEST_SUITE(Concepts)

using LiteralTypes = boost::mp11::mp_list
<       chequer
,       rectangle
,       padding
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(LiteralTypesAreRegular, T, LiteralTypes)
{
        static_assert(std::regular<T>);
}

constexpr auto rectangles = std::tuple
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
};

using RectangleIndices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(rectangles)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(RectanglesAreRectangular, Index, RectangleIndices)
{
        constexpr auto grid = std::get<Index::value>(rectangles);
        static_assert(rectangular<grid>);
}

constexpr auto chequers = std::tuple
{       chequer{1, 1, 0}
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

using ChequerIndices = boost::mp11::mp_iota_c<std::tuple_size_v<decltype(chequers)>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ChequersAreChequered, Index, ChequerIndices)
{
        constexpr auto grid = std::get<Index::value>(chequers);
        static_assert(chequered<grid>);
}

BOOST_AUTO_TEST_SUITE_END()
