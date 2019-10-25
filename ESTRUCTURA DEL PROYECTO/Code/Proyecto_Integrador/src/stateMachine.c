/*
 * stateMachine.c
 *
 *  Created on: 09/10/2019
 *     This is a state machine that provides with the current state of the system to any
 *     element that need it.
 */

#include "stateMachine.h"
#include "IC_Thread.h"

/*Top level state in case any client of the state machine needs to synchronization*/
ioport_level_t P05_sw5_status;
ioport_level_t P06_sw4_status;
ioport_level_t LedGreen=C_LED_OFF;//green
ioport_level_t LedRed=C_LED_OFF;//red
ioport_level_t LedYellow=C_LED_OFF;//yellow

/*Top level state in case any client of the state machine needs to synchronization*/
int myState=0;

int stateMachine(int *state)
{

	/*Read buttons*/
	g_ioport.p_api->pinRead(IOPORT_PORT_00_PIN_05, &P05_sw5_status);
    g_ioport.p_api->pinRead(IOPORT_PORT_00_PIN_06, &P06_sw4_status);

	switch(*state)
	{

	/*Sync*/
	case -1:
		*state=myState;
		break;

	/*Ready*/
	case myInitState:

		/**waiting Switch4 to start */
		if(P06_sw4_status == C_BTN_PRESSED)
		{
			myState=1;
			/*Turn off Led Yellow to indicate the init is done and switch 4 has been pressed to run*/
			LedYellow = C_LED_OFF;
			/*Turn on LED2 to indicate that we are in control*/
			LedGreen = C_LED_ON;
		}
		else
			/*turn on led 1 to indicate we are ready*/
			LedYellow = C_LED_ON;

		break;

	/*Running*/
	case myRunning_State:/*1*/
	   /*only switch 5 pressed can move to stop condition*/
		if(P05_sw5_status == C_BTN_PRESSED)
			{
				myState=2;
				/*Turn off LED green to indicate we need to stop due to switch 5 has been pressed*/
				LedGreen = C_LED_OFF;
				/*Turn on LED red to indicate that we are on hold*/
				LedRed = C_LED_ON;
			}
		else
			LedGreen = !LedGreen;

	break;

	/*Stop*/
	case myStop_State:
		/**waiting Switch4 to go back to run */
		if(P06_sw4_status == C_BTN_PRESSED)
			{
				myState=1;
				/*Turn off LED Red to indicate the stop condition is done and switch 4 has been pressed*/
				LedRed = C_LED_OFF;
				/*Turn on LED green to indicate that we are in control*/
				LedGreen = C_LED_ON;
			}
		else
			LedRed = !LedRed;

		break;

	/*Any unhandle state set init*/
	default:
		*state=myState;

	}

	/******************************************************/
	/*       REFRESH LEDS                                 */
	/******************************************************/
	g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, LedGreen);
	g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, LedRed);
	g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, LedYellow);

	*state=myState;
	return myState;
}
