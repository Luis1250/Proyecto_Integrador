/*
 * getSpeedRef.c
 *
 *  Created on: 16/10/2019
 *
 *  logic flow:
 *  This function receives a set point and returns a speed reference
 */

#include <math.h>
#include "getSpeedRef.h"
#include "constants.h"

float getSpeedRef(double dutyCycle)
{

	double speedCalculated_dbl;
	int    speedCalculated_int;
	float  speedCalculated_flt;

	/*Get the speed using the coefficients using high precision */
	speedCalculated_dbl = (PI_Transfer_Function_x1*pow(dutyCycle,6)) +
	                      (PI_Transfer_Function_x2*pow(dutyCycle,5)) +
			 		      (PI_Transfer_Function_x3*pow(dutyCycle,4)) +
					      (PI_Transfer_Function_x4*pow(dutyCycle,3)) +
					      (PI_Transfer_Function_x5*pow(dutyCycle,2)) +
					      (PI_Transfer_Function_x6*dutyCycle) +
					       PI_Transfer_Function_x7;

	/*round the value and get integer part */
	speedCalculated_int = (int) (speedCalculated_dbl + 0.5);

	/*return the value in float format*/
	speedCalculated_flt = (float) (speedCalculated_int * 1.0);

	return speedCalculated_flt;
}
