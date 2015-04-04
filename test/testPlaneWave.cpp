#include <gtest/gtest.h>
#include "../src/Basis/PlaneWave.h"

using namespace std;

#define EPS 1e-3
#include <iostream>
// ----------------------- Test Constructor ----------------------- //
TEST(BasisTest,SingleConstructor){
    PosType k;
    k << 1,0,0;
	PlaneWave p(k);
	
	EXPECT_EQ(k,p.k());
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
