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


//o
//o the event distributor takes a generated event, and distributes it
//o over the receiving target objects.
//o
//o Heccer will call the ->eventDistribute() function on the distributor
//o service when it generates an event.  The iTargets is a pointer to a table
//o target objects.  For each entry in the table, ->pvFunction() is called,
//o with as first argument ->pvObject (may be NULL).  The table is terminated
//o with an entry of all NULLs.
//o


struct EventDistributor;

struct EventDistributorMatrix
{
    /// target object, a queuer, a HeccerOutput, or so

    void *pvObject;

    /// target subcomponent identification

    int iTarget;

    /// called function

    /// \note decouples the event distributor from the target

    int (*pvFunction)();

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

};


//o
//o the event receptor takes a incoming event, and queues it untill it fires.
//o
//o When the event fires, it is 
//o

struct EventQueuer;

struct EventQueuerMatrix
{
    /// target object, a solver or so

    void *pvObject;

    /// target site, an index into a array of double ?

    int iTarget;

    /// connection delay

    double dDelay;

    /// connection weight

    double dWeight;

    /// called function

    /// \note decouples the event queuer from the target

    int (*pvFunction)();

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

struct DES
{
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


struct ProjectionQuery;
struct SolverRegistry;

struct DES *DESNew(struct SolverRegistry *psr, struct ProjectionQuery *ppq);

/// \note The parameter list of EventDistributorAddConnection() assumes that
/// the output objects are always heccer output generators.  Internally
/// this does not matter, just for ease of development.

struct OutputGenerator;

int
EventDistributorAddConnection
(struct EventDistributor *ped, int iType, void *pvObject, int iTarget);

int
EventDistributorAddQueuerConnection
(struct EventDistributor *ped, struct EventQueuer *peq, int iTarget);

int
EventDistributorAddOutputConnection
(struct EventDistributor *ped, struct OutputGenerator *pog, int iTarget);

struct EventDistributorMatrix *
EventDistributorDataGetEntry(struct EventDistributorData *pedd, int iEntry);

struct EventDistributorData *
EventDistributorDataNew(int iConnections, int iPre);

int
EventDistributorInitiate
(struct EventDistributor *ped, int iType);

struct EventDistributor *
EventDistributorNew
(struct EventDistributorData *pedd);

int EventDistributorSerial2Index(struct EventDistributor *ped, int iSerial);

/* extern EventDistribute EventDistributorSend; */

int EventDistributorSend(struct EventDistributor *ped, double dTime, int iTargets);


/* extern EventQueue EventQueuerDequeue ; */

double EventQueuerDequeue(struct EventQueuer *peq, double dTime, int iTarget);

/* extern EventQueue EventQueuerEnQueue ; */

int EventQueuerEnqueue(struct EventQueuer *peq, double dTime, /* int iSource,  */int iTarget);

struct EventQueuerMatrix * EventQueuerGetRowFromSerial(struct EventQueuer *peq, int iIndex);

struct EventQueuer * EventQueuerNewFromSingleRow(struct EventQueuerMatrix *peqm);

int EventQueuerProcess(struct EventQueuer *peq);

int EventQueuerSerial2ConnectionIndex(struct EventQueuer *peq, int iSerial);

int
EventQueuerSerial2ConnectionIndexAdd
(struct EventQueuer *peq,
 int iSerial,
 int iIndex);

int EventQueuerSerial2ConnectionIndexSort(struct EventQueuer *peq);


#endif


