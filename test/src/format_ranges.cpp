//          Copyright Rein Halbersma 2019-2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE, BOOST_CHECK_EQUAL
#include <array>                        // array
#include <format>                       // format
#include <print>                        // println

BOOST_AUTO_TEST_SUITE(FormatRanges)

BOOST_AUTO_TEST_CASE(PrintlnArray)
{
        constexpr auto a = std::array<int, 8>{1, 2, 3, 4, 5, 6, 7, 8};
        std::println("{}", a);
        BOOST_CHECK_EQUAL(std::format("{}", a), "[1, 2, 3, 4, 5, 6, 7, 8]");
}

BOOST_AUTO_TEST_SUITE_END()
