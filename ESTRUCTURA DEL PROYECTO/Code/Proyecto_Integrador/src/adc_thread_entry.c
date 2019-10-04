/** File: adc_thread_handler.h
 *
 *
 *  Created on: 01/10/2019
 *      Author: Team 2
 */

#include <adc_thread.h>
#include "adc_thread_handler.h"

/**
 * Refer to adc_thread_handler.h for further information.
 */
uint16_t ADC_Value = 0;

/**
 * adc_thread_entry function that will execute periodically
 */
void adc_thread_entry(void)
{
    Start_ADC(&adc_obj);

    while (true)
    {
        Read_ADC(&adc_obj, &ADC_Value);
        Send_Readings(ADC_Value);
        tx_thread_sleep(DAFAULT_THREAD_SLEEP_MS);
    }
}
