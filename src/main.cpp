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
    int nbasis=27; // number of basis functions

    // Put a hydrogen ion at the origin
    ParticlePool pPool(1);
    ParticleSet gPset(pPool.myParticles());
    
    gPset.ptcls[0]->name="H"; 
    gPset.ptcls[0]->m=1836;
    gPset.ptcls[0]->q=1;
    cout << gPset.str() << endl;
    
    // choose a set of basis functions
    vector<PosType> K;
    PosType kvec(_DFT_DIM);
    for (int i=-1;i<=1;i++){
        for (int j=-1;j<=1;j++){
            for (int k=-1;k<=1;k++){
                kvec << i,j,k;
                K.push_back(kvec);
            }
        }
    }
    
    // guess a density and initialize the potentials
    Density             n(nbasis);
    ExternalPotential   Vext(gPset);
    HatreePotential     Vh(&n,nbasis);
    n.initPlaneWaves(K);
    Vh.initPlaneWaves(K);
    
    // self-consistently solve KS equation
    for (int step=0;step<max_it;step++){
        
    
    }
    
return 0;
}
