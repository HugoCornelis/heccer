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


#ifndef HECCER_EVENT_DISTRIBUTOR_H
#define HECCER_EVENT_DISTRIBUTOR_H


#include <stdio.h>


/*! \mainpage DES -- Neurospaces Discrete Event System for Neural
 *  Network Simulations.
 *
 * Events are generated externally.  A generated event is handed over
 * to the event distributor.  The event distributor takes a generated
 * event, and distributes it over the receiving target objects.  The
 * target objects can be event queuers or other event processing
 * objects such as output objects or solvers that convert the discrete
 * event back to continuous time quantities.
 *
 * The event queuer takes a incoming event, and queues it untill it
 * fires.  At reception time the receiver object is notified about the
 * firing time.  The receiver is expected to fetch the event at the
 * correct time.
 *
 * In the current implementation Heccer calls the ->eventDistribute()
 * function on the distributor service when it generates an event.
 * The iTargets is a pointer to a table with target objects.  For each
 * entry in the table, ->pvEventReceive() is called, with as first
 * argument ->pvObject (may be NULL).  The table is terminated with an
 * entry of all NULLs.
 *
 */


struct EventDistributor;

struct EventDistributorMatrix
{
    /// target object, a queuer, a HeccerOutput, or so

    void *pvObject;

    /// target subcomponent identification

    int iTarget;

    /// called function

    /// \note decouples the event distributor from the target

    int (*pvProcess)();

/*     /// serial in the model container */

/*     /// \todo check if this can be the same as iTarget */

/*     int iSerial; */

};


struct EventDistributorData
{
    /// number of connections in the matrix

    int iConnections;

    /// last used

    int iLast;

    /// array of targets

    struct EventDistributorMatrix *ppedm;
};


/// \def a event distribution function

typedef int (*EventDistribute)(struct EventDistributor *ped, double dTime, int iTargets);

struct EventDistributor
{
    /// service specific data

    struct EventDistributorData *pedd;

    /// hand an event over to the event distributor

    /// \note decouples the event distributor from the source

    EventDistribute eventDistribute;

    /// serial range

    int iSerialEnd;

    int iSerialStart;

};


// \struct Event queuer.

struct EventQueuer;

struct EventQueuerMatrix
{
    /// target object, a solver or so

    void *pvObject;

/*     /// identifier in the target object. */

/*     int iPost; */

    /// target site

    double *pdSynapses;

    /// connection delay

    double dDelay;

    /// connection weight

    double dWeight;

    /// called function

    /// \note decouples the event queuer from the target

    int (*pvAccept)();

};


struct EventQueuerData
{
    /// array translating name service serials to event queuer target index

#define EVENTQUEUER_MAX_CONNECTIONS 10000

    int iConnectionIndices;

    int ppiSerial2ConnectionIndex[EVENTQUEUER_MAX_CONNECTIONS][2];

    /// number of rows in the matrix

    int iRows;

    /// matrix rows

    struct EventQueuerMatrix **ppeqm;
};


/// \def a event dequeuing function

typedef double (*EventDequeuer)(struct EventQueuer *peq, double dTime, int iTarget);

/// \def a event enqueuing function

typedef int (*EventEnqueuer)(struct EventQueuer *peq, double dTime, /* int iSource,  */int iTarget);


struct EventQueuer
{
    /// service specific data

    struct EventQueuerData *peqd;

/*     /// hand an event over to the event queuer */

/*     /// \note decouples the event queuer from the source */

/*     EventEnqueuer eventEnqueue; */

    /// forward an event from queuer to receiver

    /// \note decouples the event queuer from the receiver

    EventDequeuer eventDequeue;

};


/// \struct all the event distributors and queuers that connect the
/// solvers.

struct simobj_DES
{
    /// name of this des system

    /// \note if the name of des is a system wide id depends on the
    /// environment, des does not (and cannot) enforce it.

    char *pcName;

    /// status : reflects phases of compilation.

    int iStatus;

    int iErrorCount;

    /// pre-synaptic elements, event generator serials

    int iPreSerials;

    int *piPreSerials;

    /// all event distributors

    struct EventDistributor **pped;

    /// number of threads

    int iCores;

    /// all event queuers

    struct EventQueuer **ppeq;

};


int DESDumpV(struct simobj_DES *pdes);

int DESDump(struct simobj_DES *pdes, FILE *pfile, int iSelection);

#define DES_DUMP_ALL (0xffffffff & ~(DES_DUMP_SERVICE))

#define DES_DUMP_ALL_EXTENDED (0xffffffff & ~DES_DUMP_SERVICE)

#define DES_DUMP_ALL_REDUCED (0xffffffff & ~(DES_DUMP_SERVICE | DES_DUMP_DISTRIBUTOR_MATRIX | DES_DUMP_QUEUER_MATRIX))

#define DES_DUMP_SERVICE					(1 << 7)

#define DES_DUMP_DISTRIBUTOR_MATRIX				(1 << 13)

#define DES_DUMP_QUEUER_MATRIX					(1 << 14)


struct EventDistributor *DESGetDistributor(struct simobj_DES *pdes, int iSerial);

struct EventQueuer *DESGetQueuer(struct simobj_DES *pdes, int iCore);

struct simobj_DES *DESNew(int iHappy);


int
EventDistributorAddConnection
(struct EventDistributor *ped, void *pvEventReceive, void *pvObject, int iTarget);

struct EventDistributorMatrix *
EventDistributorDataGetEntry(struct EventDistributorData *pedd, int iEntry);

struct EventDistributorData *
EventDistributorDataNew(int iConnections, int iPre);

struct EventDistributor *
EventDistributorNew
(struct EventDistributorData *pedd);

/* extern EventDistribute EventDistributorSend; */

int EventDistributorSend(struct EventDistributor *ped, double dTime, int iTargets);

int EventDistributorSetSerialRange(struct EventDistributor *ped, int iStart, int iEnd);

/* extern EventDequeuer EventQueuerDequeue ; */

double EventQueuerDequeue(struct EventQueuer *peq, double dTime, int iTarget);

/* extern EventEnqueuer EventQueuerEnQueue ; */

int EventQueuerEnqueue(struct EventQueuer *peq, double dTime, /* int iSource,  */int iTarget);

struct EventQueuerMatrix * EventQueuerGetRowFromSerial(struct EventQueuer *peq, int iIndex);

struct EventQueuer * EventQueuerNew(int iPreSerials);

int EventQueuerProcess(struct EventQueuer *peq, double dTime);

int EventQueuerSerial2ConnectionIndex(struct EventQueuer *peq, int iSerial);

int
EventQueuerAddSerial2ConnectionIndex
(struct EventQueuerData *peqd,
 int iSerial,
 int iIndex);

int EventQueuerSerial2ConnectionIndexSort(struct EventQueuer *peq);


#endif


