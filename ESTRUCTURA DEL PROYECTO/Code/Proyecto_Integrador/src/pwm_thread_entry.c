/** File: pwm_thread_handler.h
 *
 *  Created on: 22/07/2019
 *
 * - 22-jul-2019  Francisco Govea
 *   - Add improvements to PWM
 *
 * - 24-jul-2019  Francico Govea
 *   - Add interruption
 *
 * - 25-jul-2019  Francisco Govea
 *   - Add interruption for Encoder
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
