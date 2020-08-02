

#ifndef CPIGERROINDICE_H
#define CPIGERROINDICE_H

#include "cpigerro.h"
#include <string>

class CPigErroIndice : public CPigErro
{
protected:
    std::string tipoDado;
    int indice;

public:
    CPigErroIndice(int indVetor,std::string tipoDeDado);
    std::string GetTipoDado();
    int GetIndice();
};

#endif
