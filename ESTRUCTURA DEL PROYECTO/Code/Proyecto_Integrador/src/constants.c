/*
 * constants.c
 *
 *  Created on: 15/10/2019
 *      This files contains all the constants of the Proyecto Integrador
 */

#include "constants.h"

/*ADC constants*/
float PI_ADC_K = 2.0;

/*Control Constants*/
double PI_Ctrl_Ki = 0.253461615626274;
double PI_Ctrl_Kp = 0.39644212156124;
double PI_Ctrl_Kd = 0.0220414662986352;


/*transfer function from set point to speed reference*/
double PI_Transfer_Function_x1 = 1.445E-7;
double PI_Transfer_Function_x2 = -4.206E-5;
double PI_Transfer_Function_x3 = 0.004221;
double PI_Transfer_Function_x4 = -0.1603;
double PI_Transfer_Function_x5 = 1.372;
double PI_Transfer_Function_x6 = 38.38;
double PI_Transfer_Function_x7 = 31.37;

/*transfer function from speed reference to new set point*/
float PI_Transfer_Function_y1 = 0.0267;
float PI_Transfer_Function_y2 = 12.36;
/*
 * All the constants are macros to save memory.
 * All the constants are located in the header file.
 *
 * */
