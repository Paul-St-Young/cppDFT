/* 
  A ParticleSet maintains a list of pointers to the particles of interest
  
  The idea is to have a "heavy" object ParticlePool that manages memory allocation and then have mutiple "light" objects ParticleSet to manipulate the data. A typical starting point:
  
  ParticlePool pPool(8); 
  pPool.initCubicPositions(1.0);
  ParticleSet gPset(pPool.myParticles());
  
  which:
  1. initialize 3 particles at the origin
  2. call an initialization method to redistribute the particles - most simulations don't allow two particles at the same position
  3. allow a particle set to control some particles in the pool (partial pool control is not yet implemented, so all particle sets are global particle sets at the moment)
  
*/

#ifndef _PARTICLESET_H
#define _PARTICLESET_H
#include "ParticlePool.h"

class ParticleSet {

public:
    int n; // number of particles
    ParticleList ptcls; // an array of pointers to the particles
    
	ParticleSet(ParticleList list) : ptcls(list){
		n=list.size();
	}
	
	std::string str();
	
	//typedef ParticleList::iterator iterator;
	//iterator begin(){return ptcls.begin();};
	//iterator end(){return ptcls.end();};
	
	void appendFile(std::string filename);
};

#endif
