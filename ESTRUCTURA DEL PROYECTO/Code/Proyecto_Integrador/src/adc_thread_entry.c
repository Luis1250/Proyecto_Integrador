
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
#include "constants.h"
#include "getSpeedRef.h"
#include <math.h>


/* ADC_Thread entry function */
void ADC_Thread_entry(void)
{

	/*Local variables for this function/thread*/
	/*ADC variables*/
	float ADC_InputPercentage;
	float ADC_InputPercentage_prev = 0;
	uint16_t ADC_Input = 0;

	/*Duty cycle variables*/
	int dutyCycle = 0;
	double speed_ref;
	double speed_error;
	int dutyCycleToDisplay;

	/*Control Variables*/
	double Ctrl_Integrator;
	double Ctrl_Integrator_prev=0;
	double Ctrl_Derivate;
	double speed_prev=0;
	double dutyCycle_dmd;
	double speedDemand;

	/* state machine variables*/
	int firstTime=1;
    /*Start local state with initialization (0)*/
    int state=0;


	/*Input variables from other threads*/
	float variable_rpm_rx;


	double y1,y2,y3,y4,y5,y6,y7;


	/*
	 * Program section
	 */

	/* ports configuration*/
    g_timer9.p_api->open (g_timer9.p_ctrl, g_timer9.p_cfg);
    g_timer9.p_api->start (g_timer9.p_ctrl);

    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);


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
             g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &ADC_Input);
             /*get Actual speed*/
             tx_queue_receive(&ADC_Queue, &variable_rpm_rx, 20);

             /* transform the ADC input to % with a range: [0-100]*/
             ADC_InputPercentage = (float)(((1)*ADC_Input*(100.0/255.0) + ( PI_ADC_K-1)*ADC_InputPercentage_prev)/ PI_ADC_K );
             ADC_InputPercentage_prev = ADC_InputPercentage;
             dutyCycle = (int) (ADC_InputPercentage + 0.5);

             /*Calculate the dutyCycle to display*/
             dutyCycleToDisplay=100-dutyCycle;

             /*Calculate the speed reference using the transfer function*/
             speed_ref = getSpeedRef(dutyCycleToDisplay);

             /* get the Error */
             speed_error = speed_ref - variable_rpm_rx;
             /* eliminate the signal */
             speed_error = speed_error * speed_error;
             speed_error = sqrt(speed_error);

            /*get Integral part */
            Ctrl_Integrator = PI_Ctrl_Ki *  speed_error + Ctrl_Integrator_prev;

            /* get derivative part */
            Ctrl_Derivate = PI_Ctrl_Kd * (speed_error - speed_prev);

            /* Calculate the new speed demand */
            speedDemand = (PI_Ctrl_Kp * speed_error) + Ctrl_Integrator + Ctrl_Derivate;

            y1 = 5.515E-18;
            y2 = -6.173E-14;
            y3 = 2.659E-10;
            y4 = -5.377E-7;
            y5 = 0.0004834;
            y6 = -0.1;
            y7= 0.6957;


            dutyCycle_dmd = (y1*pow(speedDemand,6)) + (y2*pow(speedDemand,5)) + (y3*pow(speedDemand,4)) + (y4*pow(speedDemand,3)) + (y5*pow(speedDemand,2)) + (y6*speedDemand) + y7;


            /*keep the error to compare with the next error.*/
            speed_prev = speed_error;
            /*keep the integral part to compare with the next integral part.*/
            Ctrl_Integrator_prev = Ctrl_Integrator;


             g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, (uint32_t)dutyCycle_dmd, TIMER_PWM_UNIT_PERCENT, 1);

             /*Set the duty Cycle to display*/
             setDutyCycle(dutyCycleToDisplay);

             /*set speed to display
              * filter low speeds to 0 since the motor can't rotate
             */
             if(dutyCycleToDisplay<=1)
             {
            	 setSpeed(0);
             }
             else
             setSpeed((int) (variable_rpm_rx + 0.5));
           }
    	else if(state==myStop_State)
    	{

    		/* keep the last set point*/
    		g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, (uint32_t)dutyCycle_dmd, TIMER_PWM_UNIT_PERCENT, 1);
    		/* In case that the run state is set again, initialize and open the drivers*/
    		firstTime=1;
    	}

         tx_thread_sleep(5);
       }
}



