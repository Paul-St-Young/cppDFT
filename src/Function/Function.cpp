#include "Function.h"
#include "../Basis/PlaneWave.h"

#include <sstream>
#include <iostream>
using namespace std;

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

void Function::initCoeff(VectorType c){
    for (int i=0;i<c.size();i++){
        _c[i]=c[i];
    }
}

void Function::initGrid(RealType L, int nx){
    _L = L;
    _xmin=-L/2.0; _xmax=L/2.0; _nx=nx;
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


void Function::updatePlaneWaves(){
// call initGrid before calling this method
if (_grid_initialized and _basisSet->purePlaneWave()){
    ComplexType I(0.0,1.0); // imaginary I
    #pragma omp parallel for schedule(static,1)
    for (int g=0;g<_basisSet->size();g++){
        // get the coeffient before each plane wave basis by Fourier
        _c[g] = 0.0;
        Basis* b = _basisSet->basis(g);
        PosType r;
        RealType dx=(_xmax-_xmin)/_nx;
        for (int i=0;i<_nx;i++){
            for (int j=0;j<_nx;j++){
                for (int k=0;k<_nx;k++){
                    r << dx*i+_xmin, dx*j+_xmin, dx*k+_xmin;
                    ComplexType kdotr(b->k().transpose()*r,0.0);
                    ComplexType fr = (*this)(r);
                    _c[g] += std::exp(-I*kdotr)*(ComplexType) ( 1.0/pow(_L,3)*pow(dx,3) )*fr;
                }
            }
        }
    
    }
    
}
}

ComplexType Function::integrate(Function* other){
ComplexType value(0.0,0.0);
if (_basisSet->purePlaneWave() and other->myBasisSet()->purePlaneWave()){
// if both functions are expanded in pw basis, integration is easy
    for (int i=0;i<_basisSet->size();i++){
        PosType k = _basisSet->basis(i)->k();
        PosType kneg = -k;
        
        //cout << " label " << other->myBasisSet()->basisIndex(ss.str()) << endl;
        int idx=(i-(_basisSet->size()-1)/2+_basisSet->size())%_basisSet->size();
        //cout << " refle " << (i-(_basisSet->size()-1)/2+_basisSet->size())%_basisSet->size() << endl;
        value += _c[i]*other->coeff( idx );
    }
}
return value;
}

