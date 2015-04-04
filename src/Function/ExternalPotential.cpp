#include "ExternalPotential.h"

ComplexType ExternalPotential::operator()(PosType r){
    ComplexType pot(0,0);
    for (int i=0;i<_pset.n;i++){
        pot -= _pset.ptcls[i]->q/( (r-_pset.ptcls[i]->r).norm() );
    }
    return pot;
}

void ExternalPotential::initPlaneWaves(std::vector<PosType> K){
    ArrayType C=ArrayType::Zero(_nbasis);
    Function::initPlaneWaves(K,C);
    for (int i=0;i<_nbasis;i++){
        _c[i] = 8*std::pow(M_PI,2)/_b[i]->k().squaredNorm();
    }
}
