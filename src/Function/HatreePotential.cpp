#include "HatreePotential.h"

#include <cmath>
#define USE_MATH_DEFINES

void HatreePotential::initPlaneWaves(std::vector<PosType> K){
    Function::initPlaneWaves(K);
    for (int i=0;i<_nbasis;i++){
    
        if ( _n->purePlaneWave() ){ // if the density is expressed in plane wave basis
            _c[i] = 8*std::pow(M_PI,2)/_b[i]->k().squaredNorm() * (*_n)[i];
        } else {
            // need to do the integral \int d^3r' e^{i \vec{k}\cdot\vec{r'}} V_H (\vec{r'})
        
        }
        
    }
}

