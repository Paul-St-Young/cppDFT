/* Basis Function
A basis function takes a real space coordinate and gives back a number
*/

#ifndef _BASIS_H
#define _BASIS_H

#include "../Interface/TypeFactory.h"

class Basis{
protected:
int _id;
public:
    Basis(int id) : _id(id) {};
    ~Basis(){};
    virtual ComplexType operator()(PosType r){};
    virtual int id(){return _id;};
    
    // specialized
    virtual PosType k(){}; // return the k vector of a plane wave
    
};

#endif
