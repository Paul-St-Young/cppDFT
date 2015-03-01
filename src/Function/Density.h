#ifndef _DENSITY_H
#define _DENSITY_H

#include "Function.h"

class Density : public Function {
public:
    Density(int nbasis) : Function(nbasis){};
};

#endif
