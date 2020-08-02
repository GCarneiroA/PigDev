
#ifndef CPIGERRO_H
#define CPIGERRO_H

#include <string>

class CPigErro
{
protected:
    std::string mensagem;
    int codErro;

public:
    CPigErro();
    std::string GetMensagem();
    int GetCodigoErro();
    void PrintErro();
};

#endif
