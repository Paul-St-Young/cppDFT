#include "ExternalPotential.h"

#include <cmath>

ComplexType ExternalPotential::operator()(PosType r){
    ComplexType pot(0,0);
    for (int i=0;i<_pset.n;i++){
        pot -= _pset.ptcls[i]->q/( (r-_pset.ptcls[i]->r).norm() );
    }
    return pot;
}

void ExternalPotential::updatePlaneWaves(std::vector<PosType> K, RealType L, int nx){
    /*
    ComplexType I(0.0,1.0);
    PosType r;
    RealType _xmin=-L/2.0,_xmax=L/2.0, dx=(_xmax-_xmin)/nx;
    for (int g=0;g<_basisSet->size();g++){
        _c[g] = 0.0;
        for (int i=0;i<_nx;i++){
            for (int j=0;j<_nx;j++){
                for (int k=0;k<_nx;k++){
                    r << dx*i+_xmin, dx*j+_xmin, dx*k+_xmin;
                    ComplexType kdotr(_b[g]->k().transpose()*r,0.0);
                    _c[g] += std::exp(-I*kdotr)*(ComplexType)( 1.0/pow(L,3)*pow(dx,3)*((*this)(r)) );
                }
            }
        }
    }*/
}

void ExternalPotential::update(PosType R, RealType L, int nx){
    /*
    for (int g=0;g<_nbasis;g++){
        _c[g] = 0.0;
        ComplexType I(0.0,1.0);
        PosType r;
        RealType _xmin=-L/2.0,_xmax=L/2.0, dx=(_xmax-_xmin)/nx;
        for (int i=0;i<_nx;i++){
            for (int j=0;j<_nx;j++){
                for (int k=0;k<_nx;k++){
                    r << dx*i+_xmin, dx*j+_xmin, dx*k+_xmin;
                    ComplexType kdotr(_b[g]->k().transpose()*r,0.0);
                    if ((r-R).norm()!=0)
                        _c[g] += std::exp(-I*kdotr)*(ComplexType)( 1.0/pow(L,3)*pow(dx,3)*(-1/(r-R).norm()) );
                }
            }
        }
    }*/
}
