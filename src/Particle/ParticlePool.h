/*
  The ParticlePool contains physical particles and is responsible for 
  their memory allocation (deallocation) and initialization
*/

#ifndef _PARTICLEPOOL_H
#define _PARTICLEPOOL_H

#include "Particle.h"

#include <vector>

typedef std::vector<Particle*> ParticleList;

class ParticlePool {
int _n;
ParticleList _ptls; // a list of pointers
bool _initialized;
public:
    ParticlePool() : _initialized(false) {};
    ParticlePool(int n);
    ~ParticlePool();
    int size(){return _n;};
    ParticleList myParticles(){return _ptls;};
    void readPositions (std::string filename);
    void readVelocities(std::string filename);
    void setMasses(RealType m){ for (int i=0;i<_n;i++) _ptls[i]->m=m; };
    void initCubicPositions(RealType L);
    void initVelocities(RealType T, RealType m);
};

#endif
