Getting Started
---------------

### To build
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make -j4

### to run
    export OMP_NUM_THREADS=8
    ./cppDFT ../default.inp

### requirement
1. cmake 2.8.6 or above
2. c++11 compatible compiler
3. eigen3 include directory saved in EIGEN3\_INCLUDE\_DIR environment variable

Class Structure
---------------

### Particle Management
* Particle
* ParticlePool
* ParticleSet

A particle is basically a collection of attributes such as posiotion, velocity, acceleration, mass and charge. A ParticlePool contains physical particles and is responsible for their memory allocation, deallocation and initialization. A ParticleSet maintains a list of pointers to the particles of interest.
  
  The idea is to have a "heavy" object ParticlePool that manages memory allocation and then have mutiple "light" objects ParticleSet to manipulate the data. A typical starting point is
  
    ParticlePool pPool(8); 
    pPool.initCubicPositions(1.0);
    ParticleSet gPset(pPool.myParticles());
  
  which:
  1. initialize 3 particles at the origin
  2. call an initialization method to redistribute the particles - most simulations don't allow two particles at the same position
  3. allow a particle set to control some particles in the pool (partial pool control is not yet implemented, so all particle sets are global particle sets at the moment)

### Basis
* PlaneWave
* Gaussian

A basis function takes a position and returns a value

### BasisSet

A basis set is simply a collection of basis functions with some methods to create, destroy and access these basis functions.

### Function
* Density
* ExternalPotential
* HartreePotential

A function, like basis, also takes a position and returns a value. However, most functions need to be initialized as a linear combination of basis functions.


