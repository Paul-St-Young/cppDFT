#include "ExternalPotential.h"

#include <cmath>

ComplexType ExternalPotential::operator()(PosType r){
    ComplexType pot(0,0);
    for (int i=0;i<_pset.n;i++){
        pot -= _pset.ptcls[i]->q/( (r-_pset.ptcls[i]->r).norm() );
    }
    return pot;
}
