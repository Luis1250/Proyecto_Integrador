/*
 * test_ADC.c
 *
 *  Created on: 25/10/2019
 *     function to test ADC thread
 */

#include "stateMachine.h"
#include "Display_lib.h"
#include <math.h>
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

/* Local variables*/
#define K 2.0
float y;
float y_0=0;

/*transfer function from set point to speed reference*/
double PI_Transfer_Function_x1 = 1.445E-7;
double PI_Transfer_Function_x2 = -4.206E-5;
double PI_Transfer_Function_x3 = 0.004221;
double PI_Transfer_Function_x4 = -0.1603;
double PI_Transfer_Function_x5 = 1.372;
double PI_Transfer_Function_x6 = 38.38;
double PI_Transfer_Function_x7 = 31.37;

float PI_Transfer_Function_y1 = 0.0267;
float PI_Transfer_Function_y2 = 12.36;

/*Duty cycle variables*/
int dutyCycle;
float dutyCycle_ref;
float dutyCycle_E;
int dutyCycleDisplay;
int adcData;
float variable_rpm_rx;

//Control Variables
float Ctrl_I;
float Ctrl_I_0;
float Ctrl_D;
float dutyCycle_E;
float dutyCycle_E_0;
float dutyCycle_out;
float Ki = 0.253461615626274;
float Kp = 0.39644212156124;
float Kd = 0.0220414662986352;
float speed_demand;


void input_capture_hal_module_guide_project();
void error_trap(char *);


int test_ADC(int, float );

int test_ADC(int adc, float rpm_input)
 {                                                                                                                            
	adcData = adc;
	variable_rpm_rx=rpm_input;
	/*funtion*/
	y = (float)(adcData*(100.0/255.0));
	             y_0 = y;
	             dutyCycle = (int )y;

	             /*Calculate the dutyCycle to display*/
	             dutyCycleDisplay=100-dutyCycle;


	             /*get Actual speed*/
	             /*tx_queue_receive(&ADC_Queue, &variable_rpm_rx, 20);*/

	             /*Calculate the speed reference*/
	             dutyCycle_ref = (float) ((PI_Transfer_Function_x1*pow(dutyCycleDisplay,6)) +
	            		                  (PI_Transfer_Function_x2*pow(dutyCycleDisplay,5)) +
							         	  (PI_Transfer_Function_x3*pow(dutyCycleDisplay,4)) +
							         	  (PI_Transfer_Function_x4*pow(dutyCycleDisplay,3)) +
								          (PI_Transfer_Function_x5*pow(dutyCycleDisplay,2)) +
								          (PI_Transfer_Function_x6*dutyCycleDisplay) +
								           PI_Transfer_Function_x7);
				 

	             /* get the Error*/
	             dutyCycle_E = (dutyCycle_ref - variable_rpm_rx );

	             /*get Integral part */
			    Ctrl_I = Ki *  dutyCycle_E + Ctrl_I_0;

			    /* get derivative part */
			    Ctrl_D = Kd * (dutyCycle_E - dutyCycle_E_0);

			    /* Calculate the new speed demand */
				speed_demand = (((Kp * dutyCycle_E) + Ctrl_I + Ctrl_D));

	             /*Calculate the new PWM position demand*/
	            dutyCycle_out = (PI_Transfer_Function_y1*speed_demand) + PI_Transfer_Function_y2;
	            
	            
	       
	            /*Save the current calculations for next reference*/
	            dutyCycle_E_0 = dutyCycle_E;
	            Ctrl_I_0 = Ctrl_I;

	            /*Sent to th PWM port the PWM calculated demand*/
/*	             g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, (int)dutyCycle, TIMER_PWM_UNIT_PERCENT, 1);*/
	             /*Sent the duty cycle to display*/
	             //setDutyCycle(dutyCycleDisplay);
	             if(dutyCycleDisplay<=1)
	             {
	            	;// setSpeed(0);
	             }
	             else
	             //setSpeed((long)variable_rpm_rx);

	             return y;

 }

