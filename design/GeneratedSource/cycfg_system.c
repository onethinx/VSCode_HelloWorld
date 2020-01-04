/*******************************************************************************
* File Name: cycfg_system.c
*
* Description:
* System configuration
* This file was automatically generated and should not be modified.
* Device Configurator: 2.0.0.1483
* Device Support Library (../../psoc6pdl): 1.3.1.1499
*
********************************************************************************
* Copyright 2017-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
********************************************************************************/

#include "cycfg_system.h"

#define CY_CFG_SYSCLK_ALTHF_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF0_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF0_FREQ_MHZ 32UL
#define CY_CFG_SYSCLK_CLKHF0_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_IMO_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH2_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH2_SOURCE CY_SYSCLK_CLKPATH_IN_ALTHF
#define CY_CFG_SYSCLK_CLKPERI_ENABLED 1

#if defined (CY_USING_HAL)
	const cyhal_resource_inst_t srss_0_clock_0_pathmux_2_obj = 
	{
		.type = CYHAL_RSC_CLKPATH,
		.block_num = 2U,
		.channel_num = 0U,
	};
#endif //defined (CY_USING_HAL)

__STATIC_INLINE void Cy_SysClk_AltHfInit()
{
    cy_en_ble_eco_status_t status = Cy_BLE_EcoConfigure(CY_BLE_BLESS_ECO_FREQ_32MHZ, CY_BLE_SYS_ECO_CLK_DIV_1, 32U, 25U, CY_BLE_ECO_VOLTAGE_REG_AUTO);
    if ((CY_BLE_ECO_SUCCESS != status) && (CY_BLE_ECO_ALREADY_STARTED !=status))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_ALTHF_ERROR);
    }
}
__STATIC_INLINE void Cy_SysClk_ClkHf0Init()
{
    Cy_SysClk_ClkHfSetSource(0U, CY_CFG_SYSCLK_CLKHF0_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(0U, CY_SYSCLK_CLKHF_NO_DIVIDE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath2Init()
{
    Cy_SysClk_ClkPathSetSource(2U, CY_CFG_SYSCLK_CLKPATH2_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPeriInit()
{
    Cy_SysClk_ClkPeriSetDivider(1U);
}


void init_cycfg_system(void)
{
#if defined (CY_USING_HAL)
	cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_2_obj);
#endif //defined (CY_USING_HAL)
}
