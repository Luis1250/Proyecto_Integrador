/*
 * ADC_Thread_entry.h
 *
 *  Created on: 12/07/2019
 *
 * - 12-jul-2019  Francisco Govea
 *   - Create initial file
 */

#ifndef ADC_THREAD_HANDLER_H_
#define ADC_THREAD_HANDLER_H_

/** Macro that defines default sleep to one second */
#define DAFAULT_THREAD_SLEEP_MS  50

/**
 * Global: adc_value
 *
 * Variable to store value read from ADC.
 */
uint16_t adc_value;

/**
 * Function: Close_ADC
 *
 * This function will close the ADC.
 */
void Close_ADC(const adc_instance_t * adc_instance);

/**
 * Function: Read_ADC
 *
 * This function will read the ADC and will return the value read.
 * @param adc_value Variable where the value read will be stored.
 */
void Read_ADC(const adc_instance_t * adc_instance, uint16_t * adc_val);

/**
 * Function: Send_Readings
 *
 * This function will send to another thread the value read from the ADC.
 * @return Returns 0 if the the sending was successful or another value if failed.
 */
uint16_t Send_Readings(uint16_t value);

/**
 * Function: Start_ADC
 *
 * This function will open the ADC.
 */
void Start_ADC(const adc_instance_t * adc_instance);

#endif /* ADC_THREAD_HANDLER_H_ */
