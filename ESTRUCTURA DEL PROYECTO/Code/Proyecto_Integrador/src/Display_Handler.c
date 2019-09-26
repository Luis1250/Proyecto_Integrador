/*
 * Display_Handler.c
 *
 *  Created on: 09/08/2019
 *
 * - 09-aug-2019  Francisco Govea
 *  - Add_display_module
 */
//
//#include "Display_Handler.h"
//#include "gui/guiapp_resources.h"
//#include "gui/guiapp_specifications.h"

/**
 * Refer to Display_Handler.h for further information.
 */
//Data_To_Store_T Receive_Data(void)
//{
//    Data_To_Store_T aux_struct;
//    Initialize_Struct(&aux_struct);
//    tx_queue_receive(&comm_queue, &aux_struct, TX_NO_WAIT);
//    return aux_struct;
//}

/**
 * Refer to Display_Handler.h for further information.
 */
//void Refresh_Screen(Data_To_Store_T * data_struct)
//{
//    if(NULL != data_struct)
//    {
//        LONG duty = (LONG)data_struct->duty_cycle;
//        LONG rpm = (LONG)data_struct->rpm;
//        LONG set = (LONG)data_struct->set_point;
//
//        char characters[DEFAULT_SIZE_FOR_ARRAY];
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
//}
