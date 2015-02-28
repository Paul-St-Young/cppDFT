#include <iostream>

#include "Particle/ParticleSet.h"
#include "Function/PlaneWave.h"
#include "Function/Density.h"
#include "Function/ExternalPotential.h"
#include "Function/HatreePotential.h"


using namespace std;

int main(){

    int max_it=1;

    // Put a hydrogen ion at the origin
    ParticlePool pPool(1);
    ParticleSet gPset(pPool.myParticles());
    
    gPset.ptcls[0]->name="H"; 
    gPset.ptcls[0]->m=1836;
    gPset.ptcls[0]->q=1;
    cout << gPset.str() << endl;
    
    // guess a density and initialize the potentials
    Density n;
    
    ExternalPotential Vext(gPset);
    HatreePotential   Vh(&n);
    
    // self-consistently solve KS equation
    for (int step=0;step<max_it;step++){
        
    
    }
    
    PosType k(3);
    k << 1,0,0;
    PlaneWave k1(k);
    PosType r(3);
    r << 1,0,0;
    cout << k1(r) << endl;

    
    
return 0;
}
