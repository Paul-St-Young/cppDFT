#ifndef _HARTREEPOTENTIAL_H
#define _HARTREEPOTENTIAL_H

#include "Density.h"

class HatreePotential{
Density* _n;
public:

    HatreePotential(Density* n) : _n(n) {};    
    RealType operator()(PosType r);
    
};

#endif
