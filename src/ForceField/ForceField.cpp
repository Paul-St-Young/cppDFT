#include "ForceField.h"

void ForceField::apply(){

	// zero out acceleration
	for (int i=0;i<_pset->n;i++){
		for (int coord=0;coord<_MD_DIM;coord++){
			_pset->ptcls[i]->a[coord]=0;
		}
	}
	
	ComplexType currentPot = _density->integrate(_Vext);
	ComplexType pot;
	
	// calculate new acceleration
	for (int i=0;i<_pset->n;i++){
	    PosType curPos = _pset->ptcls[i]->r;
	    for (int coord=0;coord<_MD_DIM;coord++){
            // finite difference
            _pset->ptcls[i]->r[coord] += _dx;
            _Vext->updatePlaneWaves();
            pot = _density->integrate(_Vext);
            
            _pset->ptcls[i]->a[coord] = ( -(pot-currentPot)/_dx ).real();
            // put back particle
            _pset->ptcls[i]->r = curPos;
        }
	}

}
