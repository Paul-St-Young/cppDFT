#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "../Interface/TypeFactory.h"

class Particle{

public:
    std::string name;
    PosType r,v,a; // position, velocity, acceleration
    RealType m,q; // mass, charge
    Particle(); // default constructor
    ~Particle(){};
    std::string str();
};

std::ostream& operator<<(std::ostream& os, const Particle& ptcl);

#endif
