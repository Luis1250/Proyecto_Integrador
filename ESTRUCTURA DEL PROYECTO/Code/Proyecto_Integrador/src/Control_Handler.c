/*
 * Control_Handler.c
 *
 *  Created on: 27/07/2019
 *
 * - 27-jul-2019   Francisco Govea
 *  - Add Control Module
 */
#include "ADC_Thread.h"
#include "Encoder_Thread.h"
#include "Control_Thread.h"
#include "Control_Handler.h"

/** Refer to Control_Handler.h for further information.h */
Control_Variables_T control;

/**
 * Refer to Control_Handler.h for further information.
 */
uint16_t Calculate_Correct_Signal(uint16_t st_pnt, uint16_t real_value)
{
    (void)st_pnt;
    (void)real_value;
    /**
    control.set_point  = st_pnt;
    control.actual     = real_value;
    control.error      = st_pnt - real_value;
    control.integral   = control.integral + control.error;
    control.derivative = control.error - control.last_error;
    control.last_error = control.error;
    control.control_signal = (KP_CONSTANT * control.error) + (KI_CONSTANT * control.integral) + (KD_CONSTANT * control.derivative);
    return control.control_signal;
    */
    return 1;
}

/**
 * Refer to Control_Handler.h for further information.
 */
void Send_Results(uint16_t results)
{
    tx_queue_send(&control_queue, &results, TX_NO_WAIT);
}

/**
 * Refer to Control_Handler.h for further information.
 */
uint16_t Receive_Message_from_ADC()
{
    uint16_t adc_value = 0;

    tx_queue_receive(&adc_queue, &adc_value, TX_NO_WAIT);
    return adc_value;
}

/**
 * Refer to Control_Handler.h for further information.
 */
uint16_t Receive_Message_from_Encoder()
{
    uint16_t rpm_value = 0;

    tx_queue_receive(&encoder_queue, &rpm_value, TX_NO_WAIT);
    return rpm_value;
}

/**
 * Refer to Control_Handler.h for further information.
 */
uint16_t Parse_ADC_to_RPM(uint16_t adc_value)
{
    return (uint16_t)((adc_value * MAX_REVOLUTIONS_PER_MINUTE) / MAX_ADC_VALUE);
}
