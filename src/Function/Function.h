/* Function (in some basis)
A function is written as a linear combination of basis functions.
It should be initialized with a list of coeffients, then it would 
take a real space coordinate and give back a number
*/

#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "../Basis/Basis.h"

#include <vector>

class Function{
protected:
    int _nbasis;        // number of basis functions
    Basis** _b;         // list of basis functions
    ArrayType _c;       // list of coeffients, not so protected actually
    bool _initialized;  // is the basis initialized?
    bool _allocated;    // was memory allocated during initialization?
    bool _purePlaneWave; // is there only plane wave in the basis?
    
    VectorType *_grid;  // real space grid
    RealType _xmin, _xmax; int _nx;
    bool _grid_initialized;
public:
    Function(int nbasis);
    ~Function();
    bool purePlaneWave(){return _purePlaneWave;};
    void initGrid(RealType xmin, RealType xmax, int nx);
    void updateGrid();
    VectorType* myGrid(){return _grid;};
    Basis** myBasis(){return _b;};
    
    virtual ComplexType kEvaluate(PosType k){};             // evaluate in k space
    virtual ComplexType operator()(PosType r);              // purpose in life of a function (evaluate in real space)
    virtual RealType& operator[](int i){return _c[i];};     // allow accessing and changing coeffients
    
    virtual void initBasis(std::vector<Basis*> B, ArrayType C); // initialized in the list of given basis
    virtual void initPlaneWaves(std::vector<PosType> K, ArrayType C);    // initialized in the list of given plane wave basis
};

class _Function_UninitializedBasisError{};

#endif
