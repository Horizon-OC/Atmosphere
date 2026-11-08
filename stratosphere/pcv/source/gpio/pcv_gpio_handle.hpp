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

namespace ams::pcv::gpio {

    constexpr size_t GpioDeviceNameSize = 32;

    struct GpioDeviceHandle {
        char name[GpioDeviceNameSize];
        s32 device_index;
    };

    enum GpioDirection : u8 {
        GpioDirection_Output = 0,
        GpioDirection_Input  = 1,
    };

    enum GpioDriveMode : u8 {
        GpioDriveMode_OpenDrain = 0,
        GpioDriveMode_PushPull  = 1,
    };

    enum GpioPullState : u8 {
        GpioPullState_Up      = 0,
        GpioPullState_Down    = 1,
        GpioPullState_None    = 2,
        GpioPullState_Invalid = 3,
    };

    bool SetDeviceHandleName(GpioDeviceHandle *handle, const char *name);

    Result FinalizeHandle(GpioDeviceHandle *handle);

    Result ReadAlternateMode(GpioDeviceHandle *handle);
    Result GetDirection(GpioDeviceHandle *handle, GpioDirection &direction);
    Result SetDirection(GpioDeviceHandle *handle, GpioDirection direction);
    Result GetDriveMode(GpioDeviceHandle *hande, GpioDriveMode &mode);
    Result SetDriveMode(GpioDeviceHandle *hande, GpioDriveMode mode);
    Result GetPullState(GpioDeviceHandle *handle, GpioPullState &out_state);
    Result GetOutputValue(GpioDeviceHandle *handle, u8 &output_value);
    Result SetOutputValue(GpioDeviceHandle *handle, u8 output_value);

}
