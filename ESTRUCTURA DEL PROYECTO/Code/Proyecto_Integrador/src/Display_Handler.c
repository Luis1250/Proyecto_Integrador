/*
 * Display_Handler.c
 *
 *
 *  Created on: 01/10/2019
 *      Author: Team 2
 */
//
#include "Display_Handler.h"
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"

#include "main_thread.h"

void Refresh_Screen();

/**
 * Refer to Display_Handler.h for further information.
 */
/*Data_To_Store_T Receive_Data(void)
{
    Data_To_Store_T aux_struct;
    Initialize_Struct(&aux_struct);
    tx_queue_receive(&comm_queue, &aux_struct, TX_NO_WAIT);
    return aux_struct;
}*/

/**
 * Refer to Display_Handler.h for further information.
 */
void Refresh_Screen(/*Data_To_Store_T * data_struct*/)
{
//    if(NULL != data_struct)
//    {
//        LONG duty = (LONG)data_struct->duty_cycle;
//        LONG rpm = (LONG)data_struct->rpm;
//        LONG set = (LONG)data_struct->set_point;
//
        GX_CHAR swVerAux[5];
        UINT DEFAULT_SIZE = 5;
        UINT status;
//
//        gx_utility_ltoa(duty, characters, DEFAULT_SIZE);
//        gx_prompt_text_set(&window.window_duty_cycle_value_lbl, characters);
//        gx_system_dirty_mark((GX_WIDGET*)&window.window_duty_cycle_value_lbl);
//        gx_system_canvas_refresh();
//
//        gx_utility_ltoa(rpm, characters, DEFAULT_SIZE);
//        gx_prompt_text_set(&window.window_rpm_value_lbl, characters);
//        gx_system_dirty_mark((GX_WIDGET*)&window.window_rpm_value_lbl);
//        gx_system_canvas_refresh();
//
//        gx_utility_ltoa(set, characters, DEFAULT_SIZE);
//        gx_prompt_text_set(&window.window_speed_value_lbl, characters);
//        gx_system_dirty_mark((GX_WIDGET*)&window.window_speed_value_lbl);
//        gx_system_canvas_refresh();
//    }
    LONG swVer = 5;
    gx_utility_ltoa(swVer,swVerAux,DEFAULT_SIZE);
    status = gx_prompt_text_set(&window1.window1_swver,swVerAux);
    status++;
    status = gx_prompt_text_set(&window1.window1_swver,"0.1");
    gx_system_dirty_mark((GX_WIDGET*)&window1.window1_swver);
     gx_system_canvas_refresh();

}
