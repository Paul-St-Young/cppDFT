#ifndef _FORCEFIELD_H
#define _FORCEFIELD_H

#include "../Particle/ParticleSet.h"
#include "PairPotential.h"

class ForceField{
ParticleSet* _pset;
PairPotential* _pp;
public:
	ForceField(ParticleSet* pset, PairPotential* pp) : _pset(pset), _pp(pp){};
	void apply();
	ParticleSet* myPset(){return _pset;};
	PairPotential* myPP(){return _pp;};
};

#endif
