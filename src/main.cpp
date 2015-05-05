#include <iostream>
#include <vector>
//#include <fftw3.h>

#include "Interface/InputManager.h"
#include "Particle/ParticleSet.h"
#include "Basis/BasisSet.h"
#include "Function/ExternalPotential.h"
//#include "Kohn-Sham/Hamiltonian.h"

#include <cmath>
#define USE_MATH_DEFINES

using namespace std;

int main(int argc, char* argv[]){

    // gather inputs
    if (argc<2){
        cout << "please specify input" << endl;
        exit(0);
    }
    InputManager manager(argv[1]);
    int nstep = atoi( manager["CPMD"]["nstep"].c_str() );
    double dt = atof( manager["CPMD"]["dt"].c_str() );
    double emass = atof( manager["CPMD"]["emass"].c_str() );
    double L = atof( manager["DFT"]["L"].c_str() );
    double Ecut = atof( manager["DFT"]["Ecut"].c_str() );
    int nbasis = atoi( manager["DFT"]["maxBasis"].c_str() );
    int nx = atoi( manager["DFT"]["ngrid"].c_str() );

    // Put a hydrogen ion at the origin
    ParticlePool pPool(1);
    ParticleSet gPset(pPool.myParticles());
    
    gPset.ptcls[0]->name="H"; 
    gPset.ptcls[0]->m=1836;
    gPset.ptcls[0]->q=1;
    cout << gPset.str() << endl;
    
    // choose a basis set
    BasisSet waveFunctionBasis(nbasis);
    BasisSet densityBasis(pow(2,_DFT_DIM)*nbasis);
    waveFunctionBasis.initPlaneWaves(Ecut,L);
    densityBasis.initPlaneWaves(2*Ecut,L);
    cout << "Number of Wave Function Basis: " << waveFunctionBasis.size() << endl;
    cout << "Number of Density Basis: " << densityBasis.size() << endl;
    
    /*
    ExternalPotential   Vext(gPset,K2.size());
    Vext.initPlaneWaves(K2,L,nx); 
   
    Hamiltonian H(K2.size());
    H.update(Vext);
    
    Eigen::SelfAdjointEigenSolver<MatrixType> eigensolver(*H.myHam());
    cout << "The lowest eigenvalue of H is: " << eigensolver.eigenvalues()[0] << endl;
    
    
    VectorType c = eigensolver.eigenvectors().col(0);
    cout << c.squaredNorm() << endl;
    VectorType oldc = VectorType::Zero(c.size());
    for (int istep=0;istep<nstep;istep++){
        c = 2*c-oldc+ pow(dt,2)/emass*( (*H.myHam())*c );
        Vext.update(gPset.ptcls[0]->r,L,nx);
        H.update(Vext);
        // shake it
        cout << c.squaredNorm() << endl;
        oldc = c;
    }
    
    cout << c << endl;
    */
    /*
    // self-consistently solve KS equation
    for (int step=0;step<max_it;step++){
        
    
    }
    */
    
return 0;
}
