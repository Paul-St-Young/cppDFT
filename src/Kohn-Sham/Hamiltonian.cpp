#include "Hamiltonian.h"
#include <iostream>
#include <sstream>
using namespace std;

Hamiltonian::Hamiltonian(int nbasis) : _nbasis(nbasis){
    _H = new MatrixType(nbasis,nbasis);
}

Hamiltonian::~Hamiltonian(){
    delete _H;
}

void Hamiltonian::update(ExternalPotential& Vext){
    Basis** b = Vext.myBasis();
    if (Vext.purePlaneWave()){
    
        // kinetic operator is diagonal in pw
        for (int i=0;i<_nbasis;i++){
            (*_H)(i,i) = 0.5*b[i]->k().squaredNorm(); 
        }
        // potential operator is not
        for (int g=0;g<_nbasis;g++){
            for (int g1=0;g1<_nbasis;g1++){
            
                // find the idx for k(g)-k(g1)
                PosType gmg1=b[g]->k()-b[g1]->k();
                stringstream ss; ss << gmg1[0] << " " << gmg1[1] << " " << gmg1[2];
                
                (*_H)(g,g1) += Vext[ Vext.basisIndex(ss.str()) ];
            
            }
        }
        
    } // purePlaneWave
}
