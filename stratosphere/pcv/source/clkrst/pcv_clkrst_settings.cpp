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

#include <stratosphere.hpp>

namespace ams::pcv::clkrst {

    bool GetNvSettingInteger(u32 *out, const char *key) {
        /* NOTE: Nintendo does not expose this on prod. */
        char buf[17] = {};
        const size_t size = settings::fwdbg::GetSettingsItemValue(buf, sizeof(buf) - 1, "nv", key);

        /* Setting item not found. */
        if (size == 0 || buf[0] == '\0') {
            return false;
        }

        char *end;
        const u64 value = std::strtoul(buf, std::addressof(end), 0);

        if (end == buf) {
            return false;
        }

        *out = static_cast<u32>(value);

        return true;
    }

}
