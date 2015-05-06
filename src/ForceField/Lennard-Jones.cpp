#include "Lennard-Jones.h"
#include <iostream>
#include <cmath>

RealType LennardJones::potential(PosType dR){
	RealType r=0.0;
	for (int coord=0;coord<_MD_DIM;coord++) r+=dR[coord]*dR[coord];
	r=sqrt(r);
	return 4*epsilon*(pow(sigma,12)/pow(r,12)-pow(sigma,12)/pow(r,6));
}

PosType LennardJones::gradient(PosType dR){
	PosType grad;
	grad << 0.0, 0.0, 0.0;
	
	RealType r=0.0;
	for (int coord=0;coord<_MD_DIM;coord++) r+=dR[coord]*dR[coord];
	r=sqrt(r);
	
	for (int coord=0;coord<_MD_DIM;coord++){
		grad[coord]=-4*epsilon*(12*pow(sigma,12)/pow(r,13)-6*pow(sigma,6)/pow(r,7)) *dR[coord]/r;
	}
	
	return grad;
}

