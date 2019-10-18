/*
 * stateMachine.h
 *
 *  Created on: 09/10/2019
 *      Author: mulca
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_


#define C_BTN_PRESSED IOPORT_LEVEL_LOW
#define C_LED_ON IOPORT_LEVEL_LOW
#define C_LED_OFF IOPORT_LEVEL_HIGH
#define myInitState 0
#define myRunning_State 1
#define myStop_State 2

int stateMachine(int*);

#endif /* STATEMACHINE_H_ */
