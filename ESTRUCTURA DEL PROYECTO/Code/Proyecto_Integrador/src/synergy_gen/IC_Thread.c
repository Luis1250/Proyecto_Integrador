/* generated thread source file - do not edit */
#include "IC_Thread.h"

TX_THREAD IC_Thread;
void IC_Thread_create(void);
static void IC_Thread_func(ULONG thread_input);
static uint8_t IC_Thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.IC_Thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer9) && !defined(SSP_SUPPRESS_ISR_GPT2)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 2);
#endif
#endif
static gpt_instance_ctrl_t g_timer9_ctrl;
static const timer_on_gpt_cfg_t g_timer9_extend = { .gtioca = {
		.output_enabled = false, .stop_level = GPT_PIN_LEVEL_HIGH }, .gtiocb = {
		.output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
		.shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer9_cfg = { .mode = TIMER_MODE_PERIODIC, .period =
		100, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50,
		.duty_cycle_unit = TIMER_PWM_UNIT_PERCENT, .channel = 2, .autostart =
				true, .p_callback = NULL, .p_context = &g_timer9, .p_extend =
				&g_timer9_extend, .irq_ipl = (BSP_IRQ_DISABLED), };
/* Instance structure to use this module. */
const timer_instance_t g_timer9 = { .p_ctrl = &g_timer9_ctrl, .p_cfg =
		&g_timer9_cfg, .p_api = &g_timer_on_gpt };
#if !defined(SSP_SUPPRESS_ISR_g_input_capture) && !defined(SSP_SUPPRESS_ISR_GPT9)
SSP_VECTOR_DEFINE_CHAN(gpt_input_capture_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 9);
#endif
#if !defined(SSP_SUPPRESS_ISR_g_input_capture) && !defined(SSP_SUPPRESS_ISR_GPT9)
SSP_VECTOR_DEFINE_CHAN(gpt_input_capture_isr, GPT, CAPTURE_COMPARE_A, 9);
#endif
static gpt_input_capture_instance_ctrl_t g_input_capture_ctrl;
static const gpt_input_capture_extend_t g_input_capture_extend = { .signal =
		GPT_INPUT_CAPTURE_SIGNAL_PIN_GTIOCA, .signal_filter =
		GPT_INPUT_CAPTURE_SIGNAL_FILTER_NONE, .clock_divider =
		GPT_INPUT_CAPTURE_CLOCK_DIVIDER_1, .enable_level =
		INPUT_CAPTURE_SIGNAL_LEVEL_NONE, .enable_filter =
		GPT_INPUT_CAPTURE_SIGNAL_FILTER_NONE, };
static const input_capture_cfg_t g_input_capture_cfg = { .channel = 9, .mode =
		INPUT_CAPTURE_MODE_PERIOD, .edge = INPUT_CAPTURE_SIGNAL_EDGE_RISING,
		.repetition = INPUT_CAPTURE_REPETITION_PERIODIC, .autostart = true,
		.p_callback = input_capture_callback, .p_context = &g_input_capture,
		.p_extend = &g_input_capture_extend, .capture_irq_ipl = (2),
		.overflow_irq_ipl = (2), };
/* Instance structure to use this module. */
const input_capture_instance_t g_input_capture = { .p_ctrl =
		&g_input_capture_ctrl, .p_cfg = &g_input_capture_cfg, .p_api =
		&g_input_capture_on_gpt };
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void IC_Thread_create(void) {
	/* Increment count so we will know the number of ISDE created threads. */
	g_ssp_common_thread_count++;

	/* Initialize each kernel object. */

	UINT err;
	err = tx_thread_create(&IC_Thread, (CHAR *) "IC_Thread", IC_Thread_func,
			(ULONG) NULL, &IC_Thread_stack, 1024, 1, 1, 1, TX_AUTO_START);
	if (TX_SUCCESS != err) {
		tx_startup_err_callback(&IC_Thread, 0);
	}
}

static void IC_Thread_func(ULONG thread_input) {
	/* Not currently using thread_input. */
	SSP_PARAMETER_NOT_USED(thread_input);

	/* Initialize common components */
	tx_startup_common_init();

	/* Initialize each module instance. */

	/* Enter user code for this thread. */
	IC_Thread_entry();
}
