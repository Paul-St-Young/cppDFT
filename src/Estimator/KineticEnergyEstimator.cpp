#include "KineticEnergyEstimator.h"

RealType KineticEnergyEstimator::scalarEvaluate(){
    RealType T=0.0;
    
    for (int i=0;i<_pset.n;i++){
        for (int coord=0;coord<_MD_DIM;coord++){
            T+=0.5 * _pset.ptcls[i]->m 
                * _pset.ptcls[i]->v[coord]*_pset.ptcls[i]->v[coord];
        }
    }

    return T;
}
