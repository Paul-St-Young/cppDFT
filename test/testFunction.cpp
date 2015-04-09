#include <gtest/gtest.h>
#include "../src/Basis/Gaussian.h"
#include "../src/Function/Function.h"

using namespace std;

#define EPS 1e-3

// ----------------------- Test Constructor ----------------------- //
TEST(FunctionTest,SingleConstructor){
	Function f(2);
}

// ----------------------- Test Cos(x) ----------------------- //
TEST(FunctionTest,Cosx){
	Function f(2);
	// initialize cos(x)
	vector<PosType> K;
    PosType kvec1(_DFT_DIM);
    PosType kvec2(_DFT_DIM);
    kvec1 << -1,0,0;
    kvec2 << 1,0,0;
    K.push_back(kvec1);
    K.push_back(kvec2);
    ArrayType C=ArrayType::Ones(3);
    C*=0.5;
    f.initPlaneWaves(K,C);
    
    PosType r;
    r << 1,0,0;
    ComplexType fr(0.540302,0);
    EXPECT_LT( abs(fr-f(r)), EPS );
}

// ----------------------- Test Gaussian ----------------------- //
TEST(FunctionTest,Gaussian){
	Function f(1);
	PosType ro; ro << 1,0,0;
	Gaussian g(1.0,ro,1.0);
	vector<Basis*> v;
	v.push_back(&g);
	
	f.initBasis(v,ArrayType::Ones(1));
	PosType r; r << 0,0,0;
	EXPECT_LT( abs(f(r)-(ComplexType)0.60653065971263342)  ,EPS);
}

// ======================= Test Main ======================= //
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
