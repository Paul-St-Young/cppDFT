#include "Hamiltonian.h"

Hamiltonian::Hamiltonian(BasisSet* wfBasis) : _wfBasis(wfBasis) {
    _H = new MatrixType(wfBasis->size(),wfBasis->size());
}

Hamiltonian::~Hamiltonian(){
    delete _H;
}

void Hamiltonian::update(ExternalPotential& Vext){
    // Assume Vext uses the larger basisSet (for density)
    // and the Hamiltonian uses the smaller basisSet
    BasisSet* densityBasis = Vext.myBasisSet();
    if (_wfBasis->purePlaneWave()){
        
        // zero out Hamiltonian
        for (int g=0;g<_wfBasis->size();g++){
            for (int g1=0;g1<_wfBasis->size();g1++){
                (*_H)(g,g1) = 0.0;
            }
        }
    
        // kinetic operator is diagonal in pw
        for (int i=0;i<_wfBasis->size();i++){
            (*_H)(i,i) = 0.5*_wfBasis->basis(i)->k().squaredNorm(); 
        }
        // potential operator is not
        for (int g=0;g<_wfBasis->size();g++){
            for (int g1=0;g1<_wfBasis->size();g1++){
                
                Basis* b  = _wfBasis->basis(g);
                Basis* b1 = _wfBasis->basis(g1);
            
                // find the idx for k(g)-k(g1)
                PosType gmg1=b->k()-b1->k();
                (*_H)(g,g1) += Vext.coeff( densityBasis->basisIndex(gmg1) );
            
            }
        }
        
    } // purePlaneWave
}
