/* Basis Function
A basis function takes a real space coordinate and gives back a number
*/

#ifndef _BASIS_H
#define _BASIS_H

#include "../Interface/TypeFactory.h"
#include <iostream>

class Basis{

public:
    Basis(){};
    ~Basis(){};
    
    virtual ComplexType operator()(PosType r){};
    virtual int id(){
        std::cerr << "Basis::id() being called" << std::endl;
    };
    
};

#endif
