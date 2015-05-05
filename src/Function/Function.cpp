#include "Function.h"
#include "../Basis/PlaneWave.h"

#include <sstream>

Function::Function(BasisSet* B) : _basisSet(B){
    _c = ArrayType::Zero(_basisSet->size());
    _grid_initialized=false;
 };
 
 Function::~Function(){
    if (_grid_initialized) delete _grid;
}
 
ComplexType Function::operator()(PosType r){
    ComplexType value=0;
    Basis* b;
    for (int i=0;i<_basisSet->size();i++){
        b = _basisSet->basis(i);
        value += _c[i]*(*b)(r);
    }
    return value;
};

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


