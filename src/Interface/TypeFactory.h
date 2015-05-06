#ifndef _TYPEFACTORY_H
#define _TYPEFACTORY_H

#include <Eigen/Dense>

// default to 3 dimensions
#define _DFT_DIM 3 
#define _MD_DIM 3 

typedef float                   RealType   ;
typedef std::complex<RealType>  ComplexType;
typedef Eigen::Vector3f         PosType    ;
typedef Eigen::Array<ComplexType,Eigen::Dynamic,1>                ArrayType ;
typedef Eigen::Matrix<ComplexType,Eigen::Dynamic,Eigen::Dynamic>  MatrixType;
typedef Eigen::Matrix<ComplexType,Eigen::Dynamic,1>               VectorType;

#endif
