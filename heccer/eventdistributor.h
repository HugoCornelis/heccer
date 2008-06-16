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


/* //s the connection table translates model service serial in indices */
/* //s for the EventDistributorMatrix */

/* struct ConnectionTable; */


struct EventDistributor;

struct EventDistributorMatrix
{
    //m target object, a solver, a HeccerOutput, or so

    void *pvObject;

    //m target subcomponent identification

    int iTarget;

    //m called function

    //! decouples the event distributor from the target

    int (*pvFunction)();

    //m serial in the model container

    //t check if we can share this with iTarget

    int iSerial;

};


struct EventDistributorData
{
    //m number of connections in the matrix

    int iConnections;

    //m last used

    int iLast;

    //m array of targets

    struct EventDistributorMatrix *ppedm;
};


//d a event distribution function

typedef int (*EventDistribute)(struct EventDistributor *ped, double dTime, int iTargets);

struct EventDistributor
{
    //m service specific data

    struct EventDistributorData *pedd;

    //m hand an event over to the event distributor

    //! decouples the event distributor from the source

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
    //m target object, a solver or so

    void *pvObject;

    //m target site, an index into a array of double ?

    int iTarget;

    //m connection delay

    double dDelay;

    //m connection weight

    double dWeight;

    //m called function

    //! decouples the event queuer from the target

    int (*pvFunction)();

};


struct EventQueuerData
{
    //m array translating name service serials to event queuer target index

#define EVENTQUEUER_MAX_CONNECTIONS 10000

    int iConnectionIndices;

    int ppiSerial2ConnectionIndex[EVENTQUEUER_MAX_CONNECTIONS][2];

    //m array of targets

    struct EventQueuerMatrix *ppeqm;
};


//d a event dequeuing function

typedef double (*EventDequeuer)(struct EventQueuer *peq, double dTime, int iTarget);

//d a event enqueuing function

typedef int (*EventEnqueuer)(struct EventQueuer *peq, double dTime, /* int iSource,  */int iTarget);


struct EventQueuer
{
    //m service specific data

    struct EventQueuerData *peqd;

/*     //m hand an event over to the event queuer */

/*     //! decouples the event queuer from the source */

/*     EventEnqueuer eventEnqueue; */

    //m forward an event from queuer to receiver

    //! decouples the event queuer from the receiver

    EventDequeuer eventDequeue;

};


//f prototypes

//! The parameter list of EventDistributorAddConnection() assumes that
//! the output objects are always heccer output generators.  Internally
//! this does not matter, just for ease of development.

struct OutputGenerator;

int
EventDistributorAddConnection
(struct EventDistributor *ped, struct OutputGenerator *pog, int iType);

struct EventDistributorMatrix *
EventDistributorDataGetEntry(struct EventDistributorData *pedd, int iEntry);

struct EventDistributorData *
EventDistributorDataNew(int iConnections);

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

struct EventQueuer * EventQueuerNew(struct EventQueuerMatrix *ppeqm);

int EventQueuerProcess(struct EventQueuer *peq);

int EventQueuerSerial2ConnectionIndex(struct EventQueuer *peq, int iSerial);

int
EventQueuerSerial2ConnectionIndexAdd
(struct EventQueuer *peq,
 int iSerial,
 int iIndex);

int EventQueuerSerial2ConnectionIndexSort(struct EventQueuer *peq);


#endif


