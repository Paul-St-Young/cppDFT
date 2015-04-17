#include "Hamiltonian.h"

Hamiltonian::Hamiltonian(int nbasis) : _nbasis(nbasis){
    _H = new MatrixType(nbasis,nbasis);
}

Hamiltonian::~Hamiltonian(){
    delete _H;
}

void Hamiltonian::update(Density& n){
    Basis** b = n.myBasis();
    if (n.purePlaneWave()){
        for (int i=0;i<_nbasis;i++){
            (*_H)(i,i) = 0.5*b[i]->k().squaredNorm()                   // kinetic
                       + 4*M_PI/b[i]->k().squaredNorm()                // external
                       + 8*pow(M_PI,2)*n[i]/b[i]->k().squaredNorm();   // Hatree
        }
    } // purePlaneWave
}
