#include "Gaussian.h"
#include <cmath>

Gaussian::Gaussian(RealType A, PosType mu, RealType sig,int id) 
    : Basis(id), _A(A), _mu(mu), _sig(sig){};
    
ComplexType Gaussian::operator()(PosType r){
    return _A*std::exp(-(r-_mu).squaredNorm()/(2*_sig*_sig));
}
