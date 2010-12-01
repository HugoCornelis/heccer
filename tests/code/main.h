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


extern struct simobj_Heccer *pheccer;

extern struct simobj_VClamp *pvc;

extern struct simobj_PerfectClamp *ppc;

extern struct simobj_PulseGen *ppg;

int WriteOutput(char *pcFilename);

int tests_dump(struct simobj_Heccer *pheccer, FILE *pfile, int iTested, char *pcMessage, int i);


