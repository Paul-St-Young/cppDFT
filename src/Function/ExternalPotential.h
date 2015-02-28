#ifndef _EXTERNALPOTENTIAL_H
#define _EXTERNALPOTENTIAL_H

#include "Function.h"
#include "../Particle/ParticleSet.h"

class ExternalPotential{
ParticleSet _pset;
public:
    ExternalPotential(ParticleSet pset) : _pset(pset) {};
    ~ExternalPotential(){};
    
    RealType operator()(PosType r);
    
};

#endif
