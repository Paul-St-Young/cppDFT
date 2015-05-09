#include <gtest/gtest.h>
#include "../src/Basis/BasisSet.h"

using namespace std;

#define EPS 1e-3
#include <iostream>
#include <sstream>
#include <map>
// ----------------------- Test Constructor ----------------------- //
TEST(BasisSetTest,Constructor){
    BasisSet B(1,1.0);
	EXPECT_EQ(B.size(),0);
}

// ----------------------- Test addPlaneWave ----------------------- //
TEST(BasisSetTest,addPlaneWave){
    BasisSet B(1,1.0);
    PosType k;
	k << 1,0,0;
	B.addPlaneWave(k);
	EXPECT_EQ(B.size(),1);
	EXPECT_EQ(B.basis(0)->id(),0);
	//std::stringstream ss; ss << "1 0 0";
	//EXPECT_EQ(B.basisIndex(ss.str()),0);
}

TEST(BasisSetTest,add2PlaneWave){
    RealType L=1.0;
    BasisSet B(1,L);
    PosType k;
	k << 1,0,0;
	B.addPlaneWave(k);
	k << 0,1,0;
	B.addPlaneWave(k);
	EXPECT_EQ(B.size(),2);
	EXPECT_EQ(B.basis(0)->id(),0);
	//std::stringstream ss; ss << "0 1 0";
	//EXPECT_EQ(B.basisIndex(ss.str()),1);
	//ss << "1 0 0";
	//EXPECT_EQ(B.basisIndex(ss.str()),0);
}

// ----------------------- Test modifyCoeff ----------------------- //
/*
TEST(BasisSetTest,modifyCoeff){
    BasisSet B(1);
    PosType k;
	k << 1,0,0;
	B.addPlaneWave(k,(ComplexType)1.0);
	EXPECT_EQ(B.coeff(0),(ComplexType)1.0);
	B.modifyCoeff(0,(ComplexType)3.0);
	EXPECT_EQ(B.coeff(0),(ComplexType)3.0);
}*/

// ----------------------- Test initPlaneWaves ----------------------- //
TEST(BasisSetTest,initPlaneWaves){
    BasisSet B(100,5.0);
    B.initPlaneWaves(2.0);
    map<string,int> m = B.myMap();
    for(map<string,int>::iterator it = m.begin(); it != m.end(); ++it) {
        cout << "m[\"" << it->first << "\"]=" << it->second << endl;
    }
    std::stringstream ss; ss << "-1 0 -1";
	EXPECT_EQ( 1,B.basisIndex(ss.str()) );
	ss.str("");ss << "0 0 0";
	EXPECT_EQ( 9,B.basisIndex(ss.str()) );
}
// ----------------------- Test basisIndex(kvec) ----------------------- //
TEST(BasisSetTest,basisIndex){
    RealType L=5.0;
    BasisSet B(100,L);
    B.initPlaneWaves(2.0);
    PosType kvec;
    kvec << 0,0,0;
	EXPECT_EQ( 9,B.basisIndex(kvec) );
	kvec << 2*M_PI/L,0,0;
	EXPECT_EQ( 16,B.basisIndex(kvec) );
}

// ======================= Test Main ======================= //
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
