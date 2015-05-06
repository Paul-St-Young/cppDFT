#ifndef _PAIRPOTENTIAL_H
#define _PAIRPOTENTIAL_H

#include <iostream>

#include "../Interface/TypeFactory.h"
class PairPotential{
public:
	virtual RealType potential(PosType dR){
	    std::cerr << "PairPotential::potential(PosType) being called" << std::endl;
    };
	virtual PosType gradient(PosType dR){
	    std::cerr << "PairPotential::gradient being called" << std::endl;
	};
};

#endif
