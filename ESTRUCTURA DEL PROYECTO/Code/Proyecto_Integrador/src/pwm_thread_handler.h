/*
 * PWM_Thread_entry.h
 *
 *  Created on: 12/07/2019
 *
 * - 12-jul-2019  Francisco Govea
 *   - Create initial file
 *
 * - 22-jul-2019  Francisco Govea
 *   - Add improvements to PWM
 *
 * - 25-jul-2019  Francisco Govea
 *   - Add interruption for Encoder
 *
 * - 07-aug-2019  Francisco Govea
 *   - Add Function to send duty cycle
 */

#ifndef PWM_THREAD_HANDLER_H_
#define PWM_THREAD_HANDLER_H_

/****************************************************************************
 * Macros and constants
 ****************************************************************************/

/**
 * Defines default duty cycle for PWM
 */
#define DEFAULT_DUTY_CYCLE   100

/**
 *  Defines the default pin to be updated.
 */
#define DEFAULT_PIN          1

/**
 * Defines the max value that can be read by the 10 bits ADC.
 */
#define MAX_ADC_VALUE        1023

/**
 * Defines the max percentage that the Duty cycle can have
 */
#define MAX_PERCENT          100

/**
 * Defines a time for the thread to go to sleep.
 */
#define DEFAULT_WAIT_MS      1

/****************************************************************************
 * Functions
 ****************************************************************************/

/**
 * Function: Generate_Signal
 *
 * Function that will generate the signal to be control the motor.
 *
 * @param pwm_instance Instance of the object generated of the timer.
 * @param pwm_value Variable read from the ADC which will modify the signal.
 * @return Returns 0 if the signal was successfully generated or another number if it failed.
 */
uint16_t Generate_Signal(const timer_instance_t * pwm_instance);

/**
 * Function: Initialize_PWM_Timer
 *
 * Function to start the timer for the PWM signal.
 * @param pwm_instance Instance of the object generated of the timer.
 */
void Initialize_PWM_Timer(const timer_instance_t * pwm_instance);

/**
 * Function:
 *
 * Function to stop the timer that generates the PWM signal.
 * @param pwm_instance Instance of the object generated of the timer.
 */
void Stop_Timer(const timer_instance_t * pwm_instance);

/**
 * Function: Receive_Message
 *
 * Function that will handle the messages received from other threads.
 */
void Receive_Message(void);

/**
 * Function: Parse_PWM_Data
 *
 * Parses the received data into a duty cycle value.
 *
 * @param value_read Variable that will contain the ADC value read.
 * @return Returns the value read converted into a duty cycle percentage.
 */
uint16_t Parse_PWM_Data(uint16_t value_read);

/**
 * Function: Send_Duty_Cycle
 *
 * This function sends the duty cycle value to another thread.
 */
void Send_Duty_Cycle(void);

/****************************************************************************
 * Variables
 ****************************************************************************/

/**Variable to store the value read from incoming messages*/
uint16_t readings;
/**Variable to store the current duty cycle */
uint16_t duty_cycle;

#endif /* PWM_THREAD_HANDLER_H_ */
