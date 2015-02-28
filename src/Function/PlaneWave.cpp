#include "PlaneWave.h"
#include <cmath>
#include <iostream>

using namespace std;

complex<RealType> PlaneWave::operator()(PosType r){

    complex<RealType> i(0,1);
    complex<RealType> kdotr(_k.transpose()*r,0);
    
    return exp(i*kdotr);

}
