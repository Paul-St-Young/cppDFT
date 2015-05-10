#include "PlaneWave.h"
#include <cmath>

using namespace std;

PlaneWave::PlaneWave(PosType k, RealType L, int id) : Basis(id), _L(L), _k(k) {
}

ComplexType PlaneWave::operator()(PosType r){
    ComplexType i(0.0,1.0);
    ComplexType kdotr(_k.transpose()*r,0.0);
    
    return (ComplexType)( 1.0/sqrt(pow(_L,_DFT_DIM)) )*exp(i*kdotr);
}
