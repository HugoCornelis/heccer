//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#ifndef HECCER_VM_H
#define HECCER_VM_H


#include <stdio.h>


struct VM;


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


#include "callout.h"


//s vm related (name subject to change)

struct VM
{
    //m compartment operations

    int iCops;

    int *piCops;

    //m compartment data

    int iDiagonals;

    double *pdDiagonals;

    int iAxres;

    double *pdAxres;

    //m results

    int iResults;

    double *pdResults;

    //! pdVm is accessible from outside, so should be moved to a
    //! separate place ?

    int iVms;

    double *pdVms;

    //m mechanism operations

    int iMops;

    int *pvMops;

    //m mechanism data

    //t data type unspecified

    int iMats;

    void *pvMats;

};


struct MatsCompartment
{
    double dLeak;
    double dInjected;
    double dCapacity;
    double dDiagonal;
};


struct MatsCallout
{
/*     double d; */

/*     //m the external solver (or glue to) */

/*     ExternalFunction *pfCall; */

    //m currently points to intermediary

    struct Callout *pco;
};


struct MopsChannel
{
    //m operation : HECCER_MOP_CHANNEL

    int iOperator;

    //m reversal potential

    double dReversalPotential;

    //m maximal channel conductance

    double dMaximalConductance;

    //! note : more specific things follow, notable gate operations
};


struct MatsChannel
{
    //m total channel conductance

    double dConductance;
};


struct MopsVoltageTableDependence
{
    //t so in principle the following operation is only needed once
    //t per compartment.  Still have to figure out how.

    //m operator : HECCER_MOP_LOADVOLTAGETABLE

    int iOperator;
};


struct MopsSingleGateConcept
{
    //m operator : HECCER_MOP_CONCEPTGATE

    int iOperator;

    //m table index

    int iTableIndex;

    //m power to apply

    int iPower;
};


struct MatsSingleGateConcept
{
    //m gate activation

    double dActivation;
};


//d operations for compartments

#define HECCER_COP_FORWARD_ELIMINATION		1
#define HECCER_COP_BACKWARD_SUBSTITUTION	2
#define HECCER_COP_FINISH_ROW			3
#define HECCER_COP_FINISH			4
#define HECCER_COP_SET_DIAGONAL			5
#define HECCER_COP_NEXT_ROW			6

#define HECCER_COP_CN_FOBA_ELIMINATION	( 1 || 16 )
#define HECCER_COP_CN_CALC_RESULTS	( 2 || 16 )
#define HECCER_COP_CN_FINISH		( 3 || 16 )
#define HECCER_COP_CN_SET_DIAGONAL	( 4 || 16 )
#define HECCER_COP_CN_SKIP_DIAGONAL	( 5 || 16 )
					  	  
#define HECCER_COP_BE_FOBA_ELIMINATION	( 1 || 32 )
#define HECCER_COP_BE_CALC_RESULTS	( 2 || 32 )
#define HECCER_COP_BE_FINISH		( 3 || 32 )
#define HECCER_COP_BE_SET_DIAGONAL	( 4 || 32 )
#define HECCER_COP_BE_SKIP_DIAGONAL	( 5 || 32 )


//d operations for mechanisms

#define HECCER_MOP_COMPARTMENT 1
#define HECCER_MOP_FINISH 2

#define HECCER_MOP_CALLOUT 10

#define HECCER_MOP_CHANNEL 20
#define HECCER_MOP_LOADVOLTAGETABLE 21
#define HECCER_MOP_CONCEPTGATE 22


//d all operators for mechanisms have an opcode larger than ...

//t but perhaps this should be done using flags, not sure.

#define HECCER_MOP_COMPARTMENT_BARRIER 9


//f prototypes

int
HeccerVMDump
(struct VM *pvm, FILE *pfile, int iSelection);


#endif


