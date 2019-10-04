/*
 * ADC_Thread_entry.h
 *
 *
 *  Created on: 01/10/2019
 *      Author: Team 2
 */

#include <ADC_Thread.h>
#include "adc_thread_handler.h"

/**
 * Refer to ADC_Thread_entry.h for further information.
 */
void Start_ADC(const adc_instance_t * adc_instance)
{
    if(NULL != adc_instance)
    {
        adc_instance->p_api->open(adc_instance->p_ctrl, adc_instance->p_cfg);
        adc_instance->p_api->scanCfg(adc_instance->p_ctrl, adc_instance->p_channel_cfg);
        adc_instance->p_api->scanStart(adc_instance->p_ctrl);
    }
}

/**
 * Refer to ADC_Thread_entry.h for further information.
 */
void Close_ADC(const adc_instance_t * adc_instance)
{
    if(NULL != adc_instance)
    {
        adc_instance->p_api->close(adc_instance->p_ctrl);
    }
}

/**
 * Refer to ADC_Thread_entry.h for further information.
 */
uint16_t Send_Readings(uint16_t value)
{
    return (uint16_t)tx_queue_send(&adc_queue, &value, TX_NO_WAIT);
}

/**
 * Refer to ADC_Thread_entry.h for further information.
 */
void Read_ADC(const adc_instance_t * adc_instance, uint16_t * adc_val)
{
    if(NULL != adc_val && NULL != adc_instance)
    {
        adc_instance->p_api->read(adc_instance->p_ctrl, ADC_REG_CHANNEL_0, adc_val);
    }
}
