
#include "cpigerroarquivo.h"

CPigErroArquivo::CPigErroArquivo(std::string nomeArq)
    :CPigErro()
{
    nomeArquivo = nomeArq;
    mensagem = "Nao foi possivel abrir o arquivo <" + nomeArq + ">";
    codErro = 2;
    PrintErro();
}

std::string CPigErroArquivo::GetNomeArquivo()
{
    return nomeArquivo;
}
