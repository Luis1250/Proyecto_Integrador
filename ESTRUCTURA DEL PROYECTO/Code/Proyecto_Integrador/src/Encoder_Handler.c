/*
 * Encoder_Handler.c
 *
 *  Created on: 25/07/2019
 *
 * - 25-jul-2019  Francisco Govea
 *  - Add interruption for Encoder
 */

#include "Encoder_Thread.h"
#include "Encoder_Handler.h"

/**
 * Refer to Encoder_Handler.h for further information.
 */
encoder_t encoder_data;

/**
 * Refer to Encoder_Handler.h for further information.
 */
uint16_t Convert_Ms_To_Min(uint16_t revolutions_in_ms)
{
    return (uint16_t)(revolutions_in_ms * TO_RPMS);
}

/**
 * Refer to Encoder_Handler.h for further information.
 */
void Send_RPM(uint16_t revs)
{
    tx_queue_send(&encoder_queue, &revs, TX_NO_WAIT);
    encoder_data.revolution = 0;
}

/**
 * Refer to Encoder_Handler.h for further information.
 */
void Initialize_Interrupt(const external_irq_instance_t * ext_int)
{
    if(NULL != ext_int)
    {
        ext_int->p_api->open(encoder_interrupt.p_ctrl, encoder_interrupt.p_cfg);
    }
}
