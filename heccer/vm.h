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
#include "mechanism.h"


typedef union
{
    //m index into mathcomponents

    int iMat;

    //m direct value

    double *pdValue;

}
    uMC2Mat;

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

    //m math component number to mat number convertor

    //! note that this one does not index compartments, only the mechanism math components.

    uMC2Mat *piMC2Mat;

    //m math component number to mop number convertor

    int *piMC2Mop;

    //m mechanism operations

    int iMopNumber;

    int iMops;

    void *pvMops;

    //m mechanism addressables

    //t same as for pdVms applies, see above.

    int iMatNumber;

    int iMats;

    void *pvMats;

    //m indexing from mops or mats number towards one of the above

    void **ppvCMatsIndex;

    void **ppvMopsIndex;

    void **ppvMatsIndex;

/*     //m fluxes link channels and pools */

/*     int iFluxes; */

/*     double *pdFluxes; */

/*     //m concentrations link pools and channels */

/*     int iConcentrations; */

/*     double **ppdConcentrations; */
};


#define SETMOP_FINISH(ppvMopsIndex,iMopNumber,pvMops,iMops)	\
    ((pvMops)							\
     ? ({							\
	     ((int *)pvMops)[0] = HECCER_MOP_FINISH;		\
	     ppvMopsIndex[iMopNumber++] = pvMops;		\
	     (pvMops) = (void *)&((int *)pvMops)[1];		\
	     1;							\
	 })							\
     : (							\
	 (ppvMopsIndex)						\
	 ? ({							\
		 iMopNumber++;					\
		 (iMops) += sizeof(int);			\
		 1;						\
	     })							\
	 : ({ iMopNumber++; 1; }) ) )

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


#define SETMOP_COMPARTMENT(ppvMopsIndex,iMopNumber,pvMops,iMops)	\
    ((pvMops)								\
     ? ({								\
	     ((int *)pvMops)[0] = HECCER_MOP_COMPARTMENT;		\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&((int *)pvMops)[1];			\
	     1;								\
	 })								\
     : (								\
	 (ppvMopsIndex)							\
	 ? ({								\
		 iMopNumber++;						\
		 (iMops) += sizeof(int);				\
		 1;							\
	     })								\
	 : ({ iMopNumber++; 1; }) ) )

#define SETMAT_COMPARTMENT(ppvCMatsIndex,iCNumber,ppvMatsIndex,iMatNumber,pvMats,iMats,dL,dI,dC,dD) \
    ((pvMats)								\
     ? ({ struct MatsCompartment *pmats = (struct MatsCompartment *)pvMats ; \
	     pmats->dLeak = (dL) ; pmats->dInjected = (dI) ;		\
	     pmats->dCapacity = (dC) ;					\
	     pmats->dDiagonal = (dD) ;					\
	     ppvCMatsIndex[iCNumber] = pvMats;				\
	     ppvMatsIndex[iMatNumber++] = pvMats;			\
	     pvMats = (void *)&((struct MatsCompartment *)pvMats)[1] ;	\
	     1 ;							\
	 })								\
     : (								\
	 (ppvMatsIndex)							\
	 ? ({								\
		 iMatNumber++;						\
		 (iMats) += MAT_ALIGNER(struct MatsCompartment);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsSpringMass
{
    //m operator : HECCER_MOP_TRIPLEEXPONENTIAL

    int iOperator;

    //m time table next event

    int iEvent;

    double *pdEvents;

    //m discrete event mapper indices, -1 for none

    int iDiscreteTarget;

    //m index into sm tables

    int iTable;

    //m random activation frequency

    double dFrequency;
};

struct MatsSpringMass
{
    //m time to next event from source

    double dNextEvent;

    //m two activation values

    double dX;
    double dY;
/*     double dZ; */
};

#define SETMOP_SPRINGMASS(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,pdE,iDT,iT,dF) \
    ((pvMops)								\
     ? ({ struct MopsSpringMass *pmops = (struct MopsSpringMass *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_SPRINGMASS;			\
	     pmops->iEvent = (pdE) == NULL ? -1 : 0 ;			\
	     pmops->pdEvents = (pdE) ;					\
	     pmops->iDiscreteTarget = (iDT) ;				\
	     pmops->iTable = (iT) ;					\
	     pmops->dFrequency = (dF) ;					\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsSpringMass);		\
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )
     
#define SETMAT_SPRINGMASS(iMathComponent,piMC2Mat,ppvMatsIndex,iMatNumber,pvMats,iMats,dInitX,dInitY,dNE) \
    ((pvMats)								\
     ? ({ struct MatsSpringMass *pmats = (struct MatsSpringMass *)pvMats ; \
	     pmats->dX = (dInitX) ;					\
	     pmats->dY = (dInitY) ;					\
	     pmats->dNextEvent = (dNE) ;				\
	     ppvMatsIndex[iMatNumber++] = pvMats;			\
	     pvMats = (void *)&((struct MatsSpringMass *)pvMats)[1] ;	\
	     1;								\
	 })								\
     : (								\
	 (ppvMatsIndex)							\
	 ? ({								\
		 piMC2Mat[iMathComponent].iMat = iMatNumber++;		\
		 (iMats) += MAT_ALIGNER(struct MatsSpringMass);		\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsEventGenerate
{
    //m operator : HECCER_MOP_EVENTGENERATOR

    int iOperator;

    //m source, sentinel for membrane potential

    uMC2Mat uSource;

    //m threshold logic

    double dThreshold;

    double dRefractoryReset;

    //m index into target tables

    int iTable;
};

struct MatsEventGenerate
{
    //m refractory counter, negative means not in refractory period

    double dRefractory;

    //m spiking or not

    double dSpike;
};

#define SETMOP_EVENTGENERATE(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,iS,dT,dR,iT) \
    ((pvMops)								\
     ? ({ struct MopsEventGenerate *pmops = (struct MopsEventGenerate *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_EVENTGENERATE;		\
	     pmops->uSource.iMat = (iS) ;				\
	     pmops->dThreshold = (dT) ;					\
	     pmops->dRefractoryReset = (dR) ;				\
	     pmops->iTable = (iT) ;					\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsEventGenerate);	\
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )

#define SETMAT_EVENTGENERATE(iMathComponent,piMC2Mat,ppvMatsIndex,iMatNumber,pvMats,iMats,dR,dS) \
    ((pvMats)								\
     ? ({ struct MatsEventGenerate *pmats = (struct MatsEventGenerate *)pvMats ; \
	     pmats->dRefractory = (dR) ;				\
	     pmats->dSpike = (dS) ;					\
	     ppvMatsIndex[iMatNumber++] = pvMats;			\
	     pvMats = (void *)&((struct MatsEventGenerate *)pvMats)[1] ; \
	     1;								\
	 })								\
     : (								\
	 (ppvMatsIndex)							\
	 ? ({								\
		 piMC2Mat[iMathComponent].iMat = iMatNumber++;		\
		 (iMats) += MAT_ALIGNER(struct MatsEventGenerate);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )

struct MopsReset
{
    //m operator : HECCER_MOP_RESET

    int iOperator;

    //m reset value

    double dReset;
};

#define SETMOP_RESET(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,dR) \
    ((pvMops)								\
     ? ({ struct MopsReset *pmops = (struct MopsReset *)(pvMops);	\
	     pmops->iOperator = HECCER_MOP_RESET;			\
	     pmops->dReset = (dR) ;					\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsReset);		\
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )


struct MatsCallout
{
/*     double d; */

/*     //m the external solver (or glue to) */

/*     ExternalFunction *pfCall; */

    //m currently points to intermediary

    struct Callout *pco;
};

#define SETMOP_CALLOUT(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops)	\
    ((pvMops)							\
     ? ({ ((int *)pvMops)[0] = HECCER_MOP_CALLOUT;		\
	     ppvMopsIndex[iMopNumber++] = pvMops;		\
	     (pvMops) = (void *)&((int *)pvMops)[1];		\
	     1;							\
	 })							\
     : (							\
	 (ppvMopsIndex)						\
	 ? ({							\
		 piMC2Mop[iMathComponent] = iMopNumber++;	\
		 (iMops) += sizeof(int);			\
		 1;						\
	     })							\
	 : ({ iMopNumber++; 1; }) ) )

#define SETMAT_CALLOUT(iMathComponent,piMC2Mat,ppvMatsIndex,iMatNumber,pvMats,iMats,p)		\
    ((pvMats)								\
     ? ({ struct MatsCallout *pmats = (struct MatsCallout *)pvMats ;	\
	     pmats->pco = (p) ;						\
	     ppvMatsIndex[iMatNumber++] = pvMats;			\
	     pvMats = (void *)&((struct MatsCallout *)pvMats)[1] ;	\
	     1 ;							\
	 })								\
     : (								\
	 (ppvMatsIndex)							\
	 ? ({								\
		 piMC2Mat[iMathComponent].iMat = iMatNumber++;		\
		 (iMats) += MAT_ALIGNER(struct MatsCallout);		\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsInternalNernst
{
    //m operator : HECCER_MOP_INTERNALNERNST

    int iOperator;

    //m constant

    double dConstant;

    //m external concentration

    double dExternal;

    //m variable internal concentration

    uMC2Mat uInternal;
};


struct MatsInternalNernst
{
    //m nernst potential

    double dPotential;
};

#define SETMOP_INTERNALNERNST(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,dC,dE,iI)	\
    ((pvMops)								\
     ? ({ struct MopsInternalNernst *pmops = (struct MopsInternalNernst *)(pvMops);	\
	     pmops->iOperator = HECCER_MOP_INTERNALNERNST;		\
	     pmops->dConstant = (dC) ;					\
	     pmops->dExternal = (dE) ;					\
	     pmops->uInternal.iMat = (iI) ;				\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsInternalNernst);	\
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )
     
#define SETMAT_INTERNALNERNST(iMathComponent,piMC2Mat,ppvMatsIndex,iMatNumber,pvMats,iMats,dP) \
    ((pvMats)								\
     ? ({ struct MatsInternalNernst *pmats = (struct MatsInternalNernst *)pvMats ; \
	     pmats->dPotential = (dP) ;					\
	     ppvMatsIndex[iMatNumber++] = pvMats;			\
	     pvMats = (void *)&((struct MatsInternalNernst *)pvMats)[1] ; \
	     1;								\
	 })								\
     : (								\
	 (ppvMatsIndex)							\
	 ? ({								\
		 piMC2Mat[iMathComponent].iMat = iMatNumber++;		\
		 (iMats) += MAT_ALIGNER(struct MatsInternalNernst);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsInitializeChannel
{
    //m operation : HECCER_MOP_INITIALIZECHANNEL

    int iOperator;

    //m constant reversal potential

    double dReversalPotential;

    //m maximal channel conductance

    double dMaximalConductance;
};


#define SETMOP_INITIALIZECHANNEL(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,dG,dE) \
    ((pvMops)								\
     ? ({ struct MopsInitializeChannel *pmops = (struct MopsInitializeChannel *)(pvMops);	\
	     pmops->iOperator = HECCER_MOP_INITIALIZECHANNEL;		\
	     pmops->dReversalPotential = (dE) ;				\
	     pmops->dMaximalConductance = (dG) ;			\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 })								\
     : (								\
	 (ppvMopsIndex)							\
	 ? ({								\
		 piMC2Mop[iMathComponent] = iMopNumber++;		\
		 (iMops) += sizeof(struct MopsInitializeChannel);	\
		 1;							\
	     })								\
	 : ({ iMopNumber++; 1; }) ) )


struct MopsInitializeChannelErev
{
    //m operation : HECCER_MOP_INITIALIZECHANNELEK

    int iOperator;

    //m variable reversal potential

    uMC2Mat uReversalPotential;

    //m maximal channel conductance

    double dMaximalConductance;
};


#define SETMOP_INITIALIZECHANNELEK(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,dG,iE) \
    ((pvMops)								\
     ? ({ struct MopsInitializeChannelErev *pmops = (struct MopsInitializeChannelErev *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_INITIALIZECHANNELEREV;		\
	     pmops->uReversalPotential.iMat = (iE) ;			\
	     pmops->dMaximalConductance = (dG) ;			\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 })								\
     : (								\
	 (ppvMopsIndex)							\
	 ? ({								\
		 piMC2Mop[iMathComponent] = iMopNumber++;		\
		 (iMops) += sizeof(struct MopsInitializeChannelErev);	\
		 1;							\
	     })								\
	 : ({ iMopNumber++; 1; }) ) )


struct MopsStoreChannelConductance
{
    //m operator : HECCER_MOP_STORECHANNELCONDUCTANCE

    int iOperator;
};

//t needs to be renamed to MatsStoreChannelConductance

struct MatsStoreChannelConductance
{
    //m single channel conductance

    double dChannelConductance;
};

#define SETMOP_STORECHANNELCONDUCTANCE(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops) \
    ((pvMops)								\
     ? ({ struct MopsStoreChannelConductance *pmops = (struct MopsStoreChannelConductance *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_STORECHANNELCONDUCTANCE ;	\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsStoreChannelConductance); \
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )


struct MopsVoltageTableDependency
{
    //t so in principle the following operation is only needed once
    //t per compartment.  Still have to figure out how.

    //m operator : HECCER_MOP_LOADVOLTAGETABLE

    int iOperator;
};

#define SETMOP_LOADVOLTAGETABLE(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops)	\
    ((pvMops)								\
     ? ({ struct MopsVoltageTableDependency *pmops = (struct MopsVoltageTableDependency *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_LOADVOLTAGETABLE ;		\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsVoltageTableDependency); \
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )


struct MopsUpdateCompartmentCurrent
{
    //m operator : HECCER_MOP_UPDATECOMPARTMENTCURRENT

    int iOperator;
};

#define SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops) \
    ((pvMops)								\
     ? ({ struct MopsUpdateCompartmentCurrent *pmops = (struct MopsUpdateCompartmentCurrent *)(pvMops);	\
	     pmops->iOperator = HECCER_MOP_UPDATECOMPARTMENTCURRENT ;	\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsUpdateCompartmentCurrent); \
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )


struct MopsSingleGateConcept
{
    //m operator : HECCER_MOP_CONCEPTGATE

    int iOperator;

    //m table index

    int iTableIndex;

    //m power to apply

    int iPower;

    //m possibly solved dependence

    uMC2Mat uState;
};

#define SETMOP_POWEREDGATECONCEPT(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,iT,iP,iS) \
    ((pvMops)								\
     ? ({ struct MopsSingleGateConcept *pmops = (struct MopsSingleGateConcept *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_CONCEPTGATE ;		\
	     pmops->iTableIndex = (iT) ;				\
	     pmops->iPower = (iP) ;					\
	     pmops->uState.iMat = (iS) ;				\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     ((iP) <= 0)						\
		 ? ({							\
			 HeccerError					\
			     (pheccer,					\
			      NULL,					\
			      "gate power %i out of range",		\
			      (iP));					\
		     })							\
		 : ({ });						\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsSingleGateConcept);	\
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )


struct MatsSingleGateConcept
{
    //m gate activation

    double dActivation;
};

#define SETMAT_POWEREDGATECONCEPT(iMathComponent,piMC2Mat,ppvMatsIndex,iMatNumber,pvMats,iMats,dA) \
    ((pvMats)								\
     ?  ({ struct MatsSingleGateConcept *pmats = (struct MatsSingleGateConcept *)pvMats ; \
	     pmats->dActivation = (dA) ;				\
	     ppvMatsIndex[iMatNumber++] = pvMats;			\
	     pvMats = (void *)&((struct MatsSingleGateConcept *)pvMats)[1] ; \
	     1 ;							\
	 })								\
     : (								\
	 (ppvMatsIndex)							\
	 ? ({								\
		 piMC2Mat[iMathComponent].iMat = iMatNumber++;		\
		 (iMats) += MAT_ALIGNER(struct MatsSingleGateConcept);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


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

    //m possibly solved external flux contribution

    uMC2Mat puExternal[EXPONENTIALDECAY_CONTRIBUTORS];
};


struct MatsExponentialDecay
{
    //m resulting state

    double dState;
};

#define SETMOP_EXPONENTIALDECAY(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,dB,dS,dT,piE)	\
    ((pvMops)								\
     ? ({ struct MopsExponentialDecay *pmops = (struct MopsExponentialDecay *)(pvMops);	\
	     pmops->iOperator = HECCER_MOP_EXPONENTIALDECAY;		\
	     pmops->dBeta = (dB) ;					\
	     pmops->dSteadyState = (dS) ;				\
	     pmops->dTau = (dT) ;					\
	     int i;							\
	     for (i = 0 ; i < EXPONENTIALDECAY_CONTRIBUTORS ; i++)	\
	     {								\
		 pmops->puExternal[i].iMat = (piE)[i] ;			\
	     }								\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsExponentialDecay);	\
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )
     
#define SETMAT_EXPONENTIALDECAY(iMathComponent,piMC2Mat,ppvMatsIndex,iMatNumber,pvMats,iMats,dS) \
    ((pvMats)								\
     ? ({ struct MatsExponentialDecay *pmats = (struct MatsExponentialDecay *)pvMats ; \
	     pmats->dState = (dS) ;					\
	     ppvMatsIndex[iMatNumber++] = pvMats;			\
	     pvMats = (void *)&((struct MatsExponentialDecay *)pvMats)[1] ; \
	     1;								\
	 })								\
     : (								\
	 (ppvMatsIndex)							\
	 ? ({								\
		 piMC2Mat[iMathComponent].iMat = iMatNumber++;		\
		 (iMats) += MAT_ALIGNER(struct MatsExponentialDecay);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsFluxPool
{
    //m operator : HECCER_MOP_FLUXPOOL

    int iOperator;

/*     //m pool index */

/*     int iPool; */
};

struct MatsFluxPool
{
    //m resulting flux

    double dFlux;
};

#define SETMOP_FLUXPOOL(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops/* ,iP */)	\
    ((pvMops)								\
     ? ({ struct MopsFluxPool *pmops = (struct MopsFluxPool *)(pvMops);	\
	     pmops->iOperator = HECCER_MOP_FLUXPOOL;			\
	     /* pmops->iPool = (iP) ; */				\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsFluxPool);		\
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )

#define SETMAT_FLUXPOOL(iMathComponent,piMC2Mat,ppvMatsIndex,iMatNumber,pvMats,iMats,dF)	\
    ((pvMats)								\
     ? ({ struct MatsFluxPool *pmats = (struct MatsFluxPool *)pvMats ;	\
	     pmats->dFlux = (dF) ;					\
	     ppvMatsIndex[iMatNumber++] = pvMats;			\
	     pvMats = (void *)&((struct MatsFluxPool *)pvMats)[1] ;	\
	     1;								\
	 }) : (								\
	     (ppvMatsIndex)						\
	     ? ({							\
		     piMC2Mat[iMathComponent].iMat = iMatNumber++;	\
		     (iMats) += MAT_ALIGNER(struct MatsFluxPool);	\
		     1;							\
		 })							\
	     : ({ iMatNumber++; 1; }) ) )


struct MopsRegisterChannelCurrent
{
    //m operator : HECCER_MOP_REGISTERCHANNELCURRENT

    int iOperator;
};

#define SETMOP_REGISTERCHANNELCURRENT(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops) \
    ((pvMops)								\
     ? ({ struct MopsRegisterChannelCurrent *pmops = (struct MopsRegisterChannelCurrent *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_REGISTERCHANNELCURRENT ;	\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsRegisterChannelCurrent); \
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )


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
#define HECCER_MOP_INTERNALNERNST 27
#define HECCER_MOP_INITIALIZECHANNELEREV 28
#define HECCER_MOP_SPRINGMASS 29
#define HECCER_MOP_EVENTGENERATE 31
#define HECCER_MOP_RESET 32

#define HECCER_MOP_UPDATECOMPARTMENTCURRENT 40


//d all operators for mechanisms have an opcode larger than ...

//t but perhaps this should be done using flags, not sure.

#define HECCER_MOP_COMPARTMENT_BARRIER 9


//f prototypes

int
HeccerVMDump
(struct VM *pvm, FILE *pfile, int iSelection);


#endif


