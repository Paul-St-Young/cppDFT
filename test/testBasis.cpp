#include <gtest/gtest.h>
#include "../src/Basis/PlaneWave.h"
#include "../src/Basis/Gaussian.h"

using namespace std;

#define EPS 1e-3
#include <iostream>
// ----------------------- Test Constructor ----------------------- //
TEST(BasisTest,PWSingleConstructor){
    PosType k;
    k << 1,0,0;
	PlaneWave p(k);
	
	EXPECT_EQ(k,p.k());
}

TEST(BasisTest,G0){
	PosType ro;
    ro << 0,0,0;
	Gaussian g(1.0,ro,1.0);
	PosType r;
	r << 0,0,0;
	EXPECT_EQ((ComplexType)1.0,g(r));
}

TEST(BasisTest,G1){
    PosType ro;
    ro << 0,0,0;
	Gaussian g(1.0,ro,1.0);
	PosType r;
	r << 1,0,0;
	EXPECT_LT( abs(g(r)-(ComplexType)0.60653065971263342)  ,EPS);
}

// ----------------------- Test Cos(x) ----------------------- //
TEST(BasisTest,Cosx){
    PosType k;
    k << 1,0,0;
	PlaneWave p(k);
    k << -1,0,0;
	PlaneWave p1(k);
	
    PosType r;
    r << 1,0,0;
    
    ComplexType pr(0.540302,0);
    EXPECT_LT( abs(pr-(p(r)+p1(r))/(ComplexType)2), EPS );
}

// ======================= Test Main ======================= //
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
