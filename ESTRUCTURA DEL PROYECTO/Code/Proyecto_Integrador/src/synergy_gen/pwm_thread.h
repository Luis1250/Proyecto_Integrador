/* generated thread header file - do not edit */
#ifndef PWM_THREAD_H_
#define PWM_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void pwm_thread_entry(void);
#else
extern void pwm_thread_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t pwm_timer;
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
extern TX_QUEUE pwm_queue;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* PWM_THREAD_H_ */
