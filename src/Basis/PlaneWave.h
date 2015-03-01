#ifndef _PLANEWAVE_H
#define _PLANEWAVE_H

#include "Basis.h"
#include <complex>

class PlaneWave : public Basis {
PosType _k;
public:
    PlaneWave(PosType k) : _k(k) {};
    ComplexType operator()(PosType r);
    int id(){return (int)_k.sum();};
};

#endif
