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
#include "pcv_rgltr_power_domain.hpp"

namespace ams::pcv::rgltr {

    Result SetVoltage(PowerDomain *domain, u32 micro_volts);
    Result GetVoltage(PowerDomain *domain, u32 &micro_volts);
    Result GetCachedVoltage(PowerDomain *domain, u32 &micro_volts);
    Result EnablePowerDomain(PowerDomain *domain);
    Result IsPowerDomainEnabled(PowerDomain *domain, bool &enabled);
    Result GetStateTable(PowerDomainState *state, s32 *out_count, s32 max_count);
    s32 GetStateTableCount();

}
