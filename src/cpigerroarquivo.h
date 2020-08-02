
#ifndef CPIGERROARQUIVO_H
#define CPIGERROARQUIVO_H

#include "cpigerro.h"

#include <string>

//Erro para abertura de arquivo em geral (imagem, audio, video, etc)
class CPigErroArquivo : public CPigErro
{
protected:
    std::string nomeArquivo;

public:
    CPigErroArquivo(std::string nomeArq);
    std::string GetNomeArquivo();

};

#endif
