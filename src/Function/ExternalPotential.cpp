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
    ComplexType I(0.0,1.0);
    PosType r;
    RealType L=5.0;
    RealType _xmin=-2.5, _xmax=2.5, dx=0.5;
    this->initGrid(-2.5,2.5,10);
    this->updateGrid();
    for (int g=0;g<_nbasis;g++){
        //_c[i] = 8*std::pow(M_PI,2)/_b[i]->k().squaredNorm();
        _c[g] = 0.0;
        for (int i=0;i<_nx;i++){
            for (int j=0;j<_nx;j++){
                for (int k=0;k<_nx;k++){
                    r << dx*i+_xmin, dx*j+_xmin, dx*k+_xmin;
                    ComplexType kdotr(_b[g]->k().transpose()*r,0.0);
                    _c[g] += 1/pow(L,3)*pow(dx,3)*(-1/r.norm());//*std::exp(-I*kdotr);
                }
            }
        }
    }
}
