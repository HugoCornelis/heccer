//-------------------------------------------------------------------
/*!
 *  \file pulsegen.c
 *  \author Mando Rodriguez
 *
 *  This file holds the implementation for the pulsegen algorithm 
 *  implementation for use in generating pulses:  single pulses, double pulses 
 *  (each with its own level and width), and pulse trains (of single pulses or pairs).
 *  It can be triggered, gated, or allowed to free run.
 */
//-------------------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "heccer/pulsegen.h"


//-------------------------------------------------------------------
/*!
 * \fun int PulseGenSetFields(struct PulseGen *ppg,double dLevel1, double dWidth1,
 double dDelay1,double dLevel2,double dWidth2,double dDelay2,int iTriggerMode,double *pdPulseOut)
* \param ppg A pointer to a PulseGen struct.
* \param dLevel1 level of pulse1
* \param dWidth width of pulse1
* \param dDelay delay of pulse1
* \param dLevel2 level of pulse2
* \param dWidth2 width of pulse2
* \param dDelay2 delay of pulse2
* \param iTriggerMode Trigger mode for the pulsegen: 0 - free run, 1 - ext. trig, 2 - ext gate   
* \return 0 on error, 1 on success.
*
* Function sets the fields for an allocated PulseGen struct.
 */
//-------------------------------------------------------------------
int PulseGenSetFields
(
 struct PulseGen *ppg,
 double dLevel1,
 double dWidth1,
 double dDelay1,
 double dLevel2,
 double dWidth2,
 double dDelay2,
 int iTriggerMode,
 double *pdPulseOut
)
{

  if(!ppg)
  {
    fprintf(stderr,"%s","No PulseGen Simulation Object Allocated.\n");
    return 0;
  }

  ppg->dLevel1 = dLevel1;
  ppg->dWidth1 = dWidth1;
  ppg->dDelay1 = dDelay1;
  ppg->dLevel2 = dLevel2;
  ppg->dWidth2 = dWidth2;
  ppg->iTriggerMode = iTriggerMode;
  ppg->pdPulseOut = pdPulseOut;

  return 1;
}




//-------------------------------------------------------------------
/*!
 *
 */

//-------------------------------------------------------------------
int PulseGenProcess(struct PulseGen *ppg)
{

  int iInput;
  int iPulseNum;
  double dTCycle; 
  double dTT = 0.0;

  
  if( ppg->dWidth1 > (ppg->dDelay2 + ppg->dWidth2) )
  {
    dTCycle = ppg->dDelay1 + ppg->dWidth1;
  }
  else
  {
    dTCycle = ppg->dDelay1 + ppg->dDelay2 + ppg->dWidth2;
  }



  return 1;

}



//-------------------------------------------------------------------
/*!
 * \fun struct PulseGen * PulseGenCalloc(char *pcName)
 * \param pcName The name for this pulsegen object.
 * \return A pointer to a struct on success, NULL on error.
 *
 */
//-------------------------------------------------------------------
struct PulseGen * PulseGenCalloc(char *pcName)
{

  struct PulseGen *ppgResult = NULL;

  ppgResult = (struct PulseGen*)calloc(1,sizeof(struct PulseGen));

  if(!ppgResult)
  {
    
    return NULL;

  }

  ppgResult->pcName = strdup(pcName);

  return ppgResult;

}

//-------------------------------------------------------------------
/*!
 *  \fun int PulseGenReset(struct PulseGen *ppg)
 *  \param ppg A pointer to a PulseGen simulation object.
 *  \return 0 on error, 1 on success.
 *
 *  Sets values for the pulse generator to their deault state.
 */
//-------------------------------------------------------------------
int PulseGenReset(struct PulseGen *ppg)
{

  if(!ppg)
  {
    fprintf(stderr,"%s","Error: No PulseGen simulation object allocated, can't reset.\n");
    return 0;
  }

  ppg->dPreviousInput = 0.0;
  ppg->iTriggerMode = -1;
  
  if(!ppg->pdPulseOut)
  {
    fprint(stderr,"%s","Error: No PulseOut defined, can't reset output.\n");

    // We return 0 here even to the other variables have been correctly
    // reset.
    return 0;
  }
  else
  {
    (*ppg->pdPulseOut) = ppg->dBaseLevel;
  }

  return 1;

}
