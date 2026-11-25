/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <stratosphere.hpp>
#include "pcv_clkrst_pll.hpp"
#include "pcv_clkrst_table_util.hpp"

namespace ams::pcv::clkrst {

    namespace impl {

        #include "pcv_clkrst_pll_data.inc"

        static_assert(std::size(PllInfoTableT210) == std::size(PllInfoTableT210B01));

        void InvalidPllName();

    }

    consteval size_t FindPllIndex(std::string_view name) {
        const size_t index = FindIndexByName(impl::PllInfoTableT210, name);

        if (index == std::size(impl::PllInfoTableT210) || index != FindIndexByName(impl::PllInfoTableT210B01, name)) {
            impl::InvalidPllName();
        }

        return index;
    }

}
