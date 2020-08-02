
#ifndef CPIGERROPARAMETRO_H
#define CPIGERROPARAMETRO_H

#include "cpigerro.h"
#include <string>

//Erro para falta de par�metro ou valor incorreto
class CPigErroParametro : public CPigErro
{

protected:
    std::string nomeParam;
    std::string nomeArq;

public:
    CPigErroParametro(std::string parametro,std::string arquivo);
    std::string GetNomeParam();
    std::string GetNomeArquivo();
};

#endif
