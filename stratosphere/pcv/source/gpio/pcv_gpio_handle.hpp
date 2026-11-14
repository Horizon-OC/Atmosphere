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
#include "../pcv_device_handle.hpp"

namespace ams::pcv::gpio {

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

    bool SetDeviceHandleName(DeviceHandle *handle, const char *name);

    Result FinalizeHandle(DeviceHandle *handle);

    Result ReadAlternateMode(DeviceHandle *handle);
    Result GetDirection(DeviceHandle *handle, GpioDirection &direction);
    Result SetDirection(DeviceHandle *handle, GpioDirection direction);
    Result GetDriveMode(DeviceHandle *hande, GpioDriveMode &mode);
    Result SetDriveMode(DeviceHandle *hande, GpioDriveMode mode);
    Result GetPullState(DeviceHandle *handle, GpioPullState &out_state);
    Result GetOutputValue(DeviceHandle *handle, u8 &output_value);
    Result SetOutputValue(DeviceHandle *handle, u8 output_value);

}
