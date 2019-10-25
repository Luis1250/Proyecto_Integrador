/*
 * Display_lib.h
 *
 *  Created on: 10/10/2019
 *      Author: mulca
 */

#ifndef DISPLAY_LIB_H_
#define DISPLAY_LIB_H_

void Refresh_Screen(void);
void setDutyCycle(ULONG);
void setSpeed(ULONG);
void setSetPoint(ULONG);
char *  itoa ( int, char *, int);

typedef struct {
	/*Duty Cycle is percentage in a range of 0-100 */
	char dutyCycle[4];
	/*speed in RPMs from 0-9,999*/
	char speed[5];
	/*speed in RPMs from 0-9,999*/
	char setPoint[5];
}display_type;

#endif /* DISPLAY_LIB_H_ */
