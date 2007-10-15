//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006-2007 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "heccer/vclamp.h"


#define ALLOCATE_VARIABLES 10000


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

    if (pvc->iClampsActive >= ALLOCATE_VARIABLES)
    {
	return(0);
    }

    //- set next variable

    pvc->ppdVoltage[pvc->iClampsActive] = (double *)pvVoltage;

    pvc->ppdInjector[pvc->iClampsActive] = (double *)pvInjector;

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

    free(pvc->ppdVoltage);
    free(pvc->ppdInjector);
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

    //- allocate output variables

    pvcResult->ppdVoltage = (double **)calloc(ALLOCATE_VARIABLES, sizeof(double *));

    pvcResult->ppdInjector = (double **)calloc(ALLOCATE_VARIABLES, sizeof(double *));

    pvcResult->iClampsAllocated = ALLOCATE_VARIABLES;

    if (!pvcResult->ppdVoltage
	|| !pvcResult->ppdInjector)
    {
	free(pvcResult->ppdVoltage);
	free(pvcResult->ppdInjector);
	free(pvcResult);

	return(NULL);
    }

    //- return result

    return(pvcResult);
}


/// **************************************************************************
///
/// SHORT: VClampSetFields()
///
/// ARGS.:
///
///	dCommand....: command voltage.
///	dGain.......: gain value.
///	dTau_i......: integrating time constant.
///	dTau_d......: derivative time constant.
///	dSaturation.: saturation value.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: set operation fields of voltage clamper.
///
/// **************************************************************************

int
VClampSetFields
(struct VClamp * pvc,
 double dCommand,
 double dGain,
 double dTau_i,
 double dTau_d,
 double dSaturation)
{
    //- set default result: ok

    int iResult = 1;

    //- set fields

    pvc->dCommand = dCommand;

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

    //- first preserver the previous area

    pvc->dEPrevious = pvc->dE;

    pvc->dE = pvc->dCommand - *pvc->ppdVoltage[0];

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

    *pvc->ppdInjector[0] = pvc->dOutput;

    //- register the current simulation time for the next time we are scheduled

    pvc->dPreviousTime = dTime;

    //- return result

    return(iResult);
}


