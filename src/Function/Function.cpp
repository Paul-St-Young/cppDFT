#include "Function.h"
#include "../Basis/PlaneWave.h"

#include <sstream>

Function::Function(int nbasis) : _nbasis(nbasis), _initialized(false), _allocated(false)
  , _purePlaneWave(false), _grid_initialized(false) { 
    _c.resize(_nbasis);
    _b = new Basis*[_nbasis];
};

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

void Function::initBasis(std::vector<Basis*> B, ArrayType C){
    for (int i=0;i<_nbasis;i++){
        _b[i] = B[i];
        _c[i] = C[i];
    }
    _initialized=true;
    _allocated=false;
}

void Function::initPlaneWaves(std::vector<PosType> K,ArrayType C){
    for (int i=0;i<_nbasis;i++){
        _b[i] = new PlaneWave(K[i]);
        _c[i]=C[i];
    }
    _initialized=true;
    _allocated=true;
    _purePlaneWave=true;
}

void Function::initGrid(RealType xmin, RealType xmax, int nx){
    _xmin=xmin; _xmax=xmax; _nx=nx;
    _grid = new VectorType(nx*nx*nx);
    _grid_initialized=true;
}

void Function::updateGrid(){
    PosType r;
    RealType dx=(_xmax-_xmin)/_nx;
    for (int i=0;i<_nx;i++){
        for (int j=0;j<_nx;j++){
            for (int k=0;k<_nx;k++){
                r << dx*i+_xmin, dx*j+_xmin, dx*k+_xmin;
                (*_grid)(i*_nx*_nx+j*_nx+k) = (*this)(r);
            }
        }
    }
}

Function::~Function(){
    if (_allocated){
        for (int i=0;i<_nbasis;i++){
            delete _b[i];
        }
    }
    delete[] _b;
    
    if (_grid_initialized) delete _grid;
}
