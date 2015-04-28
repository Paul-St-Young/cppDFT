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

    int max_it=1;
    int nbasis=26; // number of basis functions, k=(0,0,0) is thrown out
    double L=1.0; // Bohr
    double Ecut=10.0; // Hartree

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
                if (i!=0 || j!=0 || k!=0) K.push_back(kvec);
            }
        }
    }
    
    // guess a density and initialize the potentials
    Density             n(nbasis);
    n.initPlaneWaves(K,ArrayType::Zero(nbasis)); n[1]=1;
    
    ExternalPotential   Vext(gPset);
    Vext.initPlaneWaves(K);
    
    /*RealType xmin=-1.0;
    RealType xmax=1.0;
    const int nx=3;
    RealType dx=(xmax-xmin)/nx;
    
    n.initGrid(xmin,xmax,nx);
    fftw_complex *in, *out;
    fftw_plan p;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * pow(nx,3) );
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * pow(nx,3) );
    p = fftw_plan_dft_3d(nx,nx,nx, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);*/
   
    //Hamiltonian H(nbasis);
    //H.update(n);
    //cout << *H.myHam() << endl;
    
    // self-consistently solve KS equation
    for (int step=0;step<max_it;step++){
        
    
    }
    
return 0;
}
