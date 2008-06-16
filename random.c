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


#include <stdio.h>

#include "heccer/random.h"


/*
** Random number routines from "Numerical Recipes in C", Chapter 7
** Entered by Michael D. Speight, 10th September 1991
** All references to '*idum' changed to 'idum'
*/
#define M1 259200
#define IA1 7141
#define IC1 54773
#define RM1 (1.0)/M1
#define M2 134456
#define IA2 8121
#define IC2 28411
#define RM2 (1.0)/M2
#define M3 243000
#define IA3 4561
#define IC3 51349

float ran1(time_t idum)
{
  static long ix1,ix2,ix3;
  static float r[98];
  float temp;
  static int iff=0;
  int j;
  if (idum < 0 || iff == 0) {
    iff=1;
    ix1=(IC1-(idum)) % M1;
    ix1=(IA1*ix1+IC1) % M1;
    ix2=ix1 % M2;
    ix1=(IA1*ix1+IC1) % M1;
    ix3=ix1 % M3;
    for (j=1;j<=97;j++) {
      ix1=(IA1*ix1+IC1) % M1;
      ix2=(IA2*ix2+IC2) % M2;
      r[j]=(ix1+ix2*RM2)*RM1;
    }
    idum=1;
  }
  ix1=(IA1*ix1+IC1) % M1;
  ix2=(IA2*ix2+IC2) % M2;
  ix3=(IA3*ix3+IC3) % M3;
  j=1 + ((97*ix3)/M3);
  if (j>97||j<1) printf("RAN1: This cannot happen.\n");
  temp=r[j];
  r[j]=(ix1+ix2*RM2)*RM1;
  return temp;
}

