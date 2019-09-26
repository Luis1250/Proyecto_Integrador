/* generated thread source file - do not edit */
#include "Encoder_Thread.h"

TX_THREAD Encoder_Thread;
void Encoder_Thread_create(void);
static void Encoder_Thread_func(ULONG thread_input);
static uint8_t Encoder_Thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.Encoder_Thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (3) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_encoder_interrupt) && !defined(SSP_SUPPRESS_ISR_ICU0)
SSP_VECTOR_DEFINE( icu_irq_isr, ICU, IRQ0);
#endif
#endif
static icu_instance_ctrl_t encoder_interrupt_ctrl;
static const external_irq_cfg_t encoder_interrupt_cfg =
{ .channel = 0,
  .trigger = EXTERNAL_IRQ_TRIG_RISING,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = process_Encoder_Signal_Received,
  .p_context = &encoder_interrupt,
  .p_extend = NULL,
  .irq_ipl = (3), };
/* Instance structure to use this module. */
const external_irq_instance_t encoder_interrupt =
{ .p_ctrl = &encoder_interrupt_ctrl, .p_cfg = &encoder_interrupt_cfg, .p_api = &g_external_irq_on_icu };
TX_QUEUE encoder_queue;
static uint8_t queue_memory_encoder_queue[20];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void Encoder_Thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_encoder_queue;
    err_encoder_queue = tx_queue_create (&encoder_queue, (CHAR *) "ENCODER_QUEUE", 1, &queue_memory_encoder_queue,
                                         sizeof(queue_memory_encoder_queue));
    if (TX_SUCCESS != err_encoder_queue)
    {
        tx_startup_err_callback (&encoder_queue, 0);
    }

    UINT err;
    err = tx_thread_create (&Encoder_Thread, (CHAR *) "Encoder_Thread", Encoder_Thread_func, (ULONG) NULL,
                            &Encoder_Thread_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&Encoder_Thread, 0);
    }
}

static void Encoder_Thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    Encoder_Thread_entry ();
}
