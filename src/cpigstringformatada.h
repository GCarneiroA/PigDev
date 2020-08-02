
#ifndef CPIGSTRINGFORMATADA_H
#define CPIGSTRINGFORMATADA_H

#include <memory>
#include <string>
#include <vector>

#include "tipos_pig.h"

class CPigStringFormatada
{

    char *ExtraiString();
    std::string letras;
    std::vector<int> largAcumulada;
    std::vector<PIG_Cor> cores;
    std::vector<PIG_Estilo> estilos;

public:

    ~CPigStringFormatada();
    Uint16 GetLetra(int indice);
    PIG_Cor GetCor(int indice);
    PIG_Estilo GetEstilo(int indice);
    void Clear();
    void Adiciona(char letra,int larguraAcumulada,PIG_Cor cor,PIG_Estilo estilo);
    void Print();
    int LargTotalPixels();
    int size();
    std::vector<CPigStringFormatada> SeparaPalavras(std::string delim);
    std::vector<CPigStringFormatada> ExtraiLinhas(int largMax, std::string delim);
    CPigStringFormatada operator +=(CPigStringFormatada outra);
};

#endif // CPIGSTRINGFORMATADA_H
