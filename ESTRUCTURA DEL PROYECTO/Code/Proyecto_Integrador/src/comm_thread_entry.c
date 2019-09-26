/**
 * comm_thread_entry.c
 *
 *  Created on: 26/07/2019
 *
 * - 26-jul-2019  Francisco Govea
 *  - Add communication layer
 *
 * - 07-aug-2019  Francisco Govea
 *  - Implement Receive Communication
 */
#include "ADC_Thread.h"
#include "comm_thread.h"
#include "Comm_Handler.h"
#include "Encoder_Thread.h"
#include "PWM_Thread.h"

/**Refer to Comm_Handler.h for further information*/
extern Data_To_Store_T data_stored;

/**Refer to Comm_Handler.h for further information*/
extern uint16_t data_received;

/* Comm_Thread entry function */
void comm_thread_entry(void)
{
    Initialize_Refresh_Timer(&refresh_timer);
    Initialize_Struct(&data_stored);

    while (true)
    {
        Start_Refresh_Timer(&refresh_timer);
        On_Message(&adc_queue);
        data_stored.set_point = data_received;
        On_Message(&pwm_queue);
        data_stored.duty_cycle = data_received;
        On_Message(&encoder_queue);
        data_stored.rpm = data_received;

        tx_thread_sleep (1);
    }
}

/**
 * Function that will process the interruption of the timer to refresh the data.
 */
void process_Refresh_Information(timer_callback_args_t *p_args)
{
    (void)p_args;
    Send_Data(data_stored);
}
