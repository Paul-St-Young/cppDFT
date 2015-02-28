#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>

#include "ParticlePool.h"

using namespace std;

ParticlePool::ParticlePool(int n) : _n(n), _initialized(true) {
    for (int i=0;i<n;i++){
        _ptls.push_back(new Particle);
    }
}

void ParticlePool::initCubicPositions(RealType L){

    int Ncube=1;
    while (_n>pow(Ncube,3)){
        Ncube += 1;
    } if (pow(Ncube,3)!=_n) cerr << "CubicInit Warning: Your particle number" << _n << "is not a perfect cube; this may result in a lousy initialization" << endl;
    
    RealType rs = (RealType)L/Ncube;
    RealType roffset = (RealType)L/2-rs/2;
    
    int added = 0;
    for (int x=0; x<Ncube; x++){
        for (int y=0; y<Ncube; y++){
            for (int z=0; z<Ncube; z++){
                _ptls[added]->r(0) = rs*x - roffset;
                _ptls[added]->r(1) = rs*y - roffset;
                _ptls[added]->r(2) = rs*z - roffset;
                added++;
            }
        }
    }

}

void ParticlePool::initVelocities(RealType T, RealType m){
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<RealType> rand(-0.5,0.5);
    
    PosType  netP(_DFT_DIM);
    RealType netE=0.0;
    
    for (int i=0;i<_n;i++){
        for (int coord=0;coord<_DFT_DIM;coord++){
            _ptls[i]->v(coord)=rand(mt);
            netP(coord) += _ptls[i]->v(coord);
            netE += pow(_ptls[i]->v(coord),2);
        }
    }
    for (int coord=0;coord<_DFT_DIM;coord++) netP(coord)/=(RealType)_n;
    RealType vScale = sqrt(3*_n*T/(m*netE));
    for (int i=0;i<_n;i++){
        for (int coord=0;coord<_DFT_DIM;coord++){
            _ptls[i]->v(coord)=(_ptls[i]->v(coord)-netP(coord))*vScale;
        }
    }
}

void ParticlePool::readPositions(std::string filename){

    std::string line;
    std::ifstream fs;
    fs.open(filename.c_str());
    int line_num=0;
    if (fs.is_open()){
        while (getline(fs,line)){
            if (_initialized){
                std::istringstream buf(line);
                std::istream_iterator<std::string> beg(buf), end;
                
                // assuming: name, x, y, z, etc.
                std::vector<std::string> tokens(beg, end);
                _ptls[line_num]->name=tokens[0];
                for (int coord=0;coord<_DFT_DIM;coord++){
                    _ptls[line_num]->r(coord)=atof(tokens[coord+1].c_str());
                }
                line_num++;
            }
        }
    }
    fs.close();
    
}

void ParticlePool::readVelocities(std::string filename){
    std::fstream fs;
    fs.open(filename.c_str());
    int line_num=0;
    std::string line;
    if (fs.is_open()){
        while (getline(fs,line)){
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            
            // assuming: name, x, y, z, etc.
            std::vector<std::string> tokens(beg, end);
            for (int coord=0;coord<_DFT_DIM;coord++){
                _ptls[line_num]->v(coord)=atof(tokens[coord+1].c_str());
            }
            line_num++;
        }
    }
    fs.close();

}

ParticlePool::~ParticlePool(){
    if (_initialized){
        for (int i=0;i<_n;i++){
            delete _ptls[i];
        }
    }
}
