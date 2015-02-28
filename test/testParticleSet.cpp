#include <gtest/gtest.h>
#include "../src/Particle/ParticleSet.h"

using namespace std;

// ----------------------- Test Constructor ----------------------- //
TEST(ParticleSetTest,SingleConstructor){
	ParticleList pool;
	pool.push_back(new Particle);
    ParticleSet pset(pool);
    EXPECT_EQ(1,pset.n);
}

/*
TEST(ParticleSetTest,SingleAccess){
	ParticleList pool;
	pool.push_back(new Particle);
    ParticleSet pset(pool);
    EXPECT_EQ(1,pset.n);
	EXPECT_EQ("( 0 0 0 )",pset.ptcls[0]->str());
}

TEST(ParticleSetTest,SingleAlter){
	ParticleList pool;
	pool.push_back(new Particle);
    ParticleSet pset(pool);
	pset.ptcls[0]->r[0]=2.0;
    EXPECT_EQ(1,pset.n);
	EXPECT_EQ("( 2 0 0 )",pset.ptcls[0]->str());
}

TEST(ParticleSetTest,DoubleAlter){
	ParticleList pool;
	pool.push_back(new Particle);
	pool.push_back(new Particle);
    ParticleSet pset(pool);
    EXPECT_EQ(2,pset.n);
	
	pset.ptcls[0]->r[2]=3;
	pset.ptcls[1]->r[1]=-1;
	
	EXPECT_EQ("( 0 0 3 )",pset.ptcls[0]->str());
	EXPECT_EQ("( 0 -1 0 )",pset.ptcls[1]->str());
}
*/

// ======================= Test Main ======================= //
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
