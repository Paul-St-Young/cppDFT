#ifndef _TYPEFACTORY_H
#define _TYPEFACTORY_H

#include <Eigen/Dense>

// default to 3 dimensions
#define _DFT_DIM 3 

typedef float                   RealType   ;
typedef std::complex<RealType>  ComplexType;
typedef Eigen::VectorXf         PosType    ;
typedef Eigen::ArrayXf          ArrayType  ;

#endif
