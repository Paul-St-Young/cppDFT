#ifndef _PLANEWAVE_H
#define _PLANEWAVE_H

#include "Function.h"
#include <complex>

class PlaneWave{
PosType _k;
public:
    PlaneWave(PosType k) : _k(k) {};
    std::complex<RealType> operator()(PosType r);
    
};

#endif
