
#ifndef CGERENCIADORFONTES_H
#define CGERENCIADORFONTES_H

#include "tipos_pig.h"
#include "cmapacaracteres.h"

#include <string>

class CMapaCaracteres;
class CPoolNumeros;

class CGerenciadorFontes
{
public:
    static CMapaCaracteres *GetFonte(int idFonte);
    static void Inicia();
    static void Encerra();
    static int CriaFonteFundo(char *nome,int tamanho,int estilo,char *arquivoFundo,int contorno,PIG_Cor corContorno,int idJanela=0);

    static int CriaFonteNormal(char *nome,int tamanho,int estilo,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,int idJanela=0);

    static int CriaFonteDinamica(char *nome,int tamanho,int idJanela=0);

    static int GetLarguraPixels(std::string texto,int numFonte=0);
    static int GetFonteDescent(int numFonte=0);

    static int GetFonteAscent(int numFonte=0);
    static void EscreverString(std::string str,int x,int y,int numFonte,PIG_PosTexto pos = CPIG_TEXTO_ESQUERDA,float angulo=0);
    static void EscreverInteiro(int valor,int x,int y,int numFonte,PIG_PosTexto pos = CPIG_TEXTO_ESQUERDA,float angulo=0);

    static void EscreverReal(double valor,int x,int y,int numFonte,int casas=2,PIG_PosTexto pos = CPIG_TEXTO_ESQUERDA,float angulo=0);
    static void EscreverLonga(std::string str,int x,int y,int largMax,int espacoEntreLinhas,int numFonte,PIG_PosTexto pos = CPIG_TEXTO_ESQUERDA,float angulo=0);

    static std::vector<std::string> ExtraiLinhasString(std::string texto,int largMax,int numFonte);
    static PIG_Metricas_Fonte GetMetricas(Uint16 letra, int numFonte,PIG_Estilo estilo=ESTILO_NORMAL);
    static int GetLarguraLetra(char letra,int numFonte, PIG_Estilo estilo=ESTILO_NORMAL );
    static int GetTamanhoBaseFonte(int numFonte);
    static int GetLineSkip(int numFonte);
    static SDL_Surface *GetGlyph(Uint16 *ch,int numFonte,PIG_Cor cor=BRANCO);
    static void DestroiFonte(int idFonte);
    static void SubstituiCaracter(uint16_t caracter,std::string nomeArquivo,int largNova,int x,int y,int altura,int largura,int numFonte);

private:
    static int totalFontes;
    static CPoolNumeros *numFontes;
    static CMapaCaracteres *fontes[MAX_FONTES];
    CGerenciadorFontes(){}
};

#endif // CGERENCIADORFONTES_H
