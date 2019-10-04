/*
 * Comm_Handler.c
 *
 *
 *  Created on: 01/10/2019
 *      Author: Team 2
 */
#include "Comm_Thread.h"
#include "Comm_Handler.h"

/**Refer to Comm_Handler.h for further information*/
uint16_t data_received = 0;

/**Refer to Comm_Handler.h for further information*/
Data_To_Store_T data_stored;

/**
 * Refer to Comm_Handler.h for further information.
 */
void Start_Refresh_Timer(const timer_instance_t * timer_instance)
{
    if(NULL != timer_instance)
    {
        timer_instance->p_api->start(timer_instance->p_ctrl);
    }
}

/**
 * Refer to Comm_Handler.h for further information.
 */
void Initialize_Refresh_Timer(const timer_instance_t * timer_instance)
{
    if(NULL != timer_instance)
    {
        timer_instance->p_api->open(timer_instance->p_ctrl, timer_instance->p_cfg);
    }
}

/**
 * Refer to Comm_Handler.h for further information.
 */
void On_Message(TX_QUEUE* queue)
{
    if(NULL != queue)
    {
        tx_queue_receive(queue, &data_received, TX_NO_WAIT);
    }
}

/**
 * Refer to Comm_Handler.h for further information.
 */
void Initialize_Struct(Data_To_Store_T * data_struct)
{
    if(NULL != data_struct)
    {
        data_struct->duty_cycle = DEFAULT_VALUE;
        data_struct->rpm = DEFAULT_VALUE;
        data_struct->set_point = DEFAULT_VALUE;
    }
}

/**
 * Refer to Comm_Handler.h for further information.
 */
void Send_Data(Data_To_Store_T temp_struct)
{
    tx_queue_send(&comm_queue, &temp_struct, TX_NO_WAIT);
}
