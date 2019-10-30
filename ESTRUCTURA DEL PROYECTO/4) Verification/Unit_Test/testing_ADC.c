/*
 * tester.c
 *
 *  Created on: 25/10/2019
 *      Main function for unit test
 */


#include "stateMachine.h"
#include "Display_lib.h"
#include <math.h>
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>


int test_ADC(int, float );
void testing_ADC(void);

void testing_ADC()
{
	int testNumber=1;
	int adc,rpms;
	int result,expected;

	//for ADC=0 RPMS=0
	
	adc=0;
	rpms=0;
	expected=0;

	printf("\n\n");
	printf("===================================================\n");
	printf("|      Test %d                                     |\n",testNumber++);
	printf("| Inputs: ADC:=%3d     RPMs:= %4d                |\n",adc,rpms );
	printf("|=================================================|\n");
	printf("|Expected Result: %4d                            |\n",expected);
	result=test_ADC(adc,rpms);
	printf("|=================================================|\n");
	printf("| Current Result = %4d                           |\n",result);
	printf("|=================================================|\n");
	printf("|TEST RESULT:                   ");
	if(result == expected )
		printf("|   PASS          |\n");
	else
		printf("|   FAIL          |\n");
	printf("===================================================\n");
	
	//for ADC=0 RPMS=0
	adc=66;
	rpms=561;
	expected=25;

	printf("\n\n");
	printf("===================================================\n");
	printf("|      Test %d                                     |\n",testNumber++);
	printf("| Inputs: ADC:=%3d     RPMs:= %4d                |\n",adc,rpms );
	printf("|=================================================|\n");
	printf("|Expected Result: %4d                            |\n",expected);
	result=test_ADC(adc,rpms);
	printf("|=================================================|\n");
	printf("| Current Result = %4d                           |\n",result);
	printf("|=================================================|\n");
	printf("|TEST RESULT:                   ");
	if(result == expected )
		printf("|   PASS          |\n");
	else
		printf("|   FAIL          |\n");
	printf("===================================================\n");
	
	//for ADC=0 RPMS=0
	adc=128;
	rpms=877;
	expected=50;

	printf("\n\n");
	printf("===================================================\n");
	printf("|      Test %d                                     |\n",testNumber++);
	printf("| Inputs: ADC:=%3d     RPMs:= %4d                |\n",adc,rpms );
	printf("|=================================================|\n");
	printf("|Expected Result: %4d                            |\n",expected);
	result=test_ADC(adc,rpms);
	printf("|=================================================|\n");
	printf("| Current Result = %4d                           |\n",result);
	printf("|=================================================|\n");
	printf("|TEST RESULT:                   ");
	if(result == expected )
		printf("|   PASS          |\n");
	else
		printf("|   FAIL          |\n");
	printf("===================================================\n");
	
	//for ADC=0 RPMS=0
	adc=192;
	rpms=2576;
	expected=75;

	printf("\n\n");
	printf("===================================================\n");
	printf("|      Test %d                                     |\n",testNumber++);
	printf("| Inputs: ADC:=%3d     RPMs:= %4d                |\n",adc,rpms );
	printf("|=================================================|\n");
	printf("|Expected Result: %4d                            |\n",expected);
	result=test_ADC(adc,rpms);
	printf("|=================================================|\n");
	printf("| Current Result = %4d                           |\n",result);
	printf("|=================================================|\n");
	printf("|TEST RESULT:                   ");
	if(result == expected )
		printf("|   PASS          |\n");
	else
		printf("|   FAIL          |\n");
	printf("===================================================\n");
	
	//for ADC=0 RPMS=0
	adc=254;
	rpms=3234;
	expected=100;

	printf("\n\n");
	printf("===================================================\n");
	printf("|      Test %d                                     |\n",testNumber++);
	printf("| Inputs: ADC:=%3d     RPMs:= %4d                |\n",adc,rpms );
	printf("|=================================================|\n");
	printf("|Expected Result: %d                             |\n",expected);
	result=test_ADC(adc,rpms);
	printf("|=================================================|\n");
	printf("| Current Result 100                              |\n");
	printf("|=================================================|\n");
	printf("|TEST RESULT:                   ");
	if(result != expected )
		printf("|   PASS          |\n");
	else
		printf("|   FAIL          |\n");
	printf("===================================================\n");

}

