//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#ifndef MECHANISM_H
#define MECHANISM_H


#include "mathcomponent.h"


//s spring mass channel (synaptic channel)

#define MECHANISM_TYPE_ChannelSpringMass 1

struct ChannelSpringMass
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dEk;
    double dFrequency;
/*     double dNormalizer; */
    double dX;
    double dY;
};


//s expential decaying ion concentration

#define MECHANISM_TYPE_Concen 2

struct Concen
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dB;
    double dBase;
    double dTau;
};


//s GHK, not sure if correct, use at own risk

#define MECHANISM_TYPE_GHK 3

struct GHK
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dCin;
    double dCout;
    double dT;
    int iValency;
};


//s channel magnesium blocking

#define MECHANISM_TYPE_MGBlocker 4

struct MGBlocker
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dCMg;
    double dKMg_A;
    double dKMg_B;
};


//s variable channel nernst potential

#define MECHANISM_TYPE_Nernst 5

struct Nernst
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dCin;
    double dConstant;
    double dCout;
};


//s spike generator

#define MECHANISM_TYPE_SpikeGenerator 6

struct SpikeGenerator
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dRefract;
    double dThresh;
};


//s HH alike channel

#define MECHANISM_TYPE_TabulatedHHChannel 7

struct TabulatedHHChannel
{
    //m administration overhead

    struct MathComponent mc;

    //m first set of descriptive values, alphabetical order

    double dEk;
    double dGbar;

    double dXPower;
    double dYPower;
    double dZPower;

    /*m1-6 point into element hierarchy tabchannel structs */

    struct table_struct *ipX_A;
    struct table_struct *ipX_B;
    struct table_struct *ipY_A;
    struct table_struct *ipY_B;
    struct table_struct *ipZ_A;
    struct table_struct *ipZ_B;

#ifdef USE_NO_TABLE_STRUCT

    /*m number of intervals */

    double dXDivs;

    /*m1-2 table range */

    double dXMin;
    double dXMax;

    /*m horizontal scaling factor */

    double dXScale;

    /*m allocated table or NULL */

    double *pdX;

    double dYDivs;
    double dYMin;
    double dYMax;
    double dYScale;
    double *pdY;

    double dZDivs;
    double dZMin;
    double dZMax;
    double dZScale;
    double *pdZ;

#endif

};


//f prototypes

int HeccerMechanismCompile(struct Heccer *pheccer);

int HeccerMechanismSolveCN(struct Heccer *pheccer);

int HeccerMechanismSort(struct Heccer *pheccer);


#endif


