/*
 * constants.h
 *
 *  Created on: 15/10/2019
 *      In this file are all the constants definitions.
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/*ADC constants*/
extern float PI_ADC_K;

/*Control Constants*/
extern double PI_Ctrl_Ki;
extern double PI_Ctrl_Kp;
extern double PI_Ctrl_Kd;


/*transfer function from set point to speed reference*/
extern double PI_Transfer_Function_x1;
extern double PI_Transfer_Function_x2;
extern double PI_Transfer_Function_x3;
extern double PI_Transfer_Function_x4;
extern double PI_Transfer_Function_x5;
extern double PI_Transfer_Function_x6;
extern double PI_Transfer_Function_x7;

/*transfer function from speed reference to new set point*/
extern float PI_Transfer_Function_y1;
extern float PI_Transfer_Function_y2;


#endif /* CONSTANTS_H_ */
