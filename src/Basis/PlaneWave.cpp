#include "PlaneWave.h"
#include <cmath>

using namespace std;

PlaneWave::PlaneWave(PosType k){
    _k << k[0],k[1],k[2];
}

ComplexType PlaneWave::operator()(PosType r){
    ComplexType i(0,1);
    ComplexType kdotr(_k.transpose()*r,0);
    
    return exp(i*kdotr);
}
