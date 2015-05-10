#ifndef _PLANEWAVE_H
#define _PLANEWAVE_H

#include "Basis.h"

class PlaneWave : public Basis {
PosType _k;
RealType _L;
public:
    PlaneWave(PosType k, RealType L, int id=-1);
    ComplexType operator()(PosType r);
    PosType k(){return _k;}
};

#endif
