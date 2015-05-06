#ifndef _HAMILTONIAN_H
#define _HAMILTONIAN_H

#include "../Function/ExternalPotential.h"

class Hamiltonian{
BasisSet* _wfBasis;
MatrixType* _H;
public:
    Hamiltonian(BasisSet* wfBasis);
    ~Hamiltonian();
    void update(ExternalPotential& Vext);
    MatrixType* myHam(){return _H;};
};

#endif
