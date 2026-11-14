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
#include "pcv_hardware_type.hpp"

namespace ams::pcv {

    spl::HardwareType GetHardwareType() {
        static constinit bool cached       = false;
        static constinit u64 hardware_type = 0;

        if (!cached) {
            spl::Initialize();
            R_ABORT_UNLESS(spl::GetConfig(std::addressof(hardware_type), spl::ConfigItem::HardwareType));
            spl::Finalize();
            cached = true;
        }

        return static_cast<spl::HardwareType>(hardware_type);
    }

}
