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


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "heccer/perfectclamp.h"


/// **************************************************************************
///
/// SHORT: PerfectClampAddVariable()
///
/// ARGS.:
///
///	ppc.........: voltage clamper.
///	pvVoltage...: pointer to the voltage variable, assumed is double *
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Clamp the given voltage variable.
///
/// **************************************************************************

int
PerfectClampAddVariable
(struct PerfectClamp * ppc, void *pvVoltage)
{
    //- set default result: ok

    int iResult = 1;

    if (ppc->iClampsActive >= 1)
    {
	return(0);
    }

    //- set next variable

    ppc->pdVoltage = (double *)pvVoltage;

    ppc->iClampsActive++;

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: PerfectClampFinish()
///
/// ARGS.:
///
///	ppc...: voltage clamper.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Free the voltage clamper.
///
/// **************************************************************************

int PerfectClampFinish(struct PerfectClamp * ppc)
{
    //- set default result: ok

    int iResult = 1;

    //- free all allocated memory

    free(ppc);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: PerfectClampInitiate()
///
/// ARGS.:
///
///	ppc...: voltage clamper.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Initiate the voltage clamper.
///
/// **************************************************************************

int PerfectClampInitiate(struct PerfectClamp * ppc)
{
    //- set default result: ok

    int iResult = 1;

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: PerfectClampNew()
///
/// ARGS.:
///
///	pcName..: name of this object.
///
/// RTN..: struct PerfectClamp *
///
///	voltage clamper, NULL for failure.
///
/// DESCR: voltage clamper.
///
/// **************************************************************************

struct PerfectClamp * PerfectClampNew(char *pcName)
{
    //- set default result: failure

    struct PerfectClamp * ppcResult = NULL;

    //- allocate voltage clamper

    ppcResult = (struct PerfectClamp *)calloc(1, sizeof(struct PerfectClamp));

    if (!ppcResult)
    {
	return(NULL);
    }

    //- set name

    ppcResult->pcName = calloc(1 + strlen(pcName), sizeof(char));

    strcpy(ppcResult->pcName, pcName);

    //- return result

    return(ppcResult);
}


/// **************************************************************************
///
/// SHORT: PerfectClampSetFields()
///
/// ARGS.:
///
///	dCommand.....: command voltage.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: set operation fields of voltage clamper.
///
/// **************************************************************************

int
PerfectClampSetFields
(struct PerfectClamp * ppc,
 double dCommand)
{
    //- set default result: ok

    int iResult = 1;

    //- set fields

    ppc->dCommand = dCommand;

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: PerfectClampSingleStep()
///
/// ARGS.:
///
///	ppc...: voltage clamper.
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

int PerfectClampSingleStep(struct PerfectClamp * ppc, double dTime)
{
    //- set default result: ok

    int iResult = 1;

    //- set the output

    *ppc->pdVoltage = ppc->dCommand;

    //- return result

    return(iResult);
}


