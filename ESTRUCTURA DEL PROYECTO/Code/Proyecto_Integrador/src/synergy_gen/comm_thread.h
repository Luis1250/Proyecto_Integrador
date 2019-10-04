/* generated thread header file - do not edit */
#ifndef COMM_THREAD_H_
#define COMM_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void comm_thread_entry(void);
#else
extern void comm_thread_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t refresh_timer;
#ifndef process_Refresh_Information
void process_Refresh_Information(timer_callback_args_t *p_args);
#endif
extern TX_QUEUE comm_queue;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* COMM_THREAD_H_ */
