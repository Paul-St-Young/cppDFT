#ifndef _DENSITY_H
#define _DENSITY_H

#include "Function.h"

class Density : public Function {
public:
    Density(BasisSet* B) : Function(B){};
    void updateWithWaveFunction(Function& wfs);
};

#endif
