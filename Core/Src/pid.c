/*
 * pid.c
 *
 *  Created on: Feb 2, 2023
 *      Author: vienchau
 */

#include "pid.h"
#include "tim.h"

float g_dPIDError = 0;

// reset PID params
void PIDReset(PID_CONTROL_t *PID_Ctrl)
{
    PID_Ctrl->dIntergral = 0.0f;
    PID_Ctrl->dErrorTerm = 0.0f;
    g_dPIDError = 0;
}

// init PID
void PIDInit(PID_CONTROL_t *PID_Ctrl, float dKp, float dKi, float dKd)
{
    PIDReset(PID_Ctrl);
    PID_Ctrl->dKp = dKp;
    PID_Ctrl->dKi = dKi;
    PID_Ctrl->dKd = dKd;

}

// set new PID params
void PIDTunningSet(PID_CONTROL_t *PID_Ctrl, float dKp, float dKi, float dKd)
{
    if (dKp < 0.0f || dKi < 0.0f || dKp < 0.0f)
    {
        return;
    }

    PID_Ctrl->dKp = dKp;
    PID_Ctrl->dKi = dKi;
    PID_Ctrl->dKd = dKd;
}

// Compute PID Controllers
float PIDCompute(PID_CONTROL_t *PID_Ctrl, float dCmdValue, float dActValue, float dTs)
{
    float dPIDResult;
    g_dPIDError = dCmdValue - dActValue;
    float dP = 0, dI = 0, dD = 0;

    dP = PID_Ctrl->dKp * g_dPIDError;
    PID_Ctrl->dIntergral += g_dPIDError;
    dI = PID_Ctrl->dKi * dTs / 2 * PID_Ctrl->dIntergral;
    dD = PID_Ctrl->dKd * (g_dPIDError - PID_Ctrl->dErrorTerm) / dTs;
    dPIDResult = dP + dI + dD;
    PID_Ctrl->dErrorTerm = g_dPIDError;

    return dPIDResult;
}
