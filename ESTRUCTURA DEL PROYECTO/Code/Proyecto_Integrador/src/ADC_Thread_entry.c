
/*ADC thread main routine.
 *
 * logic flow:
 * 1) It Starts the configuration of the timer and ADC port.
 * 2) The infinity loop is requesting the current state from the state machine to:
 * 		a) read from the ADC port
 * 		b) convert the input into engineering units (set point)
 * 		c) receive the data from the Input Capture
 * 		d) convert the previous data in engineering units (current speed)
 * 		e) calculate a reference speed
 * 		f) get the error between current speed and desired speed.
 * 		g) convert the error into a delta speed
 * 		h) send the new set point demand to correct the error.
 * 	3) In case that the state machine indicates stop reading:
 * 		a) The ACD port is closed and
 * 		b) the calculations will also stopped
 *
 *
 * */



#include "ADC_Thread.h"
#include "IC_Thread.h"
#include "stateMachine.h"
#include "hal_data.h"
#include "Display_lib.h"
#include <math.h>
#include "constants.h"

/* Local variables*/
#define K 2.0
float y = 0;
float y0 = 0;

/*Duty cycle variables*/
uint32_t dutyCycle = 0;
uint32_t dutyCycle_0 = 0;
float dutyCycle_ref;
float dutyCycle_Ctrl;
float dutyCycle_E;
uint32_t dutyCycleDisplay;
int firstTime=1;
timer_info_t pwmStatus;
bool enableLed3Process;
uint16_t adcData = 0;
float variable_rpm_rx;
float variable_rpm_real;

//Control Variables
float Ctrl_I;
float Ctrl_I_0=0;
float Ctrl_D;
float dutyCycle_E;
float dutyCycle_E_0=0;
float dutyCycle_out;
float Ki = 5000;
float Kp = 100000;
float Kd = 50000;
float speed_demand;


void input_capture_hal_module_guide_project();
void error_trap(char *, ssp_err_t);

/*
 * Program section
 */
/* ADC_Thread entry function */
void ADC_Thread_entry(void)
{
	/* ports configuration*/
	/*Timer*/
    g_timer9.p_api->open (g_timer9.p_ctrl, g_timer9.p_cfg);
    g_timer9.p_api->start (g_timer9.p_ctrl);
    /*ADC port*/
    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    /*Initialize global variables*/
    y = y0;
    /*Start the state machine with 0*/
    int state=0;


    while(1)
       {

    	/* Get the state from the state machine*/
    	stateMachine(&state);

    	/* Run State*/
    	if(state==myRunning_State)
    	{
    		/* The first time is running it is necessary:
    		 * -open the timer to start reading the PIN
    		 * initialize the dutyCycle to start with the fan stop
    		 * set the flag to skip the initialization next time
    		 */
    		if (firstTime)
    		{
    			dutyCycle=0;
    			g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
    			firstTime=0;
    		}

    		/*Read Inputs*/

    		/* Read the ADC to know the potentiometer position*/
             g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &adcData);

             /* transform the ADC input to % with a range: [0-100]*/
             y = (float)(((1)*adcData*(100.0/255.0) + (K-1)*y0)/K);
             y0 = y;
             dutyCycle = (uint32_t )y;

             /*Calculate the dutyCycle to display*/
             dutyCycleDisplay=100-dutyCycle;


             /*get Actual speed*/
             tx_queue_receive(&ADC_Queue, &variable_rpm_rx, 20);

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
			dutyCycle = 100 - (uint32_t) (((Kp * dutyCycle_E) + Ctrl_I + Ctrl_D));

            /* protect for over speed */
			if (dutyCycle > 100)
			    dutyCycle = 100;




             /*Calculate the new PWM position demand*/
            dutyCycle_out = (PI_Transfer_Function_y1*speed_demand) + PI_Transfer_Function_y2;


            /*Save the current calculations for next reference*/
            dutyCycle_E_0 = dutyCycle_E;
            dutyCycle_E_0 = dutyCycle_E;
            Ctrl_I_0 = Ctrl_I;

            /*Sent to th PWM port the PWM calculated demand*/
             g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, (uint32_t)dutyCycle, TIMER_PWM_UNIT_PERCENT, 1);
             /*Sent the duty cycle to display*/
             setDutyCycle(dutyCycleDisplay);
             if(dutyCycleDisplay<=1)
             {
            	 setSpeed(0);
             }
             else
             setSpeed((ULONG)variable_rpm_rx);
            setSetPoint(1000);
           }
    	else if(state==myStop_State)
    	{
    		/* keep the last set point until control get back*/
    		g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, (uint32_t)dutyCycle, TIMER_PWM_UNIT_PERCENT, 1);
    		/* In case that the run state is set again, initialize and open the drivers*/
    		firstTime=1;
    	}

         tx_thread_sleep(10);
       }
}



