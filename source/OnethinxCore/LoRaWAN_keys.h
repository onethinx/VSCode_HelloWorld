/* ==========================================================
 *    ___             _   _     _			
 *   / _ \ _ __   ___| |_| |__ (_)_ __ __  __
 *  | | | | '_ \ / _ \ __| '_ \| | '_ \\ \/ /
 *  | |_| | | | |  __/ |_| | | | | | | |>  < 
 *   \___/|_| |_|\___|\__|_| |_|_|_| |_/_/\_\
 *									   
 * Copyright Onethinx, 2018
 * All Rights Reserved
 *
 * UNPUBLISHED, LICENSED SOFTWARE.
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Onethinx BV
 *
 * ==========================================================
*/

#ifndef LORAWAN_KEYS_H
#define LORAWAN_KEYS_H

#include "OnethinxCore01.h"

LoRaWAN_keys_t TTN_OTAAkeys = {
	.KeyType 						= OTAA_10x_key,
	.PublicNetwork					= true,
	.OTAA_10x.DevEui				= {{ 0xd1, 0xeb, 0xc9, 0xad, 0xbd, 0xcd, 0xe0, 0xe4 }},
	.OTAA_10x.AppEui				= {{ 0x94, 0x81, 0x65, 0x04, 0x40, 0x30, 0x28, 0x10 }},
	.OTAA_10x.AppKey				= {{ 0xa2, 0xfc, 0xbf, 0x6b, 0x81, 0x60, 0x0d, 0x26, 0x61, 0xc1, 0xac, 0xf6, 0x17, 0x90, 0x43, 0x2c }}
};

#endif /* LORAWAN_KEYS_H */
/* [] END OF FILE */
