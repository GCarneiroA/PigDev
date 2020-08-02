
#include "cpigerroindice.h"

CPigErroIndice::CPigErroIndice(int indVetor,std::string tipoDeDado)
    :CPigErro()
{
    tipoDado = tipoDeDado;
    indice = indVetor;
    mensagem = "O indice <"+std::to_string(indice)+"> nao pode ser utlizado para referenciar um ("+tipoDado+")";
    codErro = 4;
    PrintErro();
}

std::string CPigErroIndice::GetTipoDado()
{
    return tipoDado;
}

int CPigErroIndice::GetIndice()
{
    return indice;
}
