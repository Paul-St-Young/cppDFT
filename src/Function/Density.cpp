#include "Density.h"

void Density::updateWithWaveFunction(Function& wfs){
    for (int i=0;i<wfs.myBasisSet()->size();i++){
        PosType ki = wfs.myBasisSet()->basis(i)->k();
        ComplexType ci = wfs.coeff(i);
        for (int j=0;j<wfs.myBasisSet()->size();j++){
            PosType kj = wfs.myBasisSet()->basis(j)->k();
            ComplexType cj = wfs.coeff(j);
            PosType kjmki=kj-ki;
            _c[ _basisSet->basisIndex(kjmki) ] = conj(ci)*cj;
        }
    }

}
