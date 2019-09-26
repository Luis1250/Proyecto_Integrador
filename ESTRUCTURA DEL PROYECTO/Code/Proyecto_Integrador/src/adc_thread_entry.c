/** File: adc_thread_handler.h
 *
 *  Created on: 12/07/2019
 *
 * - 12-jul-2019  Francisco Govea
 *   - Create initial file.
 *
 */

#include <adc_thread.h>
#include "adc_thread_handler.h"

/**
 * Refer to adc_thread_handler.h for further information.
 */
uint16_t adc_value = 0;

/**
 * adc_thread_entry function that will execute periodically
 */
void adc_thread_entry(void)
{
    Start_ADC(&adc_obj);

    while (true)
    {
        Read_ADC(&adc_obj, &adc_value);
        Send_Readings(adc_value);
        tx_thread_sleep(DAFAULT_THREAD_SLEEP_MS);
    }
}
