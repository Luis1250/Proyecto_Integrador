/* generated thread header file - do not edit */
#ifndef ADC_THREAD_H_
#define ADC_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void ADC_Thread_entry(void);
#else
extern void ADC_Thread_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1;
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t g_adc0;
#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif
extern TX_QUEUE ADC_Queue;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* ADC_THREAD_H_ */
