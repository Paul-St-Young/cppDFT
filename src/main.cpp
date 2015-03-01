#include <iostream>
#include <vector>

#include "Particle/ParticleSet.h"
#include "Basis/PlaneWave.h"
#include "Function/Density.h"
#include "Function/ExternalPotential.h"
#include "Function/HatreePotential.h"

using namespace std;

int main(){

    int max_it=1;
    int nbasis=1; // number of basis functions

    // Put a hydrogen ion at the origin
    ParticlePool pPool(1);
    ParticleSet gPset(pPool.myParticles());
    
    gPset.ptcls[0]->name="H"; 
    gPset.ptcls[0]->m=1836;
    gPset.ptcls[0]->q=1;
    cout << gPset.str() << endl;
    
    // guess a density and initialize the potentials
    Density n(nbasis);
    ExternalPotential Vext(gPset);
    HatreePotential   Vh(&n,nbasis);
    
    // self-consistently solve KS equation
    for (int step=0;step<max_it;step++){
        
    
    }
    
return 0;
}
