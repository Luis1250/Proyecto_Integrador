/** File: pwm_thread_handler.h
 *
 *  Created on: 01/10/2019
 *      Author: Team 2
 */

#include <PWM_Thread.h>
#include "pwm_thread_handler.h"

/**
 * pwm_thread_entry function that will execute periodically.
 */
void pwm_thread_entry(void)
{
    Initialize_PWM_Timer(&pwm_timer);

    while (true)
    {
        Receive_Message();
        Generate_Signal(&pwm_timer);
        tx_thread_sleep (DEFAULT_WAIT_MS);
    }
}
