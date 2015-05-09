#include <gtest/gtest.h>
#include "../src/Basis/BasisSet.h"

using namespace std;

#define EPS 1e-3
#include <iostream>
#include <sstream>
#include <map>
// ----------------------- Test Constructor ----------------------- //
TEST(BasisSetTest,Constructor){
    BasisSet B(1);
	EXPECT_EQ(B.size(),0);
}

// ----------------------- Test addPlaneWave ----------------------- //
TEST(BasisSetTest,addPlaneWave){
    BasisSet B(1);
    PosType k;
	k << 1,0,0;
	B.addPlaneWave(k);
	EXPECT_EQ(B.size(),1);
	EXPECT_EQ(B.basis(0)->id(),0);
	std::stringstream ss; ss << "1 0 0";
	EXPECT_EQ(B.basisIndex(ss.str()),0);
}

TEST(BasisSetTest,add2PlaneWave){
    BasisSet B(1);
    PosType k;
	k << 1,0,0;
	B.addPlaneWave(k);
	k << 0,1,0;
	B.addPlaneWave(k);
	EXPECT_EQ(B.size(),2);
	EXPECT_EQ(B.basis(0)->id(),0);
	std::stringstream ss; ss << "0 1 0";
	EXPECT_EQ(B.basisIndex(ss.str()),1);
	ss << "1 0 0";
	EXPECT_EQ(B.basisIndex(ss.str()),0);
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
    BasisSet B(100);
    B.initPlaneWaves(2.0,5.0);
    map<string,int> m = B.myMap();
    for(map<string,int>::iterator it = m.begin(); it != m.end(); ++it) {
        cout << it->first << endl;
    }
    std::stringstream ss; ss << "-1.25664 0 -1.25664";
	EXPECT_EQ(B.basisIndex(ss.str()),1);
	ss << "0.0 0.0 0.0";
	EXPECT_EQ(B.basisIndex(ss.str()),9);
}

// ======================= Test Main ======================= //
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
