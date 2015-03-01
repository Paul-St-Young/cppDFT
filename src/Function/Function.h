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
public:
    Function(int nbasis) : _nbasis(nbasis), _initialized(false) { 
        _c.resize(_nbasis);
        _b = new Basis*[_nbasis];
    };
    ~Function();
    
    virtual ComplexType operator()(PosType r);              // purpose in life of a function
    virtual RealType& operator[](int i){return _c[i];};     // allow accessing and changing coeffients
    
    virtual void initPlaneWaves(std::vector<PosType> K);    // initialized in the list of given plane wave basis
};

class _Function_UninitializedBasisError{};

#endif
