/*
 * pid.h
 *
 *  Created on: Feb 2, 2023
 *      Author: vienchau
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include <stdint.h>

#define THRESHOLD_ENCODER 32768

// control PID Structure
typedef struct
{
    float dKp, dKi, dKd;
    float dErrorTerm;
    float dIntergral;
} PID_CONTROL_t;

extern void PIDReset(PID_CONTROL_t *PID_Ctrl);
extern void PIDInit(PID_CONTROL_t *PID_Ctrl, float dKp, float dKi, float dKd);
extern void PIDTunningSet(PID_CONTROL_t *PID_Ctrl, float dKp, float dKi, float dKd);
extern float PIDCompute(PID_CONTROL_t *PID_Ctrl, float dCmdValue, float dActValue, float dTs);

#endif /* INC_PID_H_ */
