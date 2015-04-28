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
            (*_H)(i,i) = 0.5*b[i]->k().squaredNorm();                   // kinetic
        }
        
        for (int g=0;g<_nbasis;g++){
            for (int g1=0;g1<_nbasis;g1++){
            
                // find the idx for k(g)-k(g1)
                int idx=0;
                
                // 
                (*_H)(g,g1) += Vext[idx];
            
            }
        }
        
    } // purePlaneWave
}
