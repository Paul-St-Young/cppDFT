#include <iostream>
#include <vector>

#include "Particle/ParticleSet.h"
#include "Basis/PlaneWave.h"
#include "Function/Density.h"
#include "Function/ExternalPotential.h"
#include "Function/HatreePotential.h"

using namespace std;

int main(){

    int max_it=1;
    int nbasis=26; // number of basis functions, k=(0,0,0) is thrown out

    // Put a hydrogen ion at the origin
    ParticlePool pPool(1);
    ParticleSet gPset(pPool.myParticles());
    
    gPset.ptcls[0]->name="H"; 
    gPset.ptcls[0]->m=1836;
    gPset.ptcls[0]->q=1;
    cout << gPset.str() << endl;
    
    // choose a set of basis functions
    vector<PosType> K;
    PosType kvec(_DFT_DIM);
    for (int i=-1;i<=1;i++){
        for (int j=-1;j<=1;j++){
            for (int k=-1;k<=1;k++){
                kvec << i,j,k;
                if (i!=0 || j!=0 || k!=0) K.push_back(kvec);
            }
        }
    }
    
    // guess a density and initialize the potentials
    Density             n(nbasis);
    ExternalPotential   Vext(gPset);
    HatreePotential     Vh(&n,nbasis);
    
    n.initPlaneWaves(K,ArrayType::Zero(nbasis));
    Vh.initPlaneWaves(K);
    
    // build Hamiltonian on a real space mesh
    RealType xmin=-1.0;
    RealType xmax=1.0;
    const int nx=10;
    RealType dx=(xmax-xmin)/nx;
    
    Eigen::Matrix<ComplexType,Eigen::Dynamic,Eigen::Dynamic> H(nx*nx*nx,nx*nx*nx);
    PosType r;
    // Potential is diagonal in real space
    for (int i=0;i<nx;i++){
        for (int j=0;j<nx;j++){
            for (int k=0;k<nx;k++){
                r << dx*i+xmin, dx*j+xmin, dx*k+xmin;
                H(i*nx*nx+j*nx+k,i*nx*nx+j*nx+k) = Vh(r)+Vext(r);
            }
        }
    }
    // Laplacian operator is not
    // H += lap3D(nx)
    
    // self-consistently solve KS equation
    for (int step=0;step<max_it;step++){
        
    
    }
    
return 0;
}
