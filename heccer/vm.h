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

    //t pdVm is accessible from outside, so should be moved to a
    //t separate place ?
    //t will become clear when addressing gets in place.

    int iVms;

    double *pdVms;

    //m mechanism operations

    int iMops;

    int *pvMops;

    //m mechanism data

    //t same as for pdVms applies, see above.

    int iMats;

    void *pvMats;

    //m fluxes link channels and pools

    int iFluxes;

    double *pdFluxes;
};


#define SETMOP_FINISH(pvMops,iMops) ((pvMops) ? ({ ((int *)pvMops)[0] = HECCER_MOP_FINISH; (pvMops) = (void *)&((int *)pvMops)[1]; 1; }) : ({ (iMops) += sizeof(int); }) )

//t can be automated by taking an array and diffing casted to char *
//t pointers to sequent entries ?

#define ALIGNER8(s) ((((sizeof(s) - 1) >> 3) + 1) << 3)

#define ALIGNER4(s) ((((sizeof(s) - 1) >> 3) + 1) << 2)

//d mats are aligned to 8 bytes

#define MAT_ALIGNER ALIGNER8


struct MatsCompartment
{
    double dLeak;
    double dInjected;
    double dCapacity;
    double dDiagonal;
};


#define SETMOP_COMPARTMENT(pvMops,iMops) ((pvMops) ? ({ ((int *)pvMops)[0] = HECCER_MOP_COMPARTMENT; (pvMops) = (void *)&((int *)pvMops)[1]; 1; }) : ({ (iMops) += sizeof(int); }) )

#define SETMAT_COMPARTMENT(pvMats,iMats,dL,dI,dC,dD) ((pvMats) ? ({ struct MatsCompartment *pmats = (struct MatsCompartment *)pvMats ; pmats->dLeak = (dL) ; pmats->dInjected = (dI) ; pmats->dCapacity = (dC) ; pmats->dDiagonal = (dD) ; pvMats = (void *)&((struct MatsCompartment *)pvMats)[1] ; 1 ;}) : (iMats += MAT_ALIGNER(struct MatsCompartment)))


struct MatsCallout
{
/*     double d; */

/*     //m the external solver (or glue to) */

/*     ExternalFunction *pfCall; */

    //m currently points to intermediary

    struct Callout *pco;
};

#define SETMOP_CALLOUT(pvMops,iMops) ((pvMops) ? ({ ((int *)pvMops)[0] = HECCER_MOP_CALLOUT; (pvMops) = (void *)&((int *)pvMops)[1]; 1; }) : ({ (iMops) += sizeof(int); }) )

#define SETMAT_CALLOUT(pvMats,iMats,p) ((pvMats) ? ({ struct MatsCallout *pmats = (struct MatsCallout *)pvMats ; pmats->pco = (p) ; pvMats = (void *)&((struct MatsCallout *)pvMats)[1] ; 1 ;}) : (iMats += MAT_ALIGNER(struct MatsCallout)))


struct MopsChannel
{
    //m operation : HECCER_MOP_INITIALIZECHANNEL

    int iOperator;

    //m reversal potential

    double dReversalPotential;

    //m maximal channel conductance

    double dMaximalConductance;

    //! note : more specific things follow, notable gate operations
};


#define SETMOP_INITIALIZECHANNEL(pvMops,iMops,dG,dE) ((pvMops) ? ({ struct MopsChannel *pmops = (struct MopsChannel *)(pvMops); pmops->iOperator = HECCER_MOP_INITIALIZECHANNEL; pmops->dReversalPotential = (dE) ; pmops->dMaximalConductance = (dG) ; (pvMops) = (void *)&pmops[1]; 1; }) : ((iMops) += sizeof(struct MopsChannel)))


struct MopsStoreChannelConductance
{
    //m operator : HECCER_MOP_STORECHANNELCONDUCTANCE

    int iOperator;
};

struct MatsChannel
{
    //m single channel conductance

    double dChannelConductance;
};

#define SETMOP_STORECHANNELCONDUCTANCE(pvMops,iMops) ((pvMops) ? ({ struct MopsStoreChannelConductance *pmops = (struct MopsStoreChannelConductance *)(pvMops); pmops->iOperator = HECCER_MOP_STORECHANNELCONDUCTANCE ; (pvMops) = (void *)&pmops[1]; 1; }) : ((iMops) += sizeof(struct MopsStoreChannelConductance)))


struct MopsVoltageTableDependence
{
    //t so in principle the following operation is only needed once
    //t per compartment.  Still have to figure out how.

    //m operator : HECCER_MOP_LOADVOLTAGETABLE

    int iOperator;
};

#define SETMOP_LOADVOLTAGETABLE(pvMops,iMops) ((pvMops) ? ({ struct MopsVoltageTableDependence *pmops = (struct MopsVoltageTableDependence *)(pvMops); pmops->iOperator = HECCER_MOP_LOADVOLTAGETABLE ; (pvMops) = (void *)&pmops[1]; 1; }) : ((iMops) += sizeof(struct MopsVoltageTableDependence)))


struct MopsUpdateCompartmentCurrent
{
    //m operator : HECCER_MOP_UPDATECOMPARTMENTCURRENT

    int iOperator;
};

#define SETMOP_UPDATECOMPARTMENTCURRENT(pvMops,iMops) ((pvMops) ? ({ struct MopsUpdateCompartmentCurrent *pmops = (struct MopsUpdateCompartmentCurrent *)(pvMops); pmops->iOperator = HECCER_MOP_UPDATECOMPARTMENTCURRENT ; (pvMops) = (void *)&pmops[1]; 1; }) : ((iMops) += sizeof(struct MopsUpdateCompartmentCurrent)))


struct MopsSingleGateConcept
{
    //m operator : HECCER_MOP_CONCEPTGATE

    int iOperator;

    //m table index

    int iTableIndex;

    //m power to apply

    int iPower;
};

#define SETMOP_POWEREDGATECONCEPT(pvMops,iMops,iT,iP) ((pvMops) ? ({ struct MopsSingleGateConcept *pmops = (struct MopsSingleGateConcept *)(pvMops); pmops->iOperator = HECCER_MOP_CONCEPTGATE; pmops->iTableIndex = (iT) ; pmops->iPower = (iP) ; (pvMops) = (void *)&pmops[1]; 1; }) : ((iMops) += sizeof(struct MopsSingleGateConcept)))


struct MatsSingleGateConcept
{
    //m gate activation

    double dActivation;
};

#define SETMAT_POWEREDGATECONCEPT(pvMats,iMats,dA) ((pvMats) ?  ({ struct MatsSingleGateConcept *pmats = (struct MatsSingleGateConcept *)pvMats ; pmats->dActivation = (dA) ; pvMats = (void *)&((struct MatsSingleGateConcept *)pvMats)[1] ; 1 ;}) : (iMats += MAT_ALIGNER(struct MatsSingleGateConcept)))


struct MopsExponentialDecay
{
    //m operator : HECCER_MOP_EXPONENTIALDECAY

    int iOperator;

    //m beta

    double dBeta;

    //m steady state

    double dSteadyState;

    //m tau

    double dTau;

};


struct MatsExponentialDecay
{
    //m resulting state

    double dState;
};

#define SETMOP_EXPONENTIALDECAY(pvMops,iMops,dB,dS,dT) ((pvMops) ? ({ struct MopsExponentialDecay *pmops = (struct MopsExponentialDecay *)(pvMops); pmops->iOperator = HECCER_MOP_EXPONENTIALDECAY; pmops->dBeta = (dB) ; pmops->dSteadyState = (dS) ; pmops->dTau = (dT) ; (pvMops) = (void *)&pmops[1]; 1; }) : ((iMops) += sizeof(struct MopsExponentialDecay)))
     
#define SETMAT_EXPONENTIALDECAY(pvMats,iMats,dS) ((pvMats) ? ({ struct MatsExponentialDecay *pmats = (struct MatsExponentialDecay *)pvMats ; pmats->dState = (dS) ; pvMats = (void *)&((struct MatsExponentialDecay *)pvMats)[1] ; 1 ;}) : (iMats += MAT_ALIGNER(struct MatsExponentialDecay)))


struct MopsFluxPool
{
    //m operator : HECCER_MOP_FLUXPOOL

    int iOperator;

    //m pool index

    int iPool;
};

struct MatsFluxPool
{
    //m resulting flux

    double dFlux;
};

#define SETMOP_FLUXPOOL(pvMops,iMops,iP) ((pvMops) ? ({ struct MopsFluxPool *pmops = (struct MopsFluxPool *)(pvMops); pmops->iOperator = HECCER_MOP_FLUXPOOL; pmops->iPool = (iP) ; (pvMops) = (void *)&pmops[1]; 1; }) : ((iMops) += sizeof(struct MopsFluxPool)))
     
#define SETMAT_FLUXPOOL(pvMats,iMats,dF) ((pvMats) ? ({ struct MatsFluxPool *pmats = (struct MatsFluxPool *)pvMats ; pmats->dFlux = (dF) ; pvMats = (void *)&((struct MatsFluxPool *)pvMats)[1] ; 1 ;}) : (iMats += MAT_ALIGNER(struct MatsFluxPool)))


struct MopsRegisterChannelCurrent
{
    //m operator : HECCER_MOP_REGISTERCHANNELCURRENT

    int iOperator;
};

#define SETMOP_REGISTERCHANNELCURRENT(pvMops,iMops) ((pvMops) ? ({ struct MopsRegisterChannelCurrent *pmops = (struct MopsRegisterChannelCurrent *)(pvMops); pmops->iOperator = HECCER_MOP_REGISTERCHANNELCURRENT ; (pvMops) = (void *)&pmops[1]; 1; }) : ((iMops) += sizeof(struct MopsRegisterChannelCurrent)))


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

#define HECCER_MOP_INITIALIZECHANNEL 20
#define HECCER_MOP_LOADVOLTAGETABLE 21
#define HECCER_MOP_CONCEPTGATE 22
#define HECCER_MOP_STORECHANNELCONDUCTANCE 23
#define HECCER_MOP_EXPONENTIALDECAY 24
#define HECCER_MOP_FLUXPOOL 25
#define HECCER_MOP_REGISTERCHANNELCURRENT 26

#define HECCER_MOP_UPDATECOMPARTMENTCURRENT 30

//d all operators for mechanisms have an opcode larger than ...

//t but perhaps this should be done using flags, not sure.

#define HECCER_MOP_COMPARTMENT_BARRIER 9


//f prototypes

int
HeccerVMDump
(struct VM *pvm, FILE *pfile, int iSelection);


#endif


