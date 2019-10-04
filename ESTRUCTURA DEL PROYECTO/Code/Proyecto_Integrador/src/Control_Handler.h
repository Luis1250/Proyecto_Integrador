/*
 * Control_Handler.h
 *
 *
 *  Created on: 01/10/2019
 *      Author: Team 2
 */

#include "constants.h"

#ifndef CONTROL_HANDLER_H_
#define CONTROL_HANDLER_H_
/****************************************************************************
 * Macros and constants
 ****************************************************************************/

/**
 *
 */
#define MAX_ADC_VALUE   1023

/**
 *
 */
#define MAX_REVOLUTIONS_PER_MINUTE   3036


/**
 * Struct: Control_Variables_T
 *
 * Struct that contains all the variables needed for the control PID.
 */
typedef struct
{
    int16_t  last_error;               /***/
    uint16_t  error;                    /***/
    uint16_t  actual;                   /***/
    uint16_t  set_point;                /***/
    uint16_t  control_signal;           /***/
    uint16_t  integral;                 /***/
    uint16_t  derivative;               /***/

}Control_Variables_T;

/****************************************************************************
 * Functions
 ****************************************************************************/

/**
 * Function: Calculate_Correct_Signal
 *
 * Function that will make all calculus necessary for the control signal.
 *
 * @return Duty cycle corrected.
 */
uint16_t Calculate_Correct_Signal(uint16_t set_point, uint16_t real_value);

/**
 * Function: Send_Results
 *
 * Function that will send the results form the calculus to another thread.
 */
void Send_Results(uint16_t results);

/**
 * Function: Receive_Message_from_ADC
 *
 * Function that will process the incoming message from the ADC thread.
 */
uint16_t Receive_Message_from_ADC();

/**
 * Function: Receive_Message_from_Encoder
 *
 * Function that will process the incoming message from the Encoder thread.
 * @return
 */
uint16_t Receive_Message_from_Encoder();

/**
 * Function: Parse_ADC_to_RPM
 *
 * Function that will convert the data received form the ad to RPM.
 *
 * @return Data parsed into RPM
 */
uint16_t Parse_ADC_to_RPM(uint16_t adc_value);

#endif /* CONTROL_HANDLER_H_ */
