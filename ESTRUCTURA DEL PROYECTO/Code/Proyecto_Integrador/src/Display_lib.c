/*
 * Display_lib.c
 *
 *  Created on: 07/10/2019
 *      Utilities for Display Thread
 *
 *      logic flow1:
 *      The Thread has variables that always are display,
 *      If any external function wants to modify those values,
 *      they use the interface to modify that value.
 *
 */

#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include "Display_Thread.h"
#include "stateMachine.h"
#include "display_lib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int screenDutyCyle;
int screenSpeed;
int screenSetPoint;
int screenSWVer;
int screenState;

display_type display;

void Refresh_Screen()
{
	//display state
	screenState=-1;
	screenState=stateMachine(&screenState);
	if(screenState==myInitState)
	{
		gx_prompt_text_set(&window1.window1_state,"READY");
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_state);
	}
	else if(screenState==myRunning_State)
	{
		gx_prompt_text_set(&window1.window1_state,"Running");
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_state);

		//Duty Cycle
		gx_prompt_text_set(&window1.window1_counter_dutycycle,display.dutyCycle);
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_counter_dutycycle);

		//Speed RPM
		gx_prompt_text_set(&window1.window1_speedcounter,display.speed);
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_speedcounter);

	}
	else if(screenState==myStop_State)
	{
		gx_prompt_text_set(&window1.window1_state,"ON-HOLD");
		gx_system_dirty_mark((GX_WIDGET*)&window1.window1_state);
	}





	GX_CHAR swVerAux[5];
	UINT DEFAULT_SIZE = 5;


	 LONG swVer = 5;
	 gx_utility_ltoa(swVer,swVerAux,DEFAULT_SIZE);
     gx_prompt_text_set(&window1.window1_swver,swVerAux);
     gx_prompt_text_set(&window1.window1_swver,"1.0");
	 gx_system_dirty_mark((GX_WIDGET*)&window1.window1_swver);
	 gx_system_canvas_refresh();
}

void setDutyCycle(ULONG x)
{
	/*Convert % from 0-100*/
	char string[4];

	if (x==0)
		{
		  string[0]='0';
		  string[1]='\0';
		}
	else if (x>=100)
	{
		string[0]='1';
		string[1]='0';
	    string[2]='0';
		string[3]='\0';
	}
	else
	{
		itoa((int)x,string,10);
	}

	strcpy(display.dutyCycle,string);


}

void setSpeed(ULONG x)
{ /*converts speed to string
   *operative range 0-9,999 */
	char string[5];
	if(x>9999)
		x=9999;

	itoa((int)x,string,10);

	strcpy(display.speed,string);

}



void setSetPoint(ULONG x)
{ /*converts speed to string
   *operative range 0-9,999 */
	char string[5];
	if(x>9999)
		x=9999;

	itoa((int)x,string,10);

	strcpy(display.setPoint,string);

}
