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


/* struct Heccer; */

struct EventDistributor;

struct EventDistributorData;


typedef int (*EventDistribute)(struct EventDistributor *ped, int iTargets);

struct EventDistributor
{
    //m service specific data

    struct EventDistributorData *pedd;

    //m distribute an event over the targets

    EventDistribute eventDistribute;

};


//f prototypes

/* extern EventDistribute HeccerEventDistribute; */

int HeccerEventDistribute(struct EventDistributor *ped, int iTargets);


#endif


