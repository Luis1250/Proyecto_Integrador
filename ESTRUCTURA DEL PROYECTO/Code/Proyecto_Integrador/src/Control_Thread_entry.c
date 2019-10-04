/*
 * Control_Thread_entry.c
 *
 *  Created on: 01/10/2019
 *      Author: Team 2
 */

#include "Control_Thread.h"
#include "Control_Handler.h"

/**
 * Control_Thread entry function that will execute periodically
 */
void Control_Thread_entry(void)
{
    uint16_t set_point = 0;
    uint16_t encoder_rpm = 0;
    uint16_t control_signal = 0;

    while (true)
    {
        set_point = Receive_Message_from_ADC();
        encoder_rpm = Receive_Message_from_Encoder();
        set_point = Parse_ADC_to_RPM(set_point);
        control_signal = Calculate_Correct_Signal(set_point, encoder_rpm);
        Send_Results(control_signal);
        tx_thread_sleep (1);
    }
}
