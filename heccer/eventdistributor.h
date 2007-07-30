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


#ifndef HECCER_EVENT_DISTRIBUTOR_H
#define HECCER_EVENT_DISTRIBUTOR_H


struct EventDistributor;

struct EventDistributorData
{
    //m target object

    void *pvTarget;

    //m called function

    int (*pvFunction)();
};


/* struct EventDistributorFunctions */
/* { */
/* }; */


typedef int (*EventDistribute)(struct EventDistributor *ped, double dTime, int iTargets);

struct EventDistributor
{
    //m service specific data

    struct EventDistributorData *pedd;

/*     struct EventDistributorFunctions *pedf; */

    //m distribute an event over the targets

    EventDistribute eventDistribute;

};


//f prototypes

/* extern EventDistribute HeccerEventDistribute; */

int HeccerEventDistribute(struct EventDistributor *ped, double dTime, int iTargets);


#endif


