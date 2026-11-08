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

#include "pcv_gpio_handle.hpp"
#include "pcv_gpio.hpp"
#include "../pcv_i2c.hpp"

namespace ams::pcv::gpio {

    namespace {

        using GpioDevice = Max77620GpioEntry;

        /* Slightly gross because this is technically not a result. */
        constexpr Result DeviceNotReady = -3;

    }

    bool SetDeviceHandleName(GpioDeviceHandle *handle, const char *name) {
        /* Note: Nintendo has (technically) a bug here: They have an off by one in the length check and then proceed to use strcpy. */
        /* This can technically overwrite the device index, but the gpio names are too short for that to occur. */

        if (handle == nullptr || name == nullptr || std::strlen(name) >= GpioDeviceNameSize) {
            return false;
        }

        s32 device_idx = FindDeviceIdxByName(name);

        if (device_idx == -1) {
            return false;
        }

        /* Set the device index and name. */
        handle->device_index = device_idx;
        std::memcpy(handle->name, name, std::strlen(name) + 1);

        return true;
    }

    Result FinalizeHandle(GpioDeviceHandle *handle) {
        R_UNLESS(IsDeviceReady(handle->device_index), DeviceNotReady);

        FinalizeDevice(handle->device_index);

        return ResultSuccess();
    }

    Result ReadAlternateMode(GpioDeviceHandle *handle) {
        /* NOTE: Nintendo returns a specific value depending on the index, bitmask of the device and the register value, */
        /* But they never use it. */
        /* TODO: Determine if we should do the same. */
        /* For now let's just read the register and move on. */

        R_UNLESS(IsDeviceReady(handle->device_index), DeviceNotReady);
        {
            GpioDevice &device = GetGpioDevice(handle->device_index);

            u8 out;
            return I2cRead(*device.session, device.ame_reg, out);
        }

        return ResultSuccess();
    }

    Result GetDirection(GpioDeviceHandle *handle, GpioDirection &direction) {
        R_UNLESS(IsDeviceReady(handle->device_index), DeviceNotReady);
        {
            GpioDevice &device = GetGpioDevice(handle->device_index);

            u8 out;
            R_TRY(I2cRead(*device.session, device.gpio_cfg_reg, out));

            /* Input/output direction. */
            direction = static_cast<GpioDirection>((out & Max77620PmicGpioDirMask) >> Max77620PmicGpioDirShift);
        }

        return ResultSuccess();
    }

    Result SetDirection(GpioDeviceHandle *handle, GpioDirection direction) {
        /* Only keep the lowest bit. */
        const u8 dir_bit = static_cast<u8>(direction) & 1;

        R_UNLESS(IsDeviceReady(handle->device_index), DeviceNotReady);
        {
            GpioDevice &device = GetGpioDevice(handle->device_index);

            /* Ensure we can read it first. */
            u8 reg_value;
            R_TRY(I2cRead(*device.session, device.gpio_cfg_reg, reg_value));

            /* Set and write the direction. */
            reg_value &= ~Max77620PmicGpioDirMask;
            reg_value |= ((dir_bit << Max77620PmicGpioDirShift) & Max77620PmicGpioDirMask);

            return I2cWrite(*device.session, device.gpio_cfg_reg, reg_value);
        }

        return ResultSuccess();
    }

    Result GetDriveMode(GpioDeviceHandle *handle, GpioDriveMode &mode) {
        R_UNLESS(IsDeviceReady(handle->device_index), DeviceNotReady);
        {
            GpioDevice &device = GetGpioDevice(handle->device_index);

            u8 out;
            R_TRY(I2cRead(*device.session, device.gpio_cfg_reg, out));

            /* push/pull or open drain. */
            mode = static_cast<GpioDriveMode>(out & Max77620PmicGpioDrvMask);
        }

        return ResultSuccess();
    }

    Result SetDriveMode(GpioDeviceHandle *handle, GpioDriveMode mode) {
        /* Only keep the lowest bit. */
        const u8 mode_bit = static_cast<u8>(mode) & 1;

        R_UNLESS(IsDeviceReady(handle->device_index), DeviceNotReady);
        {
            GpioDevice &device = GetGpioDevice(handle->device_index);

            /* Ensure we can read it first. */
            u8 reg_value;
            R_TRY(I2cRead(*device.session, device.gpio_cfg_reg, reg_value));

            /* Set and write the mode. */
            reg_value &= ~Max77620PmicGpioDrvMask;
            reg_value |= mode_bit;

            return I2cWrite(*device.session, device.gpio_cfg_reg, reg_value);
        }

        return ResultSuccess();
    }

    Result GetPullState(GpioDeviceHandle *handle, GpioPullState &out_state) {
        /* On failure: */
        out_state = GpioPullState_Invalid;

        R_UNLESS(IsDeviceReady(handle->device_index), DeviceNotReady);
        {
            GpioDevice &device = GetGpioDevice(handle->device_index);

            u8 reg_value;
            R_TRY(I2cRead(*device.session, device.gpio_cfg_reg, reg_value));

            /* Decide on the pull register. */
            const bool use_pull_down = (reg_value & Max77620PmicGpioOutputValMask) != 0;
            u8 pull_reg;
            if (use_pull_down) {
                pull_reg = Max77620PmicPdeGpioReg;
            } else {
                pull_reg = Max77620PmicPueGpioReg;
            }

            /* Read the pull enable register and check this GPIO's bit. */
            u8 pull_value;
            R_TRY(I2cRead(*device.session, pull_reg, pull_value));

            if ((pull_value & device.bit_mask) == 0) {
                out_state = GpioPullState_None;
            } else {
                if (use_pull_down) {
                    out_state = GpioPullState_Down;
                } else {
                    out_state = GpioPullState_Up;
                }
            }
        }

        return ResultSuccess();
    }

    Result GetOutputValue(GpioDeviceHandle *handle, u8 &output_value) {
        R_UNLESS(IsDeviceReady(handle->device_index), DeviceNotReady);
        {
            GpioDevice &device = GetGpioDevice(handle->device_index);

            u8 reg_value;
            R_TRY(I2cRead(*device.session, device.gpio_cfg_reg, reg_value));

            output_value = (reg_value & Max77620PmicGpioOutputValMask) >> Max77620PmicGpioOutputValShift;
        }

        return ResultSuccess();
    }

    Result SetOutputValue(GpioDeviceHandle *handle, u8 output_value) {
        /* Only keep the lowest bit. */
        output_value &= 1;

        R_UNLESS(IsDeviceReady(handle->device_index), DeviceNotReady);
        {
            GpioDevice &device = GetGpioDevice(handle->device_index);

            u8 reg_value;
            R_TRY(I2cRead(*device.session, device.gpio_cfg_reg, reg_value));

            reg_value &= ~Max77620PmicGpioOutputValMask;
            reg_value |= (output_value << Max77620PmicGpioOutputValShift);

            R_TRY(I2cWrite(*device.session, device.gpio_cfg_reg, reg_value));
        }

        return ResultSuccess();
    }

}
