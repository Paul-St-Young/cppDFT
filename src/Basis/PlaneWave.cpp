#include "PlaneWave.h"
#include <cmath>

using namespace std;

ComplexType PlaneWave::operator()(PosType r){
    ComplexType i(0,1);
    ComplexType kdotr(_k.transpose()*r,0);
    
    return exp(i*kdotr);
}
