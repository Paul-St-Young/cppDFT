#include "Density.h"

void Density::updateWithWaveFunction(Function& wfs){
    for (int i=0;i<wfs.myBasisSet()->size();i++){
        PosType ki = wfs.myBasisSet()->basis(i)->k();
        ComplexType ci = wfs.coeff(i);
        for (int j=0;j<wfs.myBasisSet()->size();j++){
            PosType kj = wfs.myBasisSet()->basis(j)->k();
            ComplexType cj = wfs.coeff(j);
            PosType kjmki=kj-ki;
            std::stringstream ss; //ss << kjmki[0] << " " << kjmki[1] << " " << kjmki[2];
            ss << (kjmki[0]==0?0:kjmki[0]) << " ";
            ss << (kjmki[1]==0?0:kjmki[1]) << " ";
            ss << (kjmki[2]==0?0:kjmki[2]);
            _c[ _basisSet->basisIndex(ss.str()) ] = conj(ci)*cj;
        }
    }

}
