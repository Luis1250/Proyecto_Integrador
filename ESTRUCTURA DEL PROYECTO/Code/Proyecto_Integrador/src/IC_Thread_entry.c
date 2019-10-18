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

static void error_trap(char *name, ssp_err_t err);
void input_capture_hal_module_guide_project(void);

input_capture_info_t input_capture_info;
float variable_rpm_tx;
ULONG variable_rpm_ulong;

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
    /*Local Variables*/
    volatile uint32_t g_capture_counter;
    volatile float g_time_captured;
    volatile uint32_t g_capture_overflow=0;
    volatile uint32_t g_pclk_freq_hz;
    volatile float g_rpm;

    #define BIT_32_OVERFLOW (0x100000000U)

    if(CHANNEL_NINE == p_args->channel)
    {
        switch(p_args->event)
        {
            case INPUT_CAPTURE_EVENT_MEASUREMENT:

                /* Get the value of the captured counter and overflows number */
                g_capture_counter = p_args->counter;

                /*
                * Currently there is a limitation for using API of lastCaptureGet, otherwise captured counter and overflows number can
                * be got from g_input_capture.p_api->lastCaptureGet. Please refer to the documentation for more information.
                */

                /* Get the frequency of PCLKD in Hz*/
                g_cgc_on_cgc.systemClockFreqGet(CGC_SYSTEM_CLOCKS_PCLKD, (uint32_t*)&g_pclk_freq_hz);

                /* Calculate time value of measurement (ns) */
                g_time_captured = (float)(g_capture_overflow * BIT_32_OVERFLOW);
                g_time_captured += (float)(g_capture_counter + 1);
                g_time_captured /= (float)g_pclk_freq_hz;
                g_time_captured *= (float)4;

                /*get the RPMs*/
                g_rpm = (float)(60.0 / (float)(g_time_captured));
                variable_rpm_tx = g_rpm;

                /*Send the speed for control*/
                tx_queue_send(&ADC_Queue,&variable_rpm_tx, TX_NO_WAIT);


                /*erase the variables for new calculations*/
                g_time_captured = 0;
                g_capture_overflow = 0;
                break;

            case INPUT_CAPTURE_EVENT_OVERFLOW:

                /*
                * Current there is a limitation for using parameter of p_args->overflows, otherwise overflows number can be got from p_args->overflows. Please refer to the documentation.
                */

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
