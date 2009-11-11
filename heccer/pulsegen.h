//------------------------------------------------------------------
/*!
 *  \file nsintegrator.h
 *  \author Mando Rodriguez
 *
 *  This file holds the declarations for the pulsegen algorithm.
 */
//-------------------------------------------------------------------

#ifndef SIMULATIONOBJECTS_PULSEGEN__H
#define SIMULATIONOBJECTS_PULSEGEN__H



/*
 * Trigger mode defines taken from GENESIS.
 */
#define FREE_RUN	0
#define EXT_TRIG	1
#define EXT_GATE	2


struct PulseGen
{

  char *pcName;

  double dLevel1;
  double dWidth1;
  double dDelay1;

  double dLevel2;
  double dWidth2;
  double dDelay2;

  double dBaseLevel;

  double dTriggerTime;
  int iTriggerMode;

  
  int iPreviousInput;

  /// solved variables

  double *pdPulseOut;



};





struct PulseGen * PulseGenCalloc(char *pcName);
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
 );

#endif
