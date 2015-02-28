cmake_minimum_required (VERSION 2.8.8)
project (cppDFT)
set (SRC_DIR src)

set(CMAKE_CXX_FLAGS "-std=c++11")

# find eigen
find_package(Eigen3 REQUIRED)
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

add_executable(cppDFT
	${SRC_DIR}/main.cpp
)

# link executable
target_link_libraries(cppDFT pset m)

