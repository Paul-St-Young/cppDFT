/* Function (in some basis)
A function is written as a linear combination of basis functions.
It should be initialized with a list of coeffients, then it would 
take a real space coordinate and give back a number
*/

#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "../Basis/BasisSet.h"

#include <vector>

class Function{
protected:
    BasisSet* _basisSet;
    ArrayType _c; // coeffients
    
    VectorType *_grid;  // real space grid
    RealType _xmin, _xmax, _L; int _nx;
    bool _grid_initialized;
public:
    Function(BasisSet* B);
    ~Function();
    virtual ComplexType operator()(PosType r);      // purpose in life of a function (evaluate in real space)
    
    // access
    virtual ComplexType coeff(int idx){return _c[idx];};    // basis function coeffient(idx)
    virtual BasisSet* myBasisSet(){return _basisSet;};      // basis functions
    virtual VectorType* myGrid(){return _grid;};            // real space grid
    virtual int size(){ return _basisSet->size(); };
    
    // methods
    virtual void initGrid(RealType L, int nx);
    virtual void initCoeff(VectorType c);
    virtual void updateGrid();
    virtual void updatePlaneWaves();
    virtual void modifyCoeff(int idx, ComplexType myc){_c[idx]=myc;};
    virtual ComplexType integrate(Function* other);
    
};

#endif
