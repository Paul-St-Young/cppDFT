#include "Density.h"

void Density::updateWithWaveFunction(Function& wfs){
    for (int i=0;i<wfs.myBasisSet()->size();i++){
        PosType ki = wfs.myBasisSet()->basis(i)->k();
        ComplexType ci = wfs.coeff(i);
        for (int j=0;j<wfs.myBasisSet()->size();j++){
            PosType kj = wfs.myBasisSet()->basis(j)->k();
            ComplexType cj = wfs.coeff(j);
            PosType kimkj=ki-kj;
            std::stringstream ss; ss << kimkj[0] << " " << kimkj[1] << " " << kimkj[2];
            _c[ _basisSet->basisIndex(ss.str()) ] = ci*cj;
        }
    }

}
