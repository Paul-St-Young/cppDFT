#include "Function.h"
#include "../Basis/PlaneWave.h"

ComplexType Function::operator()(PosType r){
    if (!_initialized) throw _Function_UninitializedBasisError();
    ComplexType value=0;
    Basis* b;
    for (int i=0;i<_nbasis;i++){
        b = _b[i];
        value += _c[i]*(*b)(r);
    }
    return value;
};

void Function::initPlaneWaves(std::vector<PosType> K){
    for (int i=0;i<_nbasis;i++){
        _b[i] = new PlaneWave(K[i]);
        _c[i]=0;
    }
    _initialized=true;
}

Function::~Function(){
    if (_initialized){
        for (int i=0;i<_nbasis;i++){
            delete _b[i];
        }
    }
    delete[] _b;
}
