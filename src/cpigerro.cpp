
#include "cpigerro.h"

#include <iostream>

CPigErro::CPigErro()
{
    codErro = 1;
}

std::string CPigErro::GetMensagem()
{
    return mensagem;
}

int CPigErro::GetCodigoErro()
{
    return codErro;
}

void CPigErro::PrintErro()
{
    std::cout << " Erro " << codErro << ": " << mensagem << std::endl;
}
