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


extern struct Heccer *pheccer;

extern struct VClamp *pvc;

extern struct PerfectClamp *ppc;


int WriteOutput(char *pcFilename);

int dump(struct Heccer *pheccer, FILE *pfile, int iTested, char *pcMessage, int i);


