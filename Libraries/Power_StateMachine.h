/*
 * Power_StateMachine.h
 *
 *  Created on: Nov 7, 2022
 *      Author: fil
 */

#ifndef POWER_STATEMACHINE_H_
#define POWER_STATEMACHINE_H_


extern	void PowerStateMachine(void);
extern	void Debug_PrintVoltages(void);
extern	void BoardPowerOn(void);
extern	void BoardPowerOff(void);
extern	void CarrierPowerOn(void);
extern	void CarrierPowerOff(void);

#endif /* POWER_STATEMACHINE_H_ */
