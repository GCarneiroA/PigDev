
#include "cpigerroparametro.h"

CPigErroParametro::CPigErroParametro(std::string parametro,std::string arquivo)
    :CPigErro()
{
    nomeParam = parametro;
    nomeArq = arquivo;
    mensagem = "O parametro <"+nomeParam+"> nao foi definido ou possui valor incorreto no arquivo ("+nomeArq+")";
    codErro = 3;
    PrintErro();
}

std::string CPigErroParametro::GetNomeParam()
{
    return nomeParam;
}

std::string CPigErroParametro::GetNomeArquivo()
{
    return nomeArq;
}
