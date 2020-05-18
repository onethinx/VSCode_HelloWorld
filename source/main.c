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
#include "OnethinxCore01.h"
#include "DemoKit01.h"
#include "LoRaWAN_keys.h"
#include "cycfg.h"

/* Go to ../OnethinxCore/LoRaWAN_keys.h and fill in the fields of the TTN_OTAAkeys structure */

coreConfiguration_t	coreConfig = {
	.Join.KeysPtr = 		&TTN_OTAAkeys,
	.Join.DataRate =		DR_AUTO,
	.Join.Power =			PWR_MAX,
	.Join.MAXTries = 		100,
    .Join.SubBand_1st =     EU_SUB_BANDS_DEFAULT,
	.Join.SubBand_2nd =     EU_SUB_BANDS_DEFAULT,
	.TX.Confirmed = 		false,
	.TX.DataRate = 			DR_ADR,		// Adaptive Data Rate
	.TX.Power = 			PWR_ADR,	// Adaptive Data Rate
	.TX.FPort = 			1,
	.System.Idle.Mode = 	M0_DeepSleep,
	.System.Idle.BleEcoON = false,
	.System.Idle.DebugON =  true,
};

sleepConfig_t sleepConfig =
{
	.sleepMode = modeDeepSleep,
	.BleEcoON = false,
	.DebugON = true,
	.sleepCores = coresBoth,
	.wakeUpPin = wakeUpPinHigh(true),
	.wakeUpTime = wakeUpDelay(0, 0, 0, 20), // day, hour, minute, second
};

/*******************************************************************************arm-none-eabi-gcc
* Function Name: main()
********************************************************************************
* Summary:
*  Sends a "Hello World" message using LoRaWAN.
* Details:
*  Go to ../OnethinxCore/LoRaWAN_keys.h and fill in the fields of the TTN_OTAAkeys structure
*  Read the quickstart guide on how to create keys.
*******************************************************************************/

/* OnethinxCore uses the following structures and variables, which can be defined globally */
coreStatus_t 	coreStatus;
coreInfo_t 		coreInfo;

uint8_t RXbuffer[64];
uint8_t TXbuffer[64];

int main(void)
{
	CyDelay(1000); // Needs to be here
	uint8_t j=0;

	/* initialize hardware configuration */
	init_cycfg_all();

	/* enable global interrupts */
	__enable_irq();

	/* Blue LED ON while joining*/
	LED_B_SET(LED_ON);

	/* initialize radio with parameters in coreConfig */
	coreStatus = LoRaWAN_Init(&coreConfig);

	/* Check Onethinx Core info */
	LoRaWAN_GetInfo(&coreInfo);

	/* send join using parameters in coreConfig, blocks until either success or MAXtries */
	coreStatus = LoRaWAN_Join(M4_WaitDeepSleep);

	/* check for successful join, flash Red LED if not joined */
	if (!coreStatus.mac.isJoined){
		LED_B_SET(LED_OFF);
		while(1) {
			LED_R_INV;
			CyDelay(100);
		}
	}
	LED_B_SET(LED_OFF);

	/* main loop */
	for(;;)
	{
		/* Blue LED on while sending*/
		LED_B_SET(LED_ON);

		/* Compose a message to send */
        j=0;
        TXbuffer[j++] = 0x48; /* H */
		TXbuffer[j++] = 0x45; /* E */
		TXbuffer[j++] = 0x4c; /* L */
		TXbuffer[j++] = 0x4c; /* L */
		TXbuffer[j++] = 0x4f; /* O */
		TXbuffer[j++] = 0x20; /*   */
		TXbuffer[j++] = 0x57; /* W */
		TXbuffer[j++] = 0x4f; /* O */
		TXbuffer[j++] = 0x52; /* R */
		TXbuffer[j++] = 0x4c; /* L */
		TXbuffer[j++] = 0x44; /* D */

		/* Send message over LoRaWAN */
        coreStatus = LoRaWAN_Send(TXbuffer, j, M4_WaitDeepSleep);

		/* Turn led off before sleep */
		LED_B_SET(LED_ON);

		/* Sleep before sending next message, wake up with a button as well */
		LoRaWAN_Sleep(&sleepConfig);
	}
}


/* [] END OF FILE */
