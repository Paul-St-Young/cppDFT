#include <gtest/gtest.h>
#include "../src/Basis/BasisSet.h"
#include "../src/Function/Function.h"

using namespace std;

#define EPS 1e-3

// ----------------------- Test Constructor ----------------------- //
TEST(FunctionTest,SingleConstructor){
    BasisSet B(2);
	Function f(&B);
}

// ----------------------- Test Cos(x) ----------------------- //
TEST(FunctionTest,Cosx){
    // initialize cos(r)
	BasisSet B(2);
	PosType kvec(_DFT_DIM);
	kvec << -1,0,0;
	B.addPlaneWave(kvec);
	kvec << 1,0,0;
	B.addPlaneWave(kvec);
	Function f(&B);
	f.modifyCoeff(0,(ComplexType)0.5);
	f.modifyCoeff(1,(ComplexType)0.5);
    // try cos(r)
    PosType r;
    r << 1,0,0;
    ComplexType fr(0.540302,0);
    EXPECT_LT( abs(fr-f(r)), EPS );
    
}

// ----------------------- Test Gaussian ----------------------- //
TEST(FunctionTest,Gaussian){
	//Function f(1);
	/*
	PosType ro; ro << 1,0,0;
	Gaussian g(1.0,ro,1.0);
	vector<Basis*> v;
	v.push_back(&g);
	
	f.initBasis(v,ArrayType::Ones(1));
	PosType r; r << 0,0,0;
	EXPECT_LT( abs(f(r)-(ComplexType)0.60653065971263342)  ,EPS);
	*/
}

// ======================= Test Main ======================= //
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
