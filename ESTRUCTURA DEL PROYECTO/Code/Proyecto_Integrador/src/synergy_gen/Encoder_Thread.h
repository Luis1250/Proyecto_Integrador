/* generated thread header file - do not edit */
#ifndef ENCODER_THREAD_H_
#define ENCODER_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus 
extern "C" void Encoder_Thread_entry(void);
#else 
extern void Encoder_Thread_entry(void);
#endif
#include "r_icu.h"
#include "r_external_irq_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t encoder_interrupt;
#ifndef process_Encoder_Signal_Received
void process_Encoder_Signal_Received(external_irq_callback_args_t *p_args);
#endif
extern TX_QUEUE encoder_queue;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* ENCODER_THREAD_H_ */
