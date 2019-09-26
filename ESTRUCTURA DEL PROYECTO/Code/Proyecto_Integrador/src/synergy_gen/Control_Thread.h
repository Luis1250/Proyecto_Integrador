/* generated thread header file - do not edit */
#ifndef CONTROL_THREAD_H_
#define CONTROL_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus 
extern "C" void Control_Thread_entry(void);
#else 
extern void Control_Thread_entry(void);
#endif
#ifdef __cplusplus
extern "C"
{
#endif
extern TX_QUEUE control_queue;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* CONTROL_THREAD_H_ */
