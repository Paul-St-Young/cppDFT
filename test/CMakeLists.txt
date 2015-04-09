cmake_minimum_required(VERSION 2.6)

set(SRC_DIR ../../src)

# find eigen
find_package(Eigen3 REQUIRED)
set(EIGEN3_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
if (EIGEN3_DIR)
	include_directories(${EIGEN3_DIR})
else()
	message(STATUS "Please export EIGEN3_INCLUDE_DIR")
	message(FATAL_ERROR "Undefined EIGEN3_INCLUDE_DIR env. var.")
endif()

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(particleTest 
	../testParticleSet.cpp
	${SRC_DIR}/Particle/Particle.cpp
	${SRC_DIR}/Particle/ParticleSet.cpp
)

add_executable(basisTest 
    ../testBasis.cpp
    ${SRC_DIR}/Basis/PlaneWave.cpp
    ${SRC_DIR}/Basis/Gaussian.cpp
)

add_executable(functionTest 
    ../testFunction.cpp
    ${SRC_DIR}/Basis/PlaneWave.cpp
    ${SRC_DIR}/Function/Function.cpp
)

target_link_libraries(particleTest ${GTEST_LIBRARIES} pthread)
target_link_libraries(basisTest ${GTEST_LIBRARIES} pthread)
target_link_libraries(functionTest ${GTEST_LIBRARIES} pthread)

