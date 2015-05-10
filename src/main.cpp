#include "Interface/InputManager.h"
#include "Particle/ParticleSet.h"
#include "Basis/BasisSet.h"
#include "Function/Density.h"
#include "Function/ExternalPotential.h"
#include "Kohn-Sham/Hamiltonian.h"

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
    double thres = atof( manager["CPMD"]["conv_thr"].c_str() );
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
    BasisSet waveFunctionBasis(nbasis,L);
    BasisSet densityBasis(pow(2,_DFT_DIM)*nbasis,L);
    waveFunctionBasis.initPlaneWaves(Ecut);
    densityBasis.initPlaneWaves(2*Ecut);
    cout << "Number of Wave Function Basis: " << waveFunctionBasis.size() << endl;
    cout << "Number of Density Basis: " << densityBasis.size() << endl;
    
    // construct external potential and Hamiltonian
    ExternalPotential   Vext(&densityBasis,gPset);
    Vext.initGrid(L,nx);
    Vext.updatePlaneWaves(); // obtain expansion coefficients for Vext
    Hamiltonian H(&waveFunctionBasis);
    H.update(Vext); // obtain expansion coefficients for Hamiltonian
    
    // diagonalize the Hamiltonian
    Eigen::SelfAdjointEigenSolver<MatrixType> eigensolver(*H.myHam());
    ComplexType lambda=eigensolver.eigenvalues()[0]; // Lagrange Multiplier
    cout << "The lowest eigenvalue of H is: " << lambda.real() << endl;
    VectorType c = eigensolver.eigenvectors().col(0);
    
    // mess up the electronic ground state a little
    RealType E,norm;
    c = c.Random(c.size())/100.+c;
    c /= c.norm();
    E = ( c.adjoint()*(*H.myHam())*c )(0,0).real();
    cout << "Energy after slight electronic perturbation: " << E << endl;
    
    // See that CP can bring back the ground state
    VectorType oldc=c;
    RealType oldE=E;
    for (int istep=0;istep<nstep;istep++){
    
        // update Hamiltonian
        Vext.updatePlaneWaves();
        H.update(Vext);
    
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
        
        // move the electrons
        for (int i=0;i<uc.size();i++){
            c[i] = uc[i]-conj( c[i] )*lambda*(ComplexType)(dt/emass);
        }
        
        // report properties
        norm = c.norm();
        E = ( c.adjoint()*(*H.myHam())*c )(0,0).real();
        cout << "( " << E << "," << norm << ")" << endl; 
        
        if (abs(E-oldE)<thres) break;
        
        oldc = c; 
        oldE = E;
    }
    
    
    /*
    // ---------- we are now ready to do MD ----------
    
    // create lowest KS orbital and its associated density
    Function waveFunction(&waveFunctionBasis);
    Density density(&densityBasis);
    
    // build a force field (need to be based on the electron wave function)
    ForceField* ff;
    ff = new ForceField(&gPset,&density,&Vext,0.01);
    
    // use VelocityVerlet updator using the force field
    VelocityVerlet updator(&gPset,ff); updator.h=dt;
    
    // throw in some estimators
    Estimator *kinetic;
    kinetic     = new KineticEnergyEstimator(gPset);
    
    VectorType oldc=c;
    gPset.ptcls[0]->r[1] = 0.05;
    RealType Tn, Te, E, norm; // kinetic energy of ions and electrons
    gPset.clearFile(traj);
    for (int istep=0;istep<nstep;istep++){
        
        // save trajectory
        gPset.appendFile(traj);
    
        // update Hamiltonian
        Vext.updatePlaneWaves();
        H.update(Vext);
        
        // update density because it is used by the force field
        waveFunction.initCoeff(c);
        density.updateWithWaveFunction(waveFunction);
        
        // report properties
        norm = c.norm();
        Tn = kinetic->scalarEvaluate();
        E = ( c.adjoint()*(*H.myHam())*c )(0,0).real() + Tn;
        cout << "( " << E << "," << Tn << "," << norm << ")" << endl; 
        
        // move the ions first since this depend on old waveFunction
        updator.update(); // density is used in here by ForceField
    
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
        
        // move the electrons
        for (int i=0;i<uc.size();i++){
            c[i] = uc[i]-conj( c[i] )*lambda*(ComplexType)(dt/emass);
        }
        oldc = c;
        
    }
    */
return 0;
}
