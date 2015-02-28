#ifndef _PARTICLE_CPP
#define _PARTICLE_CPP

#include "Particle.h"
#include <sstream>

Particle::Particle(){
    name="";
	m=0.0;
	r.resize(_DFT_DIM);
	v.resize(_DFT_DIM);
	a.resize(_DFT_DIM);
	for (int i=0;i<_DFT_DIM;i++){
		r(i) = 0;
		v(i) = 0;
		a(i) = 0;
	}
};

std::ostream& operator<<(std::ostream& os, const Particle& ptcl){
    os << ptcl.r.transpose();
    return os;
}

#endif
