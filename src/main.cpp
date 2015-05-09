#include <iostream>
#include <vector>
#include <cmath>
#define USE_MATH_DEFINES

#include "Interface/InputManager.h"
#include "Particle/ParticleSet.h"
#include "Basis/BasisSet.h"
#include "Function/Density.h"
#include "Function/ExternalPotential.h"
#include "Kohn-Sham/Hamiltonian.h"

#include "ForceField/Lennard-Jones.h"
#include "ForceField/ForceField.h"
#include "Updator/VelocityVerlet.h"
#include "Estimator/KineticEnergyEstimator.h"

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
    string traj=manager["output"]["trajectory"]; // Output files

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
    
    // construct external potential and Hamiltonian
    ExternalPotential   Vext(&densityBasis,gPset);
    Vext.initGrid(L,nx);
    Vext.updatePlaneWaves();
    Hamiltonian H(&waveFunctionBasis);
    H.update(Vext);
    
    // diagonalize the Hamiltonian
    Eigen::SelfAdjointEigenSolver<MatrixType> eigensolver(*H.myHam());
    cout << "The lowest eigenvalue of H is: " << eigensolver.eigenvalues()[0] << endl;
    VectorType c = eigensolver.eigenvectors().col(0);
    
    // create lowest KS orbital and its associated density
    Function waveFunction(&waveFunctionBasis);
    waveFunction.initCoeff(c);
    Density density(&densityBasis);
    density.updateWithWaveFunction(waveFunction);
    
    // ---------- we are now ready to do MD ----------
    
    // build a force field (need to be based on the electron wave function)
    ForceField* ff;
    ff = new ForceField(&gPset,&density,&Vext,0.01);
    
    // use VelocityVerlet updator using the force field
    VelocityVerlet updator(&gPset,ff); updator.h=dt;
    
    // throw in some estimators
    Estimator *kinetic;
    kinetic     = new KineticEnergyEstimator(gPset);
    
    //VectorType oldc = VectorType::Zero(c.size());
    VectorType oldc=c;
    
    gPset.ptcls[0]->r[1] = 0.05;
    ComplexType lambda=eigensolver.eigenvalues()[0]; // Lagrange Multiplier
    double Tn, Te; // kinetic energy of ions and electrons
    gPset.clearFile(traj);
    for (int istep=0;istep<nstep;istep++){
        gPset.appendFile(traj);
        VectorType conjc=c;
        for (int i=0;i<c.size();i++) conjc[i]=conj( conjc[i] );
        Tn = kinetic->scalarEvaluate();
        cout << "E= " << conjc.transpose()*(*H.myHam())*c << endl;
        // move the ions first since this depend on old waveFunction
        updator.update(); // density is used in here by ForceField
    
        // move the electrons
        //c = 2*c-oldc-pow(dt,2)/emass*( (*H.myHam())*c -lambda*c );
        
        // SHAKE it for the correct lambda
        VectorType uc; // uncontraint c
        uc = 2*c-oldc-pow(dt,2)/emass*( (*H.myHam())*c -lambda*c );
        ComplexType usigma(-1.0,0.0);
        for (int i=0;i<uc.size();i++){
            usigma += conj( uc[i] )*uc[i];
        }
        ComplexType dot(0.0,0.0);
        for (int i=0;i<uc.size();i++){
            dot += conj( uc[i] )*conj( c[i] )/(ComplexType)emass;
        }
        lambda = usigma/dot;
        for (int i=0;i<uc.size();i++){
            c[i] = uc[i]-conj( c[i] )*lambda*(ComplexType)(dt/emass);
        }
        oldc = c;
 
        // update density
        waveFunction.initCoeff(c);
        density.updateWithWaveFunction(waveFunction);
        
        // update Hamiltonian
        Vext.updatePlaneWaves();
        H.update(Vext);
    }
    
return 0;
}
