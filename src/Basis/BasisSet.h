/* Basis Set
A basis set is just a collection of basis functions
*/

#ifndef _BASIS_SET_H
#define _BASIS_SET_H

#include "PlaneWave.h"
#include <vector>
#include <map>

class BasisSet{
int _nbasis;        // number of basis functions
int _nadded;        // number of basis functions added so far
Basis** _b;         // list of basis functions
bool _purePlaneWave;// is there only plane wave in the basis?
std::map<std::string,int> _idxMap; // keep a map from basis description to idx for easy access
public:
    BasisSet(int nbasis);
    ~BasisSet();
    // access
    Basis* basis(int idx){return _b[idx];};         // basis function
    int size(){return _nadded;};                    // number of basis functions
    bool purePlaneWave(){return _purePlaneWave;};
    int basisIndex(std::string identifier){return _idxMap[identifier];};
    std::map<std::string,int> myMap(){return _idxMap;};
    // methods
    void addPlaneWave(PosType k);
    void initPlaneWaves(RealType Ecut, RealType L);
};

#endif
