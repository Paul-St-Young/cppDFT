#include "ForceField.h"

void ForceField::apply(){

	// zero out acceleration
	for (int i=0;i<_pset->n;i++){
		for (int coord=0;coord<_MD_DIM;coord++){
			_pset->ptcls[i]->a[coord]=0;
		}
	}
	
	// calculate new acceleration
	

}
