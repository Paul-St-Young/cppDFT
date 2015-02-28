#include "ExternalPotential.h"

RealType ExternalPotential::operator()(PosType r){
    RealType pot=0.0;
    for (int i=0;i<_pset.n;i++){
        pot+=1/( (r-_pset.ptcls[i]->r).norm() );
    }
    return pot;
}

