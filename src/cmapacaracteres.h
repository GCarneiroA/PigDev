
#ifndef CMAPACARACTERES_H
#define CMAPACARACTERES_H

#include "tipos_pig.h"

#include <string>
#include <vector>

typedef enum {CPIG_TEXTO_ESQUERDA,CPIG_TEXTO_DIREITA,CPIG_TEXTO_CENTRO} PIG_PosTexto;

class CMapaCaracteres
{
protected:
    static std::string PigDelimitadores;
    int **alturaExtra;
    int **larguraLetra;
    int janela;
    int fontDescent;
    int estiloFixo;

    SDL_Renderer *render;
    SDL_Texture ***glyphsT;
    TTF_Font *font;

    std::string nome;
    int tamFonte;

    void CriaLetrasSurface(PIG_Estilo estilo, int nivelOutline, PIG_Cor corOutline, SDL_Surface *fundo,  PIG_Cor corFonte=BRANCO);
    void IniciaBase(char *nomeFonte,int tamanhoFonte,int idJanela,PIG_Estilo estilo);
    CMapaCaracteres();

public:
    CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, char *nomeFundo,int outline,PIG_Cor corOutline, int idJanela);
    CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, PIG_Cor corFonte,int outline,PIG_Cor corOutline, int idJanela);
    ~CMapaCaracteres();
    void SubstituiGlyph(std::string nomeArq,uint16_t glyph, int largNova, int x, int y, int alt, int larg);
    int GetFonteDescent();
    int GetFonteAscent();
    PIG_Metricas_Fonte GetMetricasLetra(Uint16 letra, int estilo=0);
    int GetTamanhoBaseFonte();
    int GetLineSkip();
    int GetLarguraLetra(Uint16 letra, int estilo=0);
    std::vector<std::string> ExtraiLinhas(std::string texto, int largMax, std::string delim=PigDelimitadores);
    virtual int GetLarguraPixelsString(std::string texto);
    virtual void Escreve(std::string texto,int x,int y,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float ang=0);
    virtual void EscreveLonga(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,PIG_PosTexto pos=CPIG_TEXTO_ESQUERDA,float angulo=0);
    SDL_Surface *GetGlyph(Uint16 *emoji, PIG_Cor cor=BRANCO);
};

#endif // CMAPACARACTERES_H
