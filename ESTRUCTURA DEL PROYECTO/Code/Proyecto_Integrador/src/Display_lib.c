/*
 * Display_lib.c
 *
 *  Created on: 07/10/2019
 *      Author: mulca
 */

#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include "Display_Thread.h"
#include "stateMachine.h"
#include "display_lib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


display_type display;

void Refresh_Screen()
{
	/*Local Variables*/
	int screenState;
	UINT status;

	/*display state*/
	screenState=-1;
	screenState=stateMachine(&screenState);

	/*Initialization*/
	if(screenState==myInitState)
	{
		status = gx_prompt_text_set(&window1.window1_state,"READY");
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_state);
	}
	/*Running*/
	else if(screenState==myRunning_State)
	{
		status = gx_prompt_text_set(&window1.window1_state,"Running");
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_state);

		/*Duty Cycle*/
		status = gx_prompt_text_set(&window1.window1_counter_dutycycle,display.dutyCycle);
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_counter_dutycycle);

		/*Speed RPM*/
		status = gx_prompt_text_set(&window1.window1_speedcounter,display.speed);
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_speedcounter);

	}
	/*Stop*/
	else if(screenState==myStop_State)
	{
		status = gx_prompt_text_set(&window1.window1_state,"ON-HOLD");
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_state);
	}

     /*widgets without state dependency */
	 status = gx_prompt_text_set(&window1.window1_swver,"0.5");
	 gx_system_dirty_mark((GX_WIDGET*)&window1.window1_swver);
	 gx_system_canvas_refresh();

	 /*Test point for debugging*/
	 status++;
}

void setDutyCycle(int x)
{
	/*Convert % from 0-100*/
	char string[4];


	itoa(x,string,10);


	strcpy(display.dutyCycle,string);

}

void setSpeed(int x)
{ /*converts speed to string
   *operative range 0-9,999 */
	char string[5];
	if(x>9999)
		x=9999;

	itoa(x,string,10);

	strcpy(display.speed,string);

}



void setSetPoint(int x)
{ /*converts speed to string
   *operative range 0-9,999 */
	char string[5];
	if(x>9999)
		x=9999;

	itoa(x,string,10);

	strcpy(display.setPoint,string);

}
