#ifndef _VELOCITYVERLET_H
#define _VELOCITYVERLET_H

#include "Updator.h"

class VelocityVerlet: public Updator {
std::vector<PosType> _oldA; // need to store old acceleration
public:
	VelocityVerlet(ParticleSet* pset, ForceField* ff):Updator(pset,ff){
		for (int i=0;i<_pset->n;i++){
			PosType a;
			a << 0.0,0.0,0.0;
			_oldA.push_back(a);
		}
	};
    void update();
};

#endif
