/*
 * Encoder_Handler.h
 *
 *  Created on: 25/07/2019
 *
 * - 25-jul-2019  Francisco Govea
 *  - Add interruption for Encoder
 */

#ifndef ENCODER_HANDLER_H_
#define ENCODER_HANDLER_H_

#include <stdint.h>
#include "Encoder_Thread.h"

/****************************************************************************
 * Macros and constants
 ****************************************************************************/

/**
 * Defines the number of pulses received by the encoder on each revolution.
 */
#define PULSES_PER_REVOLUTION   4

/**
 * Defines the number to convert from 200 milliseconds to a minute.
 */
#define TO_RPMS   12

/**
 * Defines the Default time for the thread to go to sleep
 */
#define DEF_THREAD_SLEEP_MS  500

/****************************************************************************
 * Variables
 ****************************************************************************/

/**
 * Struct: encoder_t
 *
 * Struct that contains all data related to the encoder handling.
 */
typedef struct Encoder
{
    uint8_t encoder_pulse; /**Variable that stores the number of pulses received */
    uint16_t revolution;   /**Variable that stores the revolutions per minute*/
    uint16_t rpm;          /**Variable that stores the revolutions per minute*/
}encoder_t;

/****************************************************************************
 * Functions
 ****************************************************************************/

/**
 * Function: Convert_Ms_To_Min
 *
 * Function that will convert the revolutions read in 200 ms to a minute.
 *
 * @param revolutions variable read every 200 milliseconds.
 * @return Revolutions per minute.
 */
uint16_t Convert_Ms_To_Min(uint16_t revolutions);

/**
 * Function: Send_RPM
 *
 * Sends the RPM value to another thread.
 */
void Send_RPM(uint16_t revs);


/**
 * Function: Initialize_Interrupt
 *
 * Function that will initialize an interruption instance.
 *
 * @param ext_int Instance of the interruption.
 */
void Initialize_Interrupt(const external_irq_instance_t * ext_int);

#endif /* ENCODER_HANDLER_H_ */
