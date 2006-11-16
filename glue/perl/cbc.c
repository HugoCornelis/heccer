

#include "EXTERN.h"
#include "perl.h"


#include "heccer.h"


struct SV *HeccerNew(SV * psvInter)
{
    //- set default result : failure

    SV * psvResult = NULL;

    STRLEN len;

    struct Intermediary *pinter = SvPV(psvInter, len);

    //- instantiate a heccer with an initialized intermediary

    struct Heccer *pheccer = HeccerNewP2(pinter);

    //- build indices for optimization

    HeccerCompileP2(pheccer);

    //- compile to byte code

    HeccerCompileP3(pheccer);

    //- initiate values

    HeccerInitiate(pheccer);

    //- return result

    psvResult = newSVpv(pheccer, sizeof(*pheccer));

    return(psvResult);
}


