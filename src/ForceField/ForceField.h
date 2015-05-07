#ifndef _FORCEFIELD_H
#define _FORCEFIELD_H

#include "../Particle/ParticleSet.h"
#include "../Function/Density.h"

class ForceField{
ParticleSet* _pset;
Density *_density;
Function *_Vext;
RealType _dx; // finite difference spacing
public:
	ForceField(ParticleSet* pset, Density* density, Function* Vext, double dx) : _pset(pset), _density(density), _Vext(Vext), _dx(dx) {};
	void apply();
	ParticleSet* myPset(){return _pset;};
};

#endif
