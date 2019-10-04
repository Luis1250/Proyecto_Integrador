/* generated thread source file - do not edit */
#include "comm_thread.h"

TX_THREAD comm_thread;
void comm_thread_create(void);
static void comm_thread_func(ULONG thread_input);
static uint8_t comm_thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.comm_thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (6) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_refresh_timer) && !defined(SSP_SUPPRESS_ISR_GPT0)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 0);
#endif
#endif
static gpt_instance_ctrl_t refresh_timer_ctrl;
static const timer_on_gpt_cfg_t refresh_timer_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t refresh_timer_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 1000, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 0, .autostart = true, .p_callback = process_Refresh_Information, .p_context = &refresh_timer, .p_extend =
          &refresh_timer_extend,
  .irq_ipl = (6), };
/* Instance structure to use this module. */
const timer_instance_t refresh_timer =
{ .p_ctrl = &refresh_timer_ctrl, .p_cfg = &refresh_timer_cfg, .p_api = &g_timer_on_gpt };
TX_QUEUE comm_queue;
static uint8_t queue_memory_comm_queue[48];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void comm_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_comm_queue;
    err_comm_queue = tx_queue_create (&comm_queue, (CHAR *) "COMM_QUEUE", 3, &queue_memory_comm_queue,
                                      sizeof(queue_memory_comm_queue));
    if (TX_SUCCESS != err_comm_queue)
    {
        tx_startup_err_callback (&comm_queue, 0);
    }

    UINT err;
    err = tx_thread_create (&comm_thread, (CHAR *) "Comm_Thread", comm_thread_func, (ULONG) NULL, &comm_thread_stack,
                            1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&comm_thread, 0);
    }
}

static void comm_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    comm_thread_entry ();
}
