#ifndef _HARTREEPOTENTIAL_H
#define _HARTREEPOTENTIAL_H

#include "Density.h"

class HatreePotential : public Function{
Density* _n;
public:

    HatreePotential(Density* n, int nbasis) : Function(nbasis), _n(n) {};   
    void initPlaneWaves(std::vector<PosType> K);
    
};

#endif
