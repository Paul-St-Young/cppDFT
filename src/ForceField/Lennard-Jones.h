#ifndef _LENNARDJONES_H
#define _LENNARDJONES_H

#include "PairPotential.h"

class LennardJones: public PairPotential{
public:
	LennardJones(RealType sig, RealType eps) : sigma(sig),epsilon(eps){};
	RealType potential(PosType dR);
	PosType  gradient (PosType dR);
	RealType sigma,epsilon;
};

#endif 
