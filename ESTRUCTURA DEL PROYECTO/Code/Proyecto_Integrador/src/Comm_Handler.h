/*
 * Comm_Handler.h
 *
 *
 *  Created on: 01/10/2019
 *      Author: Team 2
 */

#ifndef COMM_HANDLER_H_
#define COMM_HANDLER_H_

/****************************************************************************
 * Macros and constants
 ****************************************************************************/
/**
 * Defines the default value for all parameters in structure.
 */
#define DEFAULT_VALUE   0

/****************************************************************************
 * Structures
 ****************************************************************************/

/** Struct: Data_To_Store
 * Struct to store all data received from the other threads.
 */
typedef struct data_to_store
{
    uint16_t rpm;             /**Variable to store the revolutions per minute received*/
    uint16_t set_point;       /**Variable to store the set point received*/
    uint16_t duty_cycle;      /**Variable to store the duty cycle received*/

}Data_To_Store_T;

/****************************************************************************
 * Functions
 ****************************************************************************/

/**
 * Function: Start_Refresh_Timer
 *
 * Function that will start the timer of refresh.
 *
 * @param timer_instance Instance of the timer to start.
 */
void Start_Refresh_Timer(const timer_instance_t * timer_instance);

/**
 * Function: Initialize_Refresh_Timer
 *
 * Function that will initialize the timer for refresh.
 *
 * @param timer_instance Instance of the timer to initialize.
 */
void Initialize_Refresh_Timer(const timer_instance_t * timer_instance);

/**
 * Function: On_Message
 *
 * Funtion that will process the message received from another thread.
 *
 * @param queue  Queue of the sender thread.
 */
void On_Message(TX_QUEUE * queue);

/**
 * Function: Initialize_Struct
 *
 * Function that will initialize all values from the structure to their defaults values.
 *
 * @param data_struct  Structure to initialize
 */
void Initialize_Struct(Data_To_Store_T * data_struct);

/**
 * Function: Send_Data
 *
 * Function that will send all data to display thread.
 */
void Send_Data(Data_To_Store_T temp_struct);

/****************************************************************************
 * Variables
 ****************************************************************************/

/**Variable to store the data received from another thread*/
uint16_t data_received;

#endif /* COMM_HANDLER_H_ */
