/* generated thread source file - do not edit */
#include "ADC_Thread.h"

TX_THREAD ADC_Thread;
void ADC_Thread_create(void);
static void ADC_Thread_func(ULONG thread_input);
static uint8_t ADC_Thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.ADC_Thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer1) && !defined(SSP_SUPPRESS_ISR_GPT1)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 1);
#endif
#endif
static gpt_instance_ctrl_t g_timer1_ctrl;
static const timer_on_gpt_cfg_t g_timer1_extend = { .gtioca = {
		.output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW }, .gtiocb = {
		.output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
		.shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer1_cfg = { .mode = TIMER_MODE_PWM, .period = 100,
		.unit = TIMER_UNIT_FREQUENCY_HZ, .duty_cycle = 50, .duty_cycle_unit =
				TIMER_PWM_UNIT_PERCENT, .channel = 1, .autostart = true,
		.p_callback = NULL, .p_context = &g_timer1,
		.p_extend = &g_timer1_extend, .irq_ipl = (BSP_IRQ_DISABLED), };
/* Instance structure to use this module. */
const timer_instance_t g_timer1 = { .p_ctrl = &g_timer1_ctrl, .p_cfg =
		&g_timer1_cfg, .p_api = &g_timer_on_gpt };
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_adc0) && !defined(SSP_SUPPRESS_ISR_ADC0)
SSP_VECTOR_DEFINE_CHAN(adc_scan_end_isr, ADC, SCAN_END, 0);
#endif
#endif
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_adc0) && !defined(SSP_SUPPRESS_ISR_ADC0)
SSP_VECTOR_DEFINE_CHAN(adc_scan_end_b_isr, ADC, SCAN_END_B, 0);
#endif
#endif
adc_instance_ctrl_t g_adc0_ctrl;
const adc_cfg_t g_adc0_cfg = { .unit = 0, .mode = ADC_MODE_CONTINUOUS_SCAN,
		.resolution = ADC_RESOLUTION_8_BIT, .alignment = ADC_ALIGNMENT_RIGHT,
		.add_average_count = ADC_ADD_OFF, .clearing = ADC_CLEAR_AFTER_READ_ON,
		.trigger = ADC_TRIGGER_SOFTWARE,
		.trigger_group_b = ADC_TRIGGER_SYNC_ELC, .p_callback = NULL,
		.p_context = &g_adc0, .scan_end_ipl = (BSP_IRQ_DISABLED),
		.scan_end_b_ipl = (BSP_IRQ_DISABLED), .calib_adc_skip = false, };
const adc_channel_cfg_t g_adc0_channel_cfg = { .scan_mask = (uint32_t)(
		((uint64_t) ADC_MASK_CHANNEL_0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | (0)),
/** Group B channel mask is right shifted by 32 at the end to form the proper mask */
.scan_mask_group_b = (uint32_t)(
		(((uint64_t) ADC_MASK_CHANNEL_0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | (0)) >> 32),
		.priority_group_a = ADC_GROUP_A_PRIORITY_OFF, .add_mask = (uint32_t)(
				(0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)
						| (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)
						| (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)
						| (0)), .sample_hold_mask = (uint32_t)((0) | (0) | (0)),
		.sample_hold_states = 24, };
/* Instance structure to use this module. */
const adc_instance_t g_adc0 = { .p_ctrl = &g_adc0_ctrl, .p_cfg = &g_adc0_cfg,
		.p_channel_cfg = &g_adc0_channel_cfg, .p_api = &g_adc_on_adc };
TX_QUEUE ADC_Queue;
static uint8_t queue_memory_ADC_Queue[20];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void ADC_Thread_create(void) {
	/* Increment count so we will know the number of ISDE created threads. */
	g_ssp_common_thread_count++;

	/* Initialize each kernel object. */
	UINT err_ADC_Queue;
	err_ADC_Queue = tx_queue_create(&ADC_Queue, (CHAR *) "ADC_Queue", 1,
			&queue_memory_ADC_Queue, sizeof(queue_memory_ADC_Queue));
	if (TX_SUCCESS != err_ADC_Queue) {
		tx_startup_err_callback(&ADC_Queue, 0);
	}

	UINT err;
	err = tx_thread_create(&ADC_Thread, (CHAR *) "ADC_Thread", ADC_Thread_func,
			(ULONG) NULL, &ADC_Thread_stack, 1024, 1, 1, 1, TX_AUTO_START);
	if (TX_SUCCESS != err) {
		tx_startup_err_callback(&ADC_Thread, 0);
	}
}

static void ADC_Thread_func(ULONG thread_input) {
	/* Not currently using thread_input. */
	SSP_PARAMETER_NOT_USED(thread_input);

	/* Initialize common components */
	tx_startup_common_init();

	/* Initialize each module instance. */

	/* Enter user code for this thread. */
	ADC_Thread_entry();
}
