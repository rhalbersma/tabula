//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/grids.hpp>             // chequered, rectangle 
#include <tabula/padding.hpp>           // padding
#include <boost/mp11/list.hpp>          // mp_list
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE_TEMPLATE
#include <concepts>                     // regular

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

BOOST_AUTO_TEST_SUITE_END()
