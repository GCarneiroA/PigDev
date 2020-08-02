
#ifndef CMAPACARACTERESDINAMICOS_H
#define CMAPACARACTERESDINAMICOS_H

#include "cpigstringformatada.h"

#include "tipos_pig.h"

#include "cmapacaracteres.h"

#include <vector>

class CMapaCaracteresDinamicos : public CMapaCaracteres
{
public:
    CMapaCaracteresDinamicos(char *nomeFonte, int tamanhoFonte, int idJanela);
    void Escreve(CPigStringFormatada formatada,int x,int y,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float ang=0);
    void Escreve(std::string texto,int x,int y,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float ang=0) override;
    void EscreveLonga(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float angulo=0) override;
    void EscreveLonga(std::vector<CPigStringFormatada> linhas, int x, int y, int espacoEntreLinhas,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float angulo=0);
    int GetLarguraPixelsString(std::string texto) override;
    std::vector<CPigStringFormatada> ExtraiLinhas(std::string texto, int largMax);
private:

    //processa uma string para transform�-la em StringFormatada
    CPigStringFormatada Processa(std::string textoOrig);
};

#endif // CMAPACARACTERESDINAMICOS_H
