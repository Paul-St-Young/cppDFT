#include "BasisSet.h"

BasisSet::BasisSet(int nbasis,RealType L) : _nbasis(nbasis), _L(L) {
    _b = new Basis*[nbasis];
    _nadded = 0;
    _purePlaneWave = false;
};

BasisSet::~BasisSet(){
    for (int i=0;i<_nadded;i++) delete _b[i];
    delete [] _b;
}

void BasisSet::addPlaneWave(PosType kvec){
    // save current index and increment
    int idx = _nadded++; 
    // add a pw basis
    _b[idx] = new PlaneWave(kvec,idx);
    // assume periodic boundary
    int i = (int)( kvec[0]*_L/(2*M_PI) );
    int j = (int)( kvec[1]*_L/(2*M_PI) );
    int k = (int)( kvec[2]*_L/(2*M_PI) );
    // map a description to idx
    std::stringstream ss; ss << i << " " << j << " " << k;
    _idxMap[ss.str()]=idx;
}

void BasisSet::initPlaneWaves(RealType Ecut){
    PosType kvec(_DFT_DIM);
    int maxIdx=ceil( sqrt(2*Ecut)*_L/2*M_PI );
    for (int i=-maxIdx;i<=maxIdx;i++){
        for (int j=-maxIdx;j<=maxIdx;j++){
            for (int k=-maxIdx;k<=maxIdx;k++){
                kvec << 2*M_PI/_L*i,2*M_PI/_L*j,2*M_PI/_L*k;
                if (0.5*kvec.squaredNorm()<Ecut)
                    addPlaneWave(kvec);
            }
        }
    }
    _purePlaneWave = true;
}

int BasisSet::basisIndex(PosType kvec){
    // assume periodic boundary
    int i = (int)( kvec[0]*_L/(2*M_PI) );
    int j = (int)( kvec[1]*_L/(2*M_PI) );
    int k = (int)( kvec[2]*_L/(2*M_PI) );
    // get the descriptio
    std::stringstream ss; ss << i << " " << j << " " << k;
    return _idxMap[ss.str()];
}
