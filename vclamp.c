//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006-2008 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "heccer/vclamp.h"


/// **************************************************************************
///
/// SHORT: VClampAddVariable()
///
/// ARGS.:
///
///	pvc.........: voltage clamper.
///	pvVoltage...: pointer to the voltage variable, assumed is double *
///	pvInjector..: pointer to the variable for injected current.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Clamp the given voltage variable, using the given injector.
///
/// **************************************************************************

int
VClampAddVariable
(struct VClamp * pvc, void *pvVoltage, void *pvInjector)
{
    //- set default result: ok

    int iResult = 1;

    if (pvc->iClampsActive >= 1)
    {
	return(0);
    }

    //- set next variable

    pvc->pdVoltage = (double *)pvVoltage;

    pvc->pdInjector = (double *)pvInjector;

    pvc->iClampsActive++;

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: VClampFinish()
///
/// ARGS.:
///
///	pvc...: voltage clamper.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Free the voltage clamper.
///
/// **************************************************************************

int VClampFinish(struct VClamp * pvc)
{
    //- set default result: ok

    int iResult = 1;

    //- free all allocated memory

    free(pvc);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: VClampInitiate()
///
/// ARGS.:
///
///	pvc...: voltage clamper.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Initiate the voltage clamper.
///
/// **************************************************************************

int VClampInitiate(struct VClamp * pvc)
{
    //- set default result: ok

    int iResult = 1;

    //- just clear out some varialbes...

    //t should initialize from a stream as heccer does.

    pvc->dEIntegral = 0;
    pvc->dEPrevious = 0;
    pvc->dOutput = 0;

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: VClampNew()
///
/// ARGS.:
///
///	pcName..: name of this object.
///
/// RTN..: struct VClamp *
///
///	voltage clamper, NULL for failure.
///
/// DESCR: voltage clamper.
///
/// **************************************************************************

struct VClamp * VClampNew(char *pcName)
{
    //- set default result: failure

    struct VClamp * pvcResult = NULL;

    //- allocate voltage clamper

    pvcResult = (struct VClamp *)calloc(1, sizeof(struct VClamp));

    if (!pvcResult)
    {
	return(NULL);
    }

    //- set name

    pvcResult->pcName = calloc(1 + strlen(pcName), sizeof(char));

    strcpy(pvcResult->pcName, pcName);

    //- return result

    return(pvcResult);
}


/// **************************************************************************
///
/// SHORT: VClampSetFields()
///
/// ARGS.:
///
///	dInjected.....: injected current.
///	dC............: parallel initial capacitance.
///	dR............: initial resistance.
///	dCommand_init.: initial command voltage.
///	dGain.........: gain value.
///	dTau_i........: integrating time constant.
///	dTau_d........: derivative time constant.
///	dSaturation...: saturation value.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: set operation fields of voltage clamper.
///
/// NOTE.:
///
///	The initial command voltage should probably have a separate
///	setter method.
///
/// **************************************************************************

int
VClampSetFields
(struct VClamp * pvc,
 double dInjected,
 double dC,
 double dR,
 double dCommand_init,
 double dGain,
 double dTau_i,
 double dTau_d,
 double dSaturation)
{
    //- set default result: ok

    int iResult = 1;

    //- set fields

    pvc->dInjected = dInjected;

    pvc->dC = dC;
    pvc->dR = dR;
    pvc->dCommand = dCommand_init;

    pvc->dGain = dGain;
    pvc->dTau_i = dTau_i;
    pvc->dTau_d = dTau_d;
    pvc->dSaturation = dSaturation;

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: VClampSingleStep()
///
/// ARGS.:
///
///	pvc...: voltage clamper.
///	dTime.: current simulation time.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Compute new currents to correct voltages.
///
/// NOTE.:
///
///	Old current values are overwritten.
///
/// **************************************************************************

int VClampSingleStep(struct VClamp * pvc, double dTime)
{
    //- set default result: ok

    int iResult = 1;

    //- calculate the time step

    double dStep = dTime - pvc->dPreviousTime;

    //- exponential euler integration for the RC circuit

    double dA = pvc->dInjected / pvc->dC;

    double dB = 1 / (pvc->dR * pvc->dC);

    double dD = exp( - dB * dStep);

    pvc->dCommand = (pvc->dCommand * dD + (dA / dB) * (1 - dD));

    //- first preserve the previous value

    pvc->dEPrevious = pvc->dE;

    pvc->dE = pvc->dCommand - *pvc->pdVoltage;

    pvc->dEDerivative = (pvc->dE - pvc->dEPrevious) / dStep;

    pvc->dEIntegral += 0.5 * (pvc->dE + pvc->dEPrevious) * dStep;

    //- compute output

    pvc->dOutput
	= (pvc->dGain *
	   (pvc->dE
	    + pvc->dTau_d * pvc->dEDerivative
	    + 1 / pvc->dTau_i * pvc->dEIntegral));

    //- apply saturation

    if (pvc->dOutput > pvc->dSaturation)
    {
	pvc->dOutput = pvc->dSaturation;

	pvc->dEIntegral -= 0.5 * (pvc->dE + pvc->dEPrevious) * dStep;
    }
    else if (pvc->dOutput < - pvc->dSaturation)
    {
	pvc->dOutput = - pvc->dSaturation;

	pvc->dEIntegral -= 0.5 * (pvc->dE + pvc->dEPrevious) * dStep;
    }

    //- set the output

    *pvc->pdInjector = pvc->dOutput;

    //- register the current simulation time for the next time we are scheduled

    pvc->dPreviousTime = dTime;

    //- return result

    return(iResult);
}


