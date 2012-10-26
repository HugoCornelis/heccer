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


#define USE_ENABLE_LINEAR_MODE


struct simobj_Heccer;


#include "des.h"
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


/// \struct global options

struct HeccerOptions
{
    /// global options and operation mode.

    int iOptions;

    /// software corrections to the operation mode.

    int iCorrections;

    /// interval has been set ?

    int iIntervalSet;

    /// discretized gate, membrane potential, interval start

    double dIntervalStart;

    /// discretized gate, membrane potential, interval end

    double dIntervalEnd;

    /// activator has been set ?

    int iActivatorSet;

    /// discretized gate, concentration, interval start

    double dConcentrationGateStart;

    /// discretized gate, concentration, interval end

    double dConcentrationGateEnd;

    /// discretized gate, membrane, number of entries

    int iIntervalEntries;

    /// pre interpolation table size, legacy from genesis tabchans

    int iSmallTableSize;
};


/// \def logical branch grouping for solution matrix :
/// \def schedules first a leave and all attached compartments until a
/// \def branch point.  When disabled, all the leaves are scheduled first,
/// \def next the compartments attached to the leaves, etc.

#define HECCER_OPTION_BRANCHES_FIRST_SCHEDULING		1

/// \def use backward euler, default is crank-nicolson

#define HECCER_OPTION_BACKWARD_EULER			2

/// \def simulate as a passive model, with synchans (springmass)

#define HECCER_OPTION_PASSIVE_SYNCHANS			4

/// \def enable serialization at finish

#define HECCER_OPTION_SERIALIZE_AT_FINISH		8

/// \def enable computation of individual currents and conductances

/// \note so by default the contribution of each channel to the overall
/// \note compartmental current is computed, when this option is turned on,
/// \note only the integrated current is computed.  Same for conductance.

#define HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS	32

/// \def enable compilation and execution of aggregator operators

#define HECCER_OPTION_ENABLE_AGGREGATORS 64


#ifdef USE_ENABLE_LINEAR_MODE

/// \def recalc compartment diameters and lengths of linear cables for improved accuracy

#define HECCER_OPTION_ENABLE_LINEAR_MODE 128

/// \def says if HECCER_OPTION_ENABLE_LINEAR_MODE has been applied

#define HECCER_OPTION_ENABLE_LINEAR_MODE_APPLIED 256

/// \def says that HECCER_OPTION_ENABLE_LINEAR_MODE has been disabled
/// because it cannot deal with this model structure or its values.

#define HECCER_CORRECTION_ENABLE_LINEAR_MODE_DISABLED 1

#endif


/// \def discretized gate, interval start

#define HECCER_INTERVAL_DEFAULT_START			(-0.1)

/// \def discretized gate, interval end

#define HECCER_INTERVAL_DEFAULT_END			(0.05)

/// \def concentration gate, interval end

#define HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_START	(0.00004)

/// \def concentration gate, interval end

#define HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_END	(0.300)

/// \def discretized gate, number of entries

#define HECCER_INTERVAL_DEFAULT_ENTRIES			3000

/// \def discretized gate, number of entries before interpolation

#define HECCER_INTERPOL_INTERVAL_DEFAULT_ENTRIES	149

/// \struct heccer main structure

struct simobj_Heccer
{
    /// name of this heccer

    /// \note whether the name of a heccer is a system wide id depends
    /// on the environment, heccer does not (and cannot) enforce it.

    char *pcName;

    /// status : reflects phases of compilation.

    int iStatus;

    int iErrorCount;

    /// options

    struct HeccerOptions ho;

    /// current time

    double dTime;

    /// time step

    double dStep;

    /// identification service : translates serials to math components.

    /// \note so to use this feature: define your translation service, and
    /// \note set it during the construction of your heccer.

    /// \note wouldn't be surprised that I need several layers of services,
    /// \note will see if that has repercussion at this low level or not.
    ///
    /// \note for the moment we have a function layer, which is fixed, and
    /// \note a data layer, which is opaque.  The function layer defines the
    /// \note real interface.

    struct TranslationService *pts;

    /// event distribution service: given an event, distributes it over the targets

    /// \note so to use this feature: define your event distribution service, and
    /// \note set it during the construction of your heccer.

    /// \note wouldn't be surprised that I need several layers of services,
    /// \note will see if that has repercussion at this low level or not.
    ///
    /// \note for the moment we have a function layer, which is fixed, and
    /// \note a data layer, which is opaque.  The function layer defines the
    /// \note real interface.

    struct EventDistributor *ped;

    /// event reception service: receive an event, and queue till it fires

    /// \note so to use this feature: define your event reception service, and
    /// \note set it during the construction of your heccer.

    /// \note wouldn't be surprised that I need several layers of services,
    /// \note will see if that has repercussion at this low level or not.
    ///
    /// \note for the moment we have a function layer, which is fixed, and
    /// \note a data layer, which is opaque.  The function layer defines the
    /// \note real interface.

    struct EventQueuer *peq;

    /// intermediary

    struct Intermediary inter;

    /// indexing structures

    struct Indexers indexers;

    /// tabulated gates and rearranged gates

    struct TabulatedGateTable tgt;

    /// tabulated spring mass channels

    struct TabulatedSpringMassTable tsmt;

    /// vm

    struct VM vm;

};


/// \def brandnew allocated, nothing done

#define HECCER_STATUS_PHASE_0		0

/// \def correctly initialized

#define HECCER_STATUS_PHASE_1		10

/// \def intermediary has been built

#define HECCER_STATUS_PHASE_2		20

/// \def byte has been compiled

#define HECCER_STATUS_PHASE_3		30

/// \def initial values have been put in place

#define HECCER_STATUS_PHASE_4		40

/// \def heccs have been done

#define HECCER_STATUS_PHASE_5		50



int HeccerAggregatorsCompile(struct simobj_Heccer *pheccer);

int HeccerCanCompile(struct simobj_Heccer *pheccer);

int HeccerCompileP1(struct simobj_Heccer *pheccer);

int HeccerCompileP2(struct simobj_Heccer *pheccer);

int HeccerCompileP3(struct simobj_Heccer *pheccer);

int HeccerDumpV(struct simobj_Heccer *pheccer);

int HeccerDump(struct simobj_Heccer *pheccer, FILE *pfile, int iSelection);

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
#define HECCER_DUMP_VM_COMPARTMENT_MATRIX_DIAGONALS		(1 << 17)
/* #define HECCER_DUMP_VM_COMPARTMENT_DATA				(1 << 17) */
#define HECCER_DUMP_VM_COMPARTMENT_OPERATIONS			(1 << 18)
#define HECCER_DUMP_VM_MECHANISM_DATA				(1 << 19)
#define HECCER_DUMP_VM_MECHANISM_OPERATIONS			(1 << 20)
#define HECCER_DUMP_VM_CHANNEL_POOL_FLUXES			(1 << 21)
#define HECCER_DUMP_VM_SUMMARY					(1 << 22)

#define HECCER_DUMP_VM_AGGREGATORS				(1 << 25)

#define HECCER_DUMP_ALL (0xffffffff & ~(HECCER_DUMP_SERVICE | HECCER_DUMP_TABLE_GATE_TABLES))

#define HECCER_DUMP_ALL_EXTENDED (0xffffffff & ~HECCER_DUMP_SERVICE)

#define HECCER_DUMP_ALL_REDUCED (0xffffffff & ~(HECCER_DUMP_SERVICE | HECCER_DUMP_TABLE_GATE_TABLES))


int
HeccerCheckParameters
(struct simobj_Heccer *pheccer, char *pcDescription, ...);

int HeccerError(struct simobj_Heccer *pheccer, char *pcContext, char *pcError, ...);

char * HeccerGetVersion(void);

int HeccerHeccs(struct simobj_Heccer *pheccer, double dTime);

int HeccerInitiate(struct simobj_Heccer *pheccer);

struct simobj_Heccer *
HeccerNew
(char *pc,
 struct TranslationService *pts,
 struct EventDistributor *ped,
 struct EventQueuer *peq);

struct simobj_Heccer *
HeccerNewP1
(char *pc,
 struct TranslationService *pts,
 struct EventDistributor *ped,
 struct EventQueuer *peq,
 int iOptions,
 double dStep);

struct simobj_Heccer *HeccerNewP2(char *pc, struct Intermediary *pinter);

struct simobj_Heccer *HeccerNewFromFile(char *pc);

int HeccerWriteToFile(struct simobj_Heccer *pheccer, char *pc);


#endif


