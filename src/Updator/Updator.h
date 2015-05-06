#ifndef _UPDATOR_H
#define _UPDATOR_H
#include <iostream>
#include "../Particle/ParticleSet.h"
#include "../ForceField/ForceField.h"
class Updator{
protected:
	ParticleSet* _pset;
	ForceField* _ff;
public:
	Updator(ParticleSet* pset, ForceField* ff) : _pset(pset), _ff(ff)
		{Rcut=0.0;h=0.0;}; // do not apply forces by default
    virtual void update(){
        std::cerr << "Updator::update being called" << std::endl;
    };
	RealType Rcut,h;
};

#endif
