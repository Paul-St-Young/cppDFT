#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "../Interface/TypeFactory.h"

class Function{

public:
    Function(){};
    ~Function(){};
    
    template <typename T>
    T operator()(PosType r);
    
};

#include "Function.hpp"

#endif
