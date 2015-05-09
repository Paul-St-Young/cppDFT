/* 
  A ParticleSet maintains a list of pointers to the particles of interest
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
	void clearFile (std::string filename);
};

#endif
