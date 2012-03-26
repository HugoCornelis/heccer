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


typedef struct
{
    /// index into mathcomponents

    int iMat;

    /// direct value

    double *pdValue;

}
    uMC2Mat;

/// \struct vm related (name subject to change)

struct VM
{
    /// number of compartments

    int iCompartments;

    /// compartment operations

    int iCops;

    int *piCops;

    /// compartment data

    int iDiagonals;

    double *pdDiagonals;

    int iAxres;

    double *pdAxres;

    /// results

    int iResults;

    double *pdResults;

    /// \todo pdVm is accessible from outside, so should be moved to a
    /// \todo separate place ?
    /// \todo will become clear when addressing gets in place.

    int iVms;

    double *pdVms;

    /// number of math components

    int iMathComponents;

    /// math component number to mat number convertor

    /// \note note that this one does not index compartments, only the mechanism math components.

    uMC2Mat *piMC2Mat;

    /// math component number to mop number convertor

    int *piMC2Mop;

    /// mechanism operations

    int iMopNumber;

    int iMops;

    void *pvMops;

    /// mechanism addressables

    /// \todo same as for pdVms applies, see above.

    int iMatNumber;

    int iMats;

    double *pdMats;

    /// indexing from mops or mats number towards one of the above

    double **ppdCMatsIndex;

    void **ppvMopsIndex;

    double **ppdMatsIndex;

    /// all aggregators: derived variables not directly available from a model's viewpoint

    /// aggregate currents etc.

    int iAggregators;

    double *pdAggregators;

/*     /// fluxes link channels and pools */

/*     int iFluxes; */

/*     double *pdFluxes; */

/*     /// concentrations link pools and channels */

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

/// \todo can be automated by taking an array and diffing casted to char *
/// \todo pointers to sequent entries ?

#define ALIGNER8(s) ((((sizeof(s) - 1) >> 3) + 1) << 3)

#define ALIGNER4(s) ((((sizeof(s) - 1) >> 2) + 1) << 2)

/// \def mats are aligned to 8 bytes

#define MAT_ALIGNER ALIGNER8


struct MatsCompartment
{
    double dLeak;
    double dInjected;
    double dCapacity;
    double dDiagonal;
};


#if (USE_ID_DISASSEM)

#define SETMOP_COMPARTMENT(ppvMopsIndex,pmc,iMopNumber,pvMops,iMops)	\
    ((pvMops)								\
     ? ({								\
	     iLoadVoltageTable = 0;					\
	     ((int *)pvMops)[0] = HECCER_MOP_COMPARTMENT;		\
	     (pvMops) = (void *)&((int *)pvMops)[1];			\
	     ((int *)pvMops)[0] = (pmc)->iSerial;			\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&((int *)pvMops)[1];			\
	     1;								\
	 })								\
     : (								\
	 (ppvMopsIndex)							\
	 ? ({								\
		 iLoadVoltageTable = 0;					\
		 iMopNumber++;						\
		 (iMops) += sizeof(int);				\
		 (iMops) += sizeof(int);				\
		 1;							\
	     })								\
	 : ({								\
		 iLoadVoltageTable = 0;					\
		 iMopNumber++;						\
		 1;							\
	     }) ) )

#else

#define SETMOP_COMPARTMENT(ppvMopsIndex,pmc,iMopNumber,pvMops,iMops)	\
    ((pvMops)								\
     ? ({								\
	     iLoadVoltageTable = 0;					\
	     ((int *)pvMops)[0] = HECCER_MOP_COMPARTMENT;		\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&((int *)pvMops)[1];			\
	     1;								\
	 })								\
     : (								\
	 (ppvMopsIndex)							\
	 ? ({								\
		 iLoadVoltageTable = 0;					\
		 iMopNumber++;						\
		 (iMops) += sizeof(int);				\
		 1;							\
	     })								\
	 : ({								\
		 iLoadVoltageTable = 0;					\
		 iMopNumber++;						\
		 1;							\
	     }) ) )

#endif


#define SETMAT_COMPARTMENT(ppdCMatsIndex,iCNumber,ppdMatsIndex,iMatNumber,pdMats,iMats,dL,dI,dC,dD) \
    ((pdMats)								\
     ? ({ struct MatsCompartment *pmats = (struct MatsCompartment *)pdMats ; \
	     pmats->dLeak = (dL) ; pmats->dInjected = (dI) ;		\
	     pmats->dCapacity = (dC) ;					\
	     pmats->dDiagonal = (dD) ;					\
	     ppdCMatsIndex[iCNumber] = pdMats;				\
	     ppdMatsIndex[iMatNumber++] = pdMats;			\
	     pdMats = (void *)&((struct MatsCompartment *)pdMats)[1] ;	\
	     1 ;							\
	 })								\
     : (								\
	 (ppdMatsIndex)							\
	 ? ({								\
		 iMatNumber++;						\
		 (iMats) += MAT_ALIGNER(struct MatsCompartment);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsSpringMass
{
    /// operator : HECCER_MOP_TRIPLEEXPONENTIAL

    int iOperator;

    /// time table next event

    int iEvent;

    double *pdEvents;

    /// discrete event mapper indices, -1 for none

    int iDiscreteTarget;

    /// index into sm tables

    int iTable;

};

struct MatsSpringMass
{
    /// time to next event from source

    double dNextEvent;

    /// two activation values

    double dX;
    double dY;
/*     double dZ; */

    /// random activation frequency

    double dFrequency;
};

#define SETMOP_SPRINGMASS(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,pdE,iDT,iT) \
    ((pvMops)								\
     ? ({ struct MopsSpringMass *pmops = (struct MopsSpringMass *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_SPRINGMASS;			\
	     pmops->iEvent = (pdE) == NULL ? -1 : 0 ;			\
	     pmops->pdEvents = (pdE) ;					\
	     pmops->iDiscreteTarget = (iDT) ;				\
	     pmops->iTable = (iT) ;					\
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
     
#define SETMAT_SPRINGMASS(iMathComponent,piMC2Mat,ppdMatsIndex,iMatNumber,pdMats,iMats,dInitX,dInitY,dNE,dF) \
    ((pdMats)								\
     ? ({ struct MatsSpringMass *pmats = (struct MatsSpringMass *)pdMats ; \
	     pmats->dX = (dInitX) ;					\
	     pmats->dY = (dInitY) ;					\
	     pmats->dNextEvent = (dNE) ;				\
	     pmats->dFrequency = (dF) ;					\
	     ppdMatsIndex[iMatNumber++] = pdMats;			\
	     pdMats = (void *)&((struct MatsSpringMass *)pdMats)[1] ;	\
	     1;								\
	 })								\
     : (								\
	 (ppdMatsIndex)							\
	 ? ({								\
		 ((piMC2Mat[iMathComponent].iMat == -1)			\
		  ? (piMC2Mat[iMathComponent].iMat = iMatNumber)	\
		  : (piMC2Mat[iMathComponent].iMat = iMatNumber));	\
		 iMatNumber++;						\
		 (iMats) += MAT_ALIGNER(struct MatsSpringMass);		\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsEventGenerate
{
    /// operator : HECCER_MOP_EVENTGENERATOR

    int iOperator;

    /// source, sentinel for membrane potential

    uMC2Mat uSource;

    /// threshold logic

    double dThreshold;

    double dRefractoryReset;

    /// index into target tables

    int iSource2Targets;
};

struct MatsEventGenerate
{
    /// refractory counter, negative means not in refractory period

    double dRefractory;

    /// spiking or not

    double dSpike;
};

#define SETMOP_EVENTGENERATE(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,iS,dT,dR,iT) \
    ((pvMops)								\
     ? ({ struct MopsEventGenerate *pmops = (struct MopsEventGenerate *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_EVENTGENERATE;		\
	     pmops->uSource.iMat = (iS) ;				\
	     pmops->dThreshold = (dT) ;					\
	     pmops->dRefractoryReset = (dR) ;				\
	     pmops->iSource2Targets = (iT) ;				\
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

#define SETMAT_EVENTGENERATE(iMathComponent,piMC2Mat,ppdMatsIndex,iMatNumber,pdMats,iMats,dR,dS) \
    ((pdMats)								\
     ? ({ struct MatsEventGenerate *pmats = (struct MatsEventGenerate *)pdMats ; \
	     pmats->dRefractory = (dR) ;				\
	     pmats->dSpike = (dS) ;					\
	     ppdMatsIndex[iMatNumber++] = pdMats;			\
	     pdMats = (void *)&((struct MatsEventGenerate *)pdMats)[1] ; \
	     1;								\
	 })								\
     : (								\
	 (ppdMatsIndex)							\
	 ? ({								\
		 ((piMC2Mat[iMathComponent].iMat == -1)			\
		  ? (piMC2Mat[iMathComponent].iMat = iMatNumber)	\
		  : (piMC2Mat[iMathComponent].iMat = iMatNumber));	\
		 iMatNumber++;						\
		 (iMats) += MAT_ALIGNER(struct MatsEventGenerate);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )

struct MopsReset
{
    /// operator : HECCER_MOP_RESET

    int iOperator;

    /// reset value

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

/*     /// the external solver (or glue to) */

/*     ExternalFunction *pfCall; */

    /// currently points to intermediary

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

#define SETMAT_CALLOUT(iMathComponent,piMC2Mat,ppdMatsIndex,iMatNumber,pdMats,iMats,p)		\
    ((pdMats)								\
     ? ({ struct MatsCallout *pmats = (struct MatsCallout *)pdMats ;	\
	     pmats->pco = (p) ;						\
	     ppdMatsIndex[iMatNumber++] = pdMats;			\
	     pdMats = (void *)&((struct MatsCallout *)pdMats)[1] ;	\
	     1 ;							\
	 })								\
     : (								\
	 (ppdMatsIndex)							\
	 ? ({								\
		 ((piMC2Mat[iMathComponent].iMat == -1)			\
		  ? (piMC2Mat[iMathComponent].iMat = iMatNumber)	\
		  : (piMC2Mat[iMathComponent].iMat = iMatNumber));	\
		 iMatNumber++;						\
		 (iMats) += MAT_ALIGNER(struct MatsCallout);		\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsInternalNernst
{
    /// operator : HECCER_MOP_INTERNALNERNST

    int iOperator;

    /// constant

    double dConstant;

    /// external concentration

    double dExternal;

    /// variable internal concentration

    uMC2Mat uInternal;
};


struct MatsInternalNernst
{
    /// nernst potential

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
     
#define SETMAT_INTERNALNERNST(iMathComponent,piMC2Mat,ppdMatsIndex,iMatNumber,pdMats,iMats,dP) \
    ((pdMats)								\
     ? ({ struct MatsInternalNernst *pmats = (struct MatsInternalNernst *)pdMats ; \
	     pmats->dPotential = (dP) ;					\
	     ppdMatsIndex[iMatNumber++] = pdMats;			\
	     pdMats = (void *)&((struct MatsInternalNernst *)pdMats)[1] ; \
	     1;								\
	 })								\
     : (								\
	 (ppdMatsIndex)							\
	 ? ({								\
		 ((piMC2Mat[iMathComponent].iMat == -1)			\
		  ? (piMC2Mat[iMathComponent].iMat = iMatNumber)	\
		  : (piMC2Mat[iMathComponent].iMat = iMatNumber));	\
		 iMatNumber++;						\
		 (iMats) += MAT_ALIGNER(struct MatsInternalNernst);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsInitializeChannel
{
    /// operation : HECCER_MOP_INITIALIZECHANNEL

    int iOperator;

    /// constant reversal potential

    double dReversalPotential;

    /// maximal channel conductance

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
    /// operation : HECCER_MOP_INITIALIZECHANNELEK

    int iOperator;

    /// variable reversal potential

    uMC2Mat uReversalPotential;

    /// maximal channel conductance

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
    /// operator : HECCER_MOP_STORECHANNELCONDUCTANCE

    int iOperator;
};

/// \todo needs to be renamed to MatsStoreChannelConductance

struct MatsStoreChannelConductance
{
    /// single channel conductance

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
    /// operator : HECCER_MOP_LOADVOLTAGETABLE

    int iOperator;
};

#define SETMOP_LOADVOLTAGETABLE(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops)	\
    ((iLoadVoltageTable == 0)						\
     ? ((pvMops)							\
	? ({								\
		iLoadVoltageTable = 1;					\
		struct MopsVoltageTableDependency *pmops = (struct MopsVoltageTableDependency *)(pvMops); \
		pmops->iOperator = HECCER_MOP_LOADVOLTAGETABLE ;	\
		ppvMopsIndex[iMopNumber++] = pvMops;			\
		(pvMops) = (void *)&pmops[1];				\
		1;							\
	    }) : (							\
		(ppvMopsIndex)						\
		? ({							\
			iLoadVoltageTable = 1;				\
			piMC2Mop[iMathComponent] = iMopNumber++;	\
			(iMops) += sizeof(struct MopsVoltageTableDependency); \
			1;						\
		    })							\
		: ({							\
			iLoadVoltageTable = 1;				\
			iMopNumber++;					\
			1;						\
		    })							\
		) )							\
     : (1))


struct MopsUpdateCompartmentCurrent
{
    /// operator : HECCER_MOP_UPDATECOMPARTMENTCURRENT

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
    /// operator : HECCER_MOP_CONCEPTGATE

    int iOperator;

    /// table index

    int iTableIndex;

    /// power to apply

    int iPower;

    /// possibly solved dependence

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
	     ((iP) > 6 || (iP) < -6)					\
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
    /// gate activation

    double dActivation;
};

#define SETMAT_POWEREDGATECONCEPT(iMathComponent,piMC2Mat,ppdMatsIndex,iMatNumber,pdMats,iMats,dA) \
    ((pdMats)								\
     ?  ({ struct MatsSingleGateConcept *pmats = (struct MatsSingleGateConcept *)pdMats ; \
	     pmats->dActivation = (dA) ;				\
	     ppdMatsIndex[iMatNumber++] = pdMats;			\
	     pdMats = (void *)&((struct MatsSingleGateConcept *)pdMats)[1] ; \
	     1 ;							\
	 })								\
     : (								\
	 (ppdMatsIndex)							\
	 ? ({								\
		 ((piMC2Mat[iMathComponent].iMat == -1)			\
		  ? (piMC2Mat[iMathComponent].iMat = iMatNumber)	\
		  : (piMC2Mat[iMathComponent].iMat = iMatNumber));	\
		 iMatNumber++;						\
		 (iMats) += MAT_ALIGNER(struct MatsSingleGateConcept);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsExponentialDecay
{
    /// operator : HECCER_MOP_EXPONENTIALDECAY

    int iOperator;

    /// beta

    double dBeta;

    /// steady state

    double dSteadyState;

    /// tau

    double dTau;

    /// possibly solved external flux contribution

    uMC2Mat puExternal[EXPONENTIALDECAY_CONTRIBUTORS];
};


struct MatsExponentialDecay
{
    /// resulting state

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
     
#define SETMAT_EXPONENTIALDECAY(iMathComponent,piMC2Mat,ppdMatsIndex,iMatNumber,pdMats,iMats,dS) \
    ((pdMats)								\
     ? ({ struct MatsExponentialDecay *pmats = (struct MatsExponentialDecay *)pdMats ; \
	     pmats->dState = (dS) ;					\
	     ppdMatsIndex[iMatNumber++] = pdMats;			\
	     pdMats = (void *)&((struct MatsExponentialDecay *)pdMats)[1] ; \
	     1;								\
	 })								\
     : (								\
	 (ppdMatsIndex)							\
	 ? ({								\
		 ((piMC2Mat[iMathComponent].iMat == -1)			\
		  ? (piMC2Mat[iMathComponent].iMat = iMatNumber)	\
		  : (piMC2Mat[iMathComponent].iMat = iMatNumber));	\
		 iMatNumber++;						\
		 (iMats) += MAT_ALIGNER(struct MatsExponentialDecay);	\
		 1;							\
	     })								\
	 : ({ iMatNumber++; 1; }) ) )


struct MopsFluxPool
{
    /// operator : HECCER_MOP_FLUXPOOL

    int iOperator;

/*     /// pool index */

/*     int iPool; */
};

struct MatsFluxPool
{
    /// resulting flux

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

#define SETMAT_FLUXPOOL(iMathComponent,piMC2Mat,ppdMatsIndex,iMatNumber,pdMats,iMats,dF)	\
    ((pdMats)								\
     ? ({ struct MatsFluxPool *pmats = (struct MatsFluxPool *)pdMats ;	\
	     pmats->dFlux = (dF) ;					\
	     ppdMatsIndex[iMatNumber++] = pdMats;			\
	     pdMats = (void *)&((struct MatsFluxPool *)pdMats)[1] ;	\
	     1;								\
	 }) : (								\
	     (ppdMatsIndex)						\
	     ? ({							\
		     ((piMC2Mat[iMathComponent].iMat == -1)		\
		      ? (piMC2Mat[iMathComponent].iMat = iMatNumber)	\
		      : (piMC2Mat[iMathComponent].iMat = iMatNumber));	\
		     iMatNumber++;					\
		     (iMats) += MAT_ALIGNER(struct MatsFluxPool);	\
		     1;							\
		 })							\
	     : ({ iMatNumber++; 1; }) ) )


struct MopsRegisterChannelCurrent
{
    /// operator : HECCER_MOP_REGISTERCHANNELCURRENT

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


struct MopsStoreSingleChannelCurrent
{
    /// operator : HECCER_MOP_STORESINGLECHANNELCURRENT

    int iOperator;
};

struct MatsStoreSingleChannelCurrent
{
    /// single channel conductance

    double dConductance;

    /// single channel current

    double dCurrent;

};

#define SETMOP_STORESINGLECHANNELCURRENT(iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops) \
    ((pvMops)								\
     ? ({ struct MopsStoreSingleChannelCurrent *pmops = (struct MopsStoreSingleChannelCurrent *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_STORESINGLECHANNELCURRENT ;	\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsStoreSingleChannelCurrent); \
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )

#define SETMAT_STORESINGLECHANNELCURRENT(iMathComponent,piMC2Mat,ppdMatsIndex,iMatNumber,pdMats,iMats,dCo,dCu) \
    ((pdMats)								\
     ? ({ struct MatsStoreSingleChannelCurrent *pmats = (struct MatsStoreSingleChannelCurrent *)pdMats ; \
	     pmats->dConductance = (dCo) ;				\
	     pmats->dCurrent = (dCu) ;					\
	     ppdMatsIndex[iMatNumber++] = pdMats;			\
	     pdMats = (void *)&((struct MatsStoreSingleChannelCurrent *)pdMats)[1] ; \
	     1;								\
	 }) : (								\
	     (ppdMatsIndex)						\
	     ? ({							\
		     ((piMC2Mat[iMathComponent].iMat == -1)		\
		      ? (piMC2Mat[iMathComponent].iMat = iMatNumber)	\
		      : (piMC2Mat[iMathComponent].iMat = iMatNumber));	\
		     iMatNumber++;					\
		     (iMats) += MAT_ALIGNER(struct MatsStoreSingleChannelCurrent); \
		     1;							\
		 })							\
	     : ({ iMatNumber++; 1; }) ) )


struct MopsAggregateCurrent
{
    /// operator : HECCER_MOP_AGGREGATECURRENT

    int iOperator;

    /// index into the aggregate results array

    int iIndex;
};

#define SET_AGGREGATOR_MAX(pvm,iAggregator) ((pvm)->iAggregators <= iAggregator ? ((pvm)->iAggregators = iAggregator + 1) : (0))

#define SETMOP_AGGREGATECURRENT(pvm,iMathComponent,piMC2Mop,ppvMopsIndex,iMopNumber,pvMops,iMops,iAggregator) \
    ((pvMops)								\
     ? ({ struct MopsAggregateCurrent *pmops = (struct MopsAggregateCurrent *)(pvMops); \
	     pmops->iOperator = HECCER_MOP_AGGREGATECURRENT ;		\
	     pmops->iIndex = iAggregator ;				\
	     ppvMopsIndex[iMopNumber++] = pvMops;			\
	     (pvMops) = (void *)&pmops[1];				\
	     SET_AGGREGATOR_MAX((pvm),(iAggregator));			\
	     1;								\
	 }) : (								\
	     (ppvMopsIndex)						\
	     ? ({							\
		     piMC2Mop[iMathComponent] = iMopNumber++;		\
		     (iMops) += sizeof(struct MopsAggregateCurrent);	\
		     1;							\
		 })							\
	     : ({ iMopNumber++; 1; }) ) )


/// \def operations for compartments

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


/// \def operations for mechanisms

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
#define HECCER_MOP_STORESINGLECHANNELCURRENT 41

#define HECCER_MOP_AGGREGATECURRENT 60


/// \def all operators for mechanisms have an opcode larger than ...

/// \todo but perhaps this should be done using flags, not sure.

#define HECCER_MOP_COMPARTMENT_BARRIER 9



int
HeccerVMDumpOperations
(struct VM *pvm, FILE *pfile, int iSelection);

int
HeccerVMDump
(struct VM *pvm, FILE *pfile, int iSelection);


#endif


