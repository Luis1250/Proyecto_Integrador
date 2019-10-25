#include "IC_Thread.h"
#include "ADC_Thread.h"
#include <stdio.h>

#ifdef SEMI_HOSTING
#ifdef __GNUC__
extern void initialise_monitor_handles(void);
#endif
#endif

#define CHANNEL_NINE (9U)
#define TIMER_SECOND (1000000000U)
#define TIMER_MILLISECOND (1000000U)
#define TIMER_MICROSECOND (1000U)
#define BIT_32 (0x100000000U)
#define BIT_32_OVERFLOW (0x100000000U)

static void error_trap(char *name, ssp_err_t err);
void input_capture_hal_module_guide_project(void);

input_capture_info_t input_capture_info;
float variable_rpm_tx;
ULONG variable_rpm_ulong;

float rpmAvg[100];
float rmpAvgSum = 0.0;
int rpmAvg_cnt = 0;
int rpmAvg_cnt_div=1;

/*
 * This function prints out the error currently being trapped by the firmware
 */
void error_trap(char *name, ssp_err_t err)
{

#ifdef SEMI_HOSTING
    if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
    {
        printf("%s: err = 0x%x",name, err);
    }
#endif

    if (name!=NULL)
       err++;

    while(1)
    {

    }
}

int init=1;

/**********************************************************************************************************************
 * input capture initialization
 *
 * Initialize GPT input capture and waveform output
 *
 **********************************************************************************************************************/
void input_capture_hal_module_guide_project(void)
{
    ssp_version_t input_capture_version;
    ssp_err_t err;

    #ifdef SEMI_HOSTING
    #ifdef __GNUC__
        if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
            initialise_monitor_handles();
    #endif
    #endif

    /* Initialize GPT Timer Driver */
    err = g_timer9.p_api->open(g_timer9.p_ctrl, g_timer9.p_cfg);
    if (SSP_SUCCESS != err)
    {
        error_trap("g_timer9.p_api->open", err);
    }

    /* Get the version of this API and code */
    err = g_input_capture.p_api->versionGet(&input_capture_version);
    if (SSP_SUCCESS != err)
    {
        error_trap("g_input_capture.p_api->versionGet", err);
    }

    /* Print API version and code version using semi-hosting function */
    #ifdef SEMI_HOSTING
        if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
        {
            printf("API version is: %02d%02d\n",(int16_t)input_capture_version.api_version_major, (int16_t)input_capture_version.api_version_minor);
            printf("Code version is: %02d%02d\n",(int16_t)input_capture_version.code_version_major, (int16_t)input_capture_version.code_version_minor);
        }
    #endif

    /* Initialize Input Capture Driver */
    err = g_input_capture.p_api->open(g_input_capture.p_ctrl, g_input_capture.p_cfg);
    if (SSP_SUCCESS != err)
    {
        error_trap("g_input_capture.p_api->open", err);
    }

    /* Get the status (running or not) of the measurement counter */
    err = g_input_capture.p_api->infoGet(g_input_capture.p_ctrl, &input_capture_info);
    if (SSP_SUCCESS != err)
    {
        error_trap("g_input_capture.p_api->infoGet", err);
    }

    /* Print status of measurement counter using semi-hosting function*/
    #ifdef SEMI_HOSTING
        if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
        {
            if(INPUT_CAPTURE_STATUS_IDLE == input_capture_info.status)
            {
                printf("The input capture timer is idle.\n");
            }
            else
            {
                printf("A capture measurement is in progress.\n");
            }
            if(INPUT_CAPTURE_VARIANT_32_BIT == input_capture_info.variant)
            {
                printf("It is a 32-bit timer.\n\n");
            }
            else
            {
                printf("It is a 16-bit timer.\n\n");
            }
        }
    #endif

    for(int i=0;i<100;i++)
    {
    	rpmAvg[i]=0;
    }

    while(1)
    {
    	tx_thread_sleep(100);
    }
}

/* IC_Thread entry function */
void IC_Thread_entry(void)
{

    if(init)
    {
     input_capture_hal_module_guide_project();
     init=0;
    }

    tx_thread_sleep(100);

}


void input_capture_callback(input_capture_callback_args_t * p_args)
{
	volatile uint32_t g_pclk_freq_hz;

    if(CHANNEL_NINE == p_args->channel)
    {
        switch(p_args->event)
        {
           volatile float g_time_captured;
           volatile uint32_t g_capture_overflow=0;
           volatile float g_rpm;

            case INPUT_CAPTURE_EVENT_MEASUREMENT:

                /*
                * Currently there is a limitation for using API of lastCaptureGet, otherwise captured counter and overflows number can
                * be got from g_input_capture.p_api->lastCaptureGet. Please refer to the documentation for more information.
                */

                /* Get the frequency of PCLKD in Hz*/
                //#g_cgc_on_cgc.systemClockFreqGet(CGC_SYSTEM_CLOCKS_PCLKD, &pclk_freq_hz);
                g_cgc_on_cgc.systemClockFreqGet(CGC_SYSTEM_CLOCKS_PCLKD, (uint32_t*)&g_pclk_freq_hz);

                /* Calculate time value of measurement (ns) */
                //#time_captured = (uint64_t)(((capture_overflow * BIT_32) + (uint64_t)capture_counter) * TIMER_SECOND / pclk_freq_hz);

                g_time_captured = (float)(g_capture_overflow * BIT_32_OVERFLOW);
                g_time_captured += (float)(p_args->counter + 1);
                g_time_captured /= (float)g_pclk_freq_hz;
                g_time_captured *= (float)4;

                g_rpm = (float)(60.0 / (float)(g_time_captured));
                variable_rpm_tx = g_rpm;

                rpmAvg[rpmAvg_cnt++]=variable_rpm_tx;


                /*Initialize the average array*/
                if(rpmAvg_cnt>=5)
                	rpmAvg_cnt=0;


                /*get the sum for the average*/
                rmpAvgSum=0;
                for(int i=0; i<5; i++)
                {
                	if(rpmAvg[i]>0.0)
                	{
                		rmpAvgSum = rmpAvgSum + rpmAvg[i];
                	}
                }

                /*Get the average*/
                variable_rpm_tx = (rmpAvgSum/(float)rpmAvg_cnt_div);
                rpmAvg_cnt_div++;
                if (rpmAvg_cnt_div >=6)
                    rpmAvg_cnt_div=5;


                /*Sent the speed average for control calculations*/
                tx_queue_send(&ADC_Queue,&variable_rpm_tx, TX_NO_WAIT);


                #ifdef SEMI_HOSTING
                    if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
                    {
                        /* Debugger is connected */

                        /* Output current status and value captured */
                        printf("Input capture interrupt occurs.\n");
                        //#printf("The captured timer value from interrupt callback is: %ld\n", capture_counter);
                        //#printf("The overflows counter value from interrupt callback is: %ld\n", (uint32_t)capture_overflow);

                        printf("The pulse counter value from interrupt callback is: %i\n", (int)g_rpm);
                        printf("The overflows counter value from interrupt callback is: %i\n", (int)g_capture_overflow);


                        /* Output time value of measurement */
                        /*#if( time_captured < TIMER_MICROSECOND )
                        {
                            printf("Timer captured is: %ld ns\n", (uint32_t)((float)time_captured + 0.5F));
                        }
                        else if( (TIMER_MICROSECOND <= time_captured) && (time_captured < TIMER_MILLISECOND) )
                        {
                            printf("Timer captured is: %ld us\n", (uint32_t)(((float)time_captured / (float)TIMER_MICROSECOND) + 0.5F));
                        }
                        else if( (TIMER_MILLISECOND <= time_captured) && (time_captured < TIMER_SECOND) )
                        {
                            printf("Timer captured is: %ld ms\n", (uint32_t)(((float)time_captured / (float)TIMER_MILLISECOND) + 0.5F));
                        }
                        else
                        {
                            printf("Time captured is: %ld s\n", (uint32_t)(((float)time_captured / (float)TIMER_SECOND) + 0.5F));
                        }
                        if(INPUT_CAPTURE_STATUS_IDLE == input_capture_info.status)
                        {
                            printf("The input capture timer is idle.\n\n");
                        }
                        else
                        {
                            printf("A capture measurement is in progress.\n\n");
                        }#*/
                    }
                #endif


                g_time_captured = 0;
                g_capture_overflow = 0;
                break;

            case INPUT_CAPTURE_EVENT_OVERFLOW:


                #ifdef SEMI_HOSTING
                    if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
                    {
                        /* Output current status*/
                        printf("Overflow interrupt occurs.\n");
                        if(INPUT_CAPTURE_STATUS_IDLE == input_capture_info.status)
                        {
                            printf("The input capture timer is idle.\n");
                        }
                        else
                        {
                            printf("A capture measurement is in progress.\n\n");
                        }
                    }
                #endif

                g_capture_overflow++;
                break;
            default:
                break;
        }
    }
}
