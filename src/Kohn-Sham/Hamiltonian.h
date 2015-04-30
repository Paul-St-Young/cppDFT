#ifndef _HAMILTONIAN_H
#define _HAMILTONIAN_H

#include "../Function/ExternalPotential.h"

class Hamiltonian{
int _nbasis; // size of basis set
Basis** _b;  // basis set
MatrixType* _H;
public:
    Hamiltonian(int nbasis);
    ~Hamiltonian();
    void update(ExternalPotential& Vext);
    MatrixType* myHam(){return _H;};
};

#endif
