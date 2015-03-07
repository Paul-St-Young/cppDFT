#ifndef _EXTERNALPOTENTIAL_H
#define _EXTERNALPOTENTIAL_H

#include "Function.h"
#include "../Particle/ParticleSet.h"

class ExternalPotential : public Function{
ParticleSet _pset;
public:
    ExternalPotential(ParticleSet pset) : Function(0), _pset(pset) {};
    ~ExternalPotential(){};
    
    ComplexType operator()(PosType r);              // override operator() since external potential is easy to calculate
    void initPlaneWaves(std::vector<PosType> K);
    
};

#endif
