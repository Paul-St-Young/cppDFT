#include "HatreePotential.h"

void HatreePotential::initPlaneWaves(std::vector<PosType> K){
    Function::initPlaneWaves(K);
    for (int i=0;i<_nbasis;i++){
        _c[i]=0; // get expansion coefficients
        // need to do the integral \int d^3r' e^{i \vec{k}\cdot\vec{r'}} V_H (\vec{r'})
    }
}

