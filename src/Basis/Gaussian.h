#ifndef _GAUSSIAN_H
#define _GAUSSIAN_H

#include "Basis.h"

class Gaussian : public Basis {
RealType _A,_sig;
PosType _mu;
public:
    Gaussian(RealType A, PosType mu, RealType sig,int id=-1);
    ComplexType operator()(PosType r);
};

#endif
