/*
 * constants.h
 *
 *  Created on: 15/10/2019
 *      In this file are all the constants definitions.
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/*ADC constants*/
#define PI_ADC_K 2.0

/*Control Constants*/
#define PI_Ctrl_Ki 0.253461615626274
#define PI_Ctrl_Kp 0.39644212156124
#define PI_Ctrl_Kd 0.0220414662986352


/*transfer function from set point to speed reference*/
#define PI_Transfer_Function_x1 1.445E-7
#define PI_Transfer_Function_x2 -4.206E-5
#define PI_Transfer_Function_x3 0.004221
#define PI_Transfer_Function_x4 -0.1603
#define PI_Transfer_Function_x5 1.372
#define PI_Transfer_Function_x6 38.38
#define PI_Transfer_Function_x7 31.37


#endif /* CONSTANTS_H_ */
