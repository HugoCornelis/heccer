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


#ifndef HECCER_HECCER_H
#define HECCER_HECCER_H


#include <stdio.h>


struct Heccer;


#include "eventdistributor.h"
#include "intermediary.h"
#include "indexers.h"
#include "service.h"
#include "table.h"
#include "vm.h"


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


//s global options

struct HeccerOptions
{
    //m global options and operation mode.

    int iOptions;

    //m interval has been set ?

    int iIntervalSet;

    //m discretized gate, membrane potential, interval start

    double dIntervalStart;

    //m discretized gate, membrane potential, interval end

    double dIntervalEnd;

    //m activator has been set ?

    int iActivatorSet;

    //m discretized gate, concentration, interval start

    double dConcentrationGateStart;

    //m discretized gate, concentration, interval end

    double dConcentrationGateEnd;

    //m discretized gate, membrane, number of entries

    int iIntervalEntries;

    //m pre interpolation table size, legacy from genesis tabchans

    int iSmallTableSize;
};


//d logical branch grouping for solution matrix :
//d schedules first a leave and all attached compartments until a
//d branch point.  When disabled, all the leaves are scheduled first,
//d next the compartments attached to the leaves, etc.

#define HECCER_OPTION_BRANCHES_FIRST_SCHEDULING		1

//d use backward euler, default is crank-nicolson

#define HECCER_OPTION_BACKWARD_EULER			2

//d simulate as a passive model, with synchans (springmass)

#define HECCER_OPTION_PASSIVE_SYNCHANS			4

//d enable computation of individual currents and conductances

//! so by default the contribution of each channel to the overall
//! compartmental current is computed, when this option is turned on,
//! only the integrated current is computed.  Same for conductance.

#define HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS	32

//d enable compilation and execution of aggregator operators

#define HECCER_OPTION_ENABLE_AGGREGATORS 64


//d discretized gate, interval start

#define HECCER_INTERVAL_DEFAULT_START			(-0.1)

//d discretized gate, interval end

#define HECCER_INTERVAL_DEFAULT_END			(0.05)

//d concentration gate, interval end

#define HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_START	(0.00004)

//d concentration gate, interval end

#define HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_END	(0.300)

//d discretized gate, number of entries

#define HECCER_INTERVAL_DEFAULT_ENTRIES			3000

//d discretized gate, number of entries before interpolation

#define HECCER_INTERPOL_INTERVAL_DEFAULT_ENTRIES	149

//s heccer main structure

struct Heccer
{
    //m name of this heccer

    //! if the name of a heccer is a system wide id depends on the
    //! environment, heccer does not (and cannot) enforce it.

    char *pcName;

    //m status : reflects phases of compilation.

    int iStatus;

    int iErrorCount;

    //m options

    struct HeccerOptions ho;

    //m current time

    double dTime;

    //m time step

    double dStep;

    //m identification service : translates serials to math components.

    //! so to use this feature: define your translation service, and
    //! set it during the construction of your heccer.

    //! wouldn't be surprised that I need several layers of services,
    //! will see if that has repercussion at this low level or not.
    //!
    //! for the moment we have a function layer, which is fixed, and
    //! a data layer, which is opaque.  The function layer defines the
    //! real interface.

    struct TranslationService *pts;

    //m event distribution service: given an event, distributes it over the targets

    //! so to use this feature: define your event distribution service, and
    //! set it during the construction of your heccer.

    //! wouldn't be surprised that I need several layers of services,
    //! will see if that has repercussion at this low level or not.
    //!
    //! for the moment we have a function layer, which is fixed, and
    //! a data layer, which is opaque.  The function layer defines the
    //! real interface.

    struct EventDistributor *ped;

    //m event reception service: receive an event, and queue till it fires

    //! so to use this feature: define your event reception service, and
    //! set it during the construction of your heccer.

    //! wouldn't be surprised that I need several layers of services,
    //! will see if that has repercussion at this low level or not.
    //!
    //! for the moment we have a function layer, which is fixed, and
    //! a data layer, which is opaque.  The function layer defines the
    //! real interface.

    struct EventQueuer *peq;

    //m intermediary

    struct Intermediary inter;

    //m indexing structures

    struct Indexers indexers;

    //m tabulated gates and rearranged gates

    struct TabulatedGateTable tgt;

    //m tabulated spring mass channels

    struct TabulatedSpringMassTable tsmt;

    //m vm

    struct VM vm;

};


//d brandnew allocated, nothing done

#define HECCER_STATUS_PHASE_0		0

//d correctly initialized

#define HECCER_STATUS_PHASE_1		10

//d intermediary has been built

#define HECCER_STATUS_PHASE_2		20

//d byte has been compiled

#define HECCER_STATUS_PHASE_3		30

//d initial values have been put in place

#define HECCER_STATUS_PHASE_4		40

//d heccs have been done, further status unknown

#define HECCER_STATUS_PHASE_5		50


//f prototypes

int HeccerAggregatorsCompile(struct Heccer *pheccer);

int HeccerCanCompile(struct Heccer *pheccer);

int HeccerCompileP1(struct Heccer *pheccer);

int HeccerCompileP2(struct Heccer *pheccer);

int HeccerCompileP3(struct Heccer *pheccer);

int HeccerDumpV(struct Heccer *pheccer);

int HeccerDump(struct Heccer *pheccer, FILE *pfile, int iSelection);

#define HECCER_DUMP_ALL (0xffffffff & ~HECCER_DUMP_SERVICE)

#define HECCER_DUMP_SERVICE					(1 << 7)

#define HECCER_DUMP_INDEXERS_SUMMARY				(1 << 8)
#define HECCER_DUMP_INDEXERS_STRUCTURE				(1 << 9)

#define HECCER_DUMP_INTERMEDIARY_COMPARTMENTS_PARAMETERS	(1 << 1)
#define HECCER_DUMP_INTERMEDIARY_COMPARTMENT_SUMMARY		(1 << 2)
#define HECCER_DUMP_INTERMEDIARY_MECHANISM_SUMMARY		(1 << 3)
#define HECCER_DUMP_INTERMEDIARY_STRUCTURE			(1 << 4)
#define HECCER_DUMP_INTERMEDIARY_SUMMARY			(1 << 5)

#define HECCER_DUMP_TABLE_GATE_SUMMARY				(1 << 12)
#define HECCER_DUMP_TABLE_GATE_TABLES				(1 << 13)

#define HECCER_DUMP_VM_COMPARTMENT_MATRIX			(1 << 16)
#define HECCER_DUMP_VM_COMPARTMENT_DATA				(1 << 17)
#define HECCER_DUMP_VM_COMPARTMENT_OPERATIONS			(1 << 18)
#define HECCER_DUMP_VM_MECHANISM_DATA				(1 << 19)
#define HECCER_DUMP_VM_MECHANISM_OPERATIONS			(1 << 20)
#define HECCER_DUMP_VM_CHANNEL_POOL_FLUXES			(1 << 21)
#define HECCER_DUMP_VM_SUMMARY					(1 << 22)

#define HECCER_DUMP_VM_AGGREGATORS				(1 << 25)


char * HeccerGetVersion(void);

int HeccerError(struct Heccer *pheccer, char *pcContext, char *pcError, ...);

/* int HeccerHecc(struct Heccer *pheccer); */

int HeccerHeccs(struct Heccer *pheccer, double dTime);

int HeccerInitiate(struct Heccer *pheccer);

struct Heccer *
HeccerNew
(char *pc,
 struct TranslationService *pts,
 struct EventDistributor *ped,
 struct EventQueuer *peq);

struct Heccer *
HeccerNewP1
(char *pc,
 struct TranslationService *pts,
 struct EventDistributor *ped,
 struct EventQueuer *peq,
 int iOptions,
 double dStep);

struct Heccer *HeccerNewP2(char *pc, struct Intermediary *pinter);


#endif


