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
#include "../pcv_device_handle.hpp"
#include "../pcv_i2c.hpp"
#include "pcv_rgltr.hpp"
#include "pcv_rgltr_device_handle.hpp"
#include "pcv_rgltr_max77620.hpp"
#include "pcv_rgltr_max77621.hpp"
#include "pcv_rgltr_max77812.hpp"

namespace ams::pcv::rgltr {

    namespace {

        s32 GetRegulatorIdxByName(const char *name) {
            for (u32 idx = 0; idx < RegulatorCount; ++idx) {
                Regulator &regulator = GetRegulator(idx);
                if (std::strcmp(name, regulator.name) != 0) {
                    continue;
                }

                /* Check if the register is present on the board. */
                if (std::strncmp(name, "max77620", 8) == 0) {
                    regulator.type = PmicType_Main;
                } else if (GetRegulatorVariant() != RegulatorVariant_Erista_Max77621) {
                    if (std::strncmp(name, "max77812", 8) != 0) {
                        return -1;
                    }
                    regulator.type = PmicType_Mariko_Dvfs;
                } else {
                    if (std::strncmp(name, "max77621", 8) != 0) {
                        return -1;
                    }
                    regulator.type = PmicType_Erista_Dvfs;
                }

                return static_cast<s32>(idx);
            }

            return -1;
        }

        bool OpenMax77620(u32 idx) {
            Regulator &regulator = GetRegulator(idx);
            if (!regulator.is_initialized) {
                return false;
            }

            regulator.ref_count++;

            return true;
        }

        bool OpenMax77621(u32 idx) {
            Regulator &regulator = GetRegulator(idx);
            if (!regulator.is_initialized) {
                return false;
            }

            /* Just open it and move on with your live */
            if (regulator.ref_count <= 0) {
                R_ABORT_UNLESS(i2c::OpenSession(regulator.session, static_cast<DeviceCode>(regulator.i2c_device_code)));
            }

            regulator.ref_count++;

            return true;
        }

        /* was this dev on drugs? I need therapy now... */
        bool OpenMax77812(u32 idx) {
            Regulator &regulator = GetRegulator(idx);

            /* Nintendo uses a global session here, but this is uggly and the session in the struct should always be valid. */
            {
                /* They don't actually use this lol. */
                u8 m1_cfg;
                R_DISCARD(I2cRead(*regulator.session, Max77812M1CfgReg, m1_cfg));
            }

            if (!regulator.is_initialized) {
                return false;
            }

            /* Increment the reference count. */
            if (regulator.ref_count++ <= 0) {
                /* If it's now zero or negative it's now magically initialized! */
                regulator.is_initialized = true;

                /* To end this fever dream, read the register again! */
                {
                    u8 m1_cfg;
                    R_DISCARD(I2cRead(*regulator.session, Max77812M1CfgReg, m1_cfg));
                }
            }

            /* Succeed regardless of the outcome of the i2c read. */
            return true;
        }

        bool OpenById(u32 idx) {
            Regulator &regulator = GetRegulator(idx);

            bool opened;
            switch (regulator.type) {
                case PmicType_Main:        opened = OpenMax77620(idx); break;
                case PmicType_Erista_Dvfs: opened = OpenMax77621(idx); break;
                case PmicType_Mariko_Dvfs: opened = OpenMax77812(idx); break;
                default:                   return false;
            }

            if (opened && regulator.ref_count == 1) {
                regulator.is_open = true;
            }

            return opened;
        }

        bool CloseById(u32 idx) {
            Regulator &regulator = GetRegulator(idx);

            bool closed;
            switch (regulator.type) {
                case PmicType_Main:        closed = FinalizeMax77620(idx); break;
                case PmicType_Erista_Dvfs: closed = FinalizeMax77621(idx); break;
                case PmicType_Mariko_Dvfs: closed = FinalizeMax77812(idx); break;
                default:                   return false;
            }

            if (closed && regulator.ref_count == 0) {
                regulator.is_open = false;
            }

            return closed;
        }

    }

    /* Todo deduplicate this? */
    bool InitializeHandleByName(DeviceHandle *handle, const char *name) {
        /* Note: Nintendo has (technically) a bug here AGAIN: They have an off by one in the length check and then proceed to use strcpy. */
        /* This can technically overwrite the device index, but the gpio names are too short for that to occur. */
        if (handle == nullptr || name == nullptr || std::strlen(name) >= DeviceNameSize) {
            return false;
        }

        const s32 idx = GetRegulatorIdxByName(name);
        if (idx < 0) {
            return false;
        }

        /* OPen it. */
        if (!OpenById(static_cast<u32>(idx))) {
            return false;
        }

        /* Set the device name and index.. */
        handle->device_index = idx;
        std::memcpy(handle->name, name, std::strlen(name) + 1);

        return true;
    }

    bool FinalizeHandle(DeviceHandle *handle) {
        return IsRegulatorOpen(handle->device_index) && CloseById(handle->device_index);
    }

    bool IsRegulatorOpen(u32 idx) {
        return idx <= RegulatorMaxIdx && GetRegulator(idx).is_open;
    }

}
