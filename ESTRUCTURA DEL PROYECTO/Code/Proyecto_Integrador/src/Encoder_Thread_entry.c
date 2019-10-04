/*
 * Encoder_Thread_entry.c
 *
 *
 *  Created on: 01/10/2019
 *      Author: Team 2
 */

#include "Encoder_Thread.h"
#include "Encoder_Handler.h"

extern encoder_t encoder_data;

/* Encoder_Thread_entry function that */
void Encoder_Thread_entry(void)
{
    Initialize_Interrupt(&encoder_interrupt);

    while (true)
    {
        tx_thread_sleep(DEF_THREAD_SLEEP_MS);
        encoder_data.rpm = Convert_Ms_To_Min(encoder_data.revolution);
        Send_RPM(encoder_data.rpm);
    }
}

/**
 * Function that will process the interruption of the encoder.
 */
void process_Encoder_Signal_Received(external_irq_callback_args_t *p_args)
{
    (void)p_args;
    encoder_data.encoder_pulse++;

    if(PULSES_PER_REVOLUTION == encoder_data.encoder_pulse)
    {
        encoder_data.encoder_pulse = 0;
        encoder_data.revolution++;
    }
}
