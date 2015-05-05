#include "BasisSet.h"
#include <sstream>
#include <cmath>
#define USE_MATH_DEFINES
#include <iostream>
using namespace std;


BasisSet::BasisSet(int nbasis) : _nbasis(nbasis) {
    _b = new Basis*[nbasis];
    _nadded = 0;
    _purePlaneWave = false;
};

BasisSet::~BasisSet(){
    for (int i=0;i<_nadded;i++) delete _b[i];
    delete [] _b;
}

void BasisSet::addPlaneWave(PosType k){
    // save current index and increment
    int idx = _nadded++; 
    // add a pw basis
    _b[idx] = new PlaneWave(k,idx);
    // map a description to idx
    std::stringstream ss; ss << k[0] << " " << k[1] << " " << k[2];
    _idxMap[ss.str()]=idx;
}

void BasisSet::initPlaneWaves(RealType Ecut, RealType L){
    PosType kvec(_DFT_DIM);
    int maxIdx=ceil( sqrt(2*Ecut)*L/2*M_PI );
    for (int i=-maxIdx;i<=maxIdx;i++){
        for (int j=-maxIdx;j<=maxIdx;j++){
            for (int k=-maxIdx;k<=maxIdx;k++){
                kvec << 2*M_PI/L*i,2*M_PI/L*j,2*M_PI/L*k;
                if (0.5*kvec.squaredNorm()<Ecut)
                    addPlaneWave(kvec);
            }
        }
    }
    _purePlaneWave = true;
}
