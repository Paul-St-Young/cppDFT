#ifndef _ESTIMATOR_H
#define _ESTIMATOR_H

#include "../Interface/TypeFactory.h"
#include "../Particle/ParticleSet.h"

#include <complex>
#include <fstream>
#include <iostream>

class Estimator{
protected:
    ParticleSet _pset;
public:
    Estimator(ParticleSet pset) : _pset(pset) {};
	virtual RealType scalarEvaluate(){};
	virtual PosType  vectorEvaluate(){};
	virtual void accumulate(int t){};
	virtual void finalize(std::string filename){};
	virtual void appendFile(std::string filename, int){};
};

#endif
