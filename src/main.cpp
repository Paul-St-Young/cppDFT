#include <iostream>

#include "Particle/ParticleSet.h"
#include "Function/ExternalPotential.h"

using namespace std;

int main(){

    // Put a hydrogen ion at the origin
    ParticlePool pPool(1);
    ParticleSet gPset(pPool.myParticles());
    
    gPset.ptcls[0]->name="H"; 
    gPset.ptcls[0]->m=1836;
    gPset.ptcls[0]->q=1;
    cout << gPset.str() << endl;
    
    ExternalPotential Vext(gPset);

    
    
return 0;
}
