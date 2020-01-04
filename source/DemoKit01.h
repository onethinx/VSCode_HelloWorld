/* ==========================================================
 *	___			 _   _	 _			
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
#ifndef DEMOKIT01_H
#define DEMOKIT01_H	
 
#include <stdint.h>
#include <stdbool.h>

#define LED_OFF 0
#define LED_ON 1

#define LED_R_SET(value)		Cy_GPIO_Write(LED_RED_PORT, LED_RED_PIN, value)
#define LED_B_SET(value)		Cy_GPIO_Write(LED_BLUE_PORT, LED_BLUE_NUM, value)
#define LED_B_INV				Cy_GPIO_Inv( P12_4_PORT, P12_4_NUM )
#define LED_R_INV				Cy_GPIO_Inv( P12_5_PORT, P12_5_NUM )

#endif /* DEMOKIT01_H */

