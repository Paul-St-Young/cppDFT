cmake_minimum_required (VERSION 2.8.8)
project (cppDFT)
set (SRC_DIR src)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS "-std=c++11")

# find eigen
set(EIGEN3_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
if (EIGEN3_DIR)
	include_directories(${EIGEN3_DIR})
else()
	message(STATUS "Please export EIGEN3_INCLUDE_DIR")
	message(FATAL_ERROR "Undefined EIGEN3_INCLUDE_DIR env. var.")
endif()

# compile objects
add_library(pset
	${SRC_DIR}/Particle/Particle.cpp
	${SRC_DIR}/Particle/ParticlePool.cpp
	${SRC_DIR}/Particle/ParticleSet.cpp
)

add_library(updator 
	${SRC_DIR}/ForceField/Lennard-Jones.cpp
	${SRC_DIR}/ForceField/ForceField.cpp
	${SRC_DIR}/Updator/VelocityVerlet.cpp
)

add_library(basis
	${SRC_DIR}/Basis/PlaneWave.cpp
	${SRC_DIR}/Basis/BasisSet.cpp
)

add_library(func
	${SRC_DIR}/Function/Function.cpp
	${SRC_DIR}/Function/Density.cpp
	${SRC_DIR}/Function/ExternalPotential.cpp
	${SRC_DIR}/Kohn-Sham/Hamiltonian.cpp
)

# link executable
add_executable(cppDFT
    ${SRC_DIR}/Interface/InputManager.cpp
	${SRC_DIR}/main.cpp
)
target_link_libraries(cppDFT pset updator basis func m)

