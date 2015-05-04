#include <iostream>
#include <vector>
#include <fftw3.h>

#include "Particle/ParticleSet.h"
#include "Basis/PlaneWave.h"
#include "Function/Density.h"
#include "Function/ExternalPotential.h"
#include "Function/HatreePotential.h"
#include "Kohn-Sham/Hamiltonian.h"

#include <cmath>
#define USE_MATH_DEFINES

using namespace std;

int main(){

    int nstep=20;
    double dt=0.5;
    double emass=800;
    double L=5.0; // Bohr
    double Ecut=2.0; // Hartree
    int nx=23; // # of real space grid points must be odd to avoid r=0

    // Put a hydrogen ion at the origin
    ParticlePool pPool(1);
    ParticleSet gPset(pPool.myParticles());
    
    gPset.ptcls[0]->name="H"; 
    gPset.ptcls[0]->m=1836;
    gPset.ptcls[0]->q=1;
    cout << gPset.str() << endl;
    
    // choose a set of basis functions
    vector<PosType> K;
    int maxIdx=ceil( sqrt(2*Ecut)*L/2*M_PI );
    PosType kvec(_DFT_DIM);
    for (int i=-maxIdx;i<=maxIdx;i++){
        for (int j=-maxIdx;j<=maxIdx;j++){
            for (int k=-maxIdx;k<=maxIdx;k++){
                kvec << 2*M_PI/L*i,2*M_PI/L*j,2*M_PI/L*k;
                if (0.5*kvec.squaredNorm()<Ecut)
                    K.push_back(kvec);
            }
        }
    }
    vector<PosType> K2; // density needs more basis
    maxIdx*=2;
    for (int i=-maxIdx;i<=maxIdx;i++){
        for (int j=-maxIdx;j<=maxIdx;j++){
            for (int k=-maxIdx;k<=maxIdx;k++){
                kvec << 2*M_PI/L*i,2*M_PI/L*j,2*M_PI/L*k;
                if (0.5*kvec.squaredNorm()<2*Ecut)
                    K2.push_back(kvec);
            }
        }
    }
    cout << "Number of Wave Function Basis: " << K.size() << endl;
    cout << "Number of Density Basis: " << K2.size() << endl;

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
    
    /*
    // self-consistently solve KS equation
    for (int step=0;step<max_it;step++){
        
    
    }
    */
    
return 0;
}
