#ifndef _HAMILTONIAN_H
#define _HAMILTONIAN_H

#include "../Function/Density.h"

class Hamiltonian{
int _nbasis; // size of basis set
MatrixType* _H;
public:
    Hamiltonian(int nbasis);
    ~Hamiltonian();
    void update(Density& n);
    MatrixType* myHam(){return _H;};
};

#endif
