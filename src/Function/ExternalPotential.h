#ifndef _EXTERNALPOTENTIAL_H
#define _EXTERNALPOTENTIAL_H

#include "Function.h"
#include "../Particle/ParticleSet.h"

class ExternalPotential : public Function{
ParticleSet _pset;
int _nbasis;
public:
    ExternalPotential(ParticleSet pset,int nbasis) : Function(nbasis), _pset(pset),_nbasis(nbasis) {};
    ~ExternalPotential(){};
    
    ComplexType operator()(PosType r);              // override operator() since external potential is easy to calculate
    void initPlaneWaves(std::vector<PosType> K, RealType L, int nx);
    
};

#endif
