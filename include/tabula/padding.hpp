#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

// CSS padding Property: https://www.w3schools.com/cssref/pr_padding.asp

struct padding
{
        int top;
        int right;
        int bottom;
        int left;

        [[nodiscard]] constexpr auto operator==(padding const&) const noexcept -> bool = default;
};

[[nodiscard]] inline constexpr auto pad_right(int r) noexcept
{
        return padding(0, r, 0, 0);
}

[[nodiscard]] inline constexpr auto mailbox(int tb, int rl) noexcept
{
        return padding(tb, rl, tb, rl);
}

}       // namespace tabula
