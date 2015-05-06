#ifndef _FORCEFIELD_H
#define _FORCEFIELD_H

#include "../Particle/ParticleSet.h"

class ForceField{
ParticleSet* _pset;
public:
	ForceField(ParticleSet* pset) : _pset(pset){};
	void apply();
	ParticleSet* myPset(){return _pset;};
};

#endif
