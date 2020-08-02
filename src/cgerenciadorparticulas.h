
#ifndef CGERENCIADORPARTICULAS_H
#define CGERENCIADORPARTICULAS_H

#include <string>
#include "tipos_pig.h"

class CObjeto;
class CAnimacao;
class CGeradorParticulas;
class CPoolNumeros;

class CGerenciadorParticulas
{
public:
    static void Inicia(SDL_Renderer *renderer=NULL);
    static void Encerra();
    static int CriaGeradorParticulas(int maxParticulas,std::string nomeArquivoBMP,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1);
    static int CriaGeradorParticulas(int maxParticulas,CAnimacao *animacaoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1);
    static int CriaGeradorParticulas(int maxParticulas,CObjeto *objetoBase,int audioCriacao, int audioEncerramento, int idJanela=0,int usaGerenciadorTimer=1);
    static void DestroiGeradorParticulas(int idGerador);
    static void Move(int idGerador,int px,int py);
    static void Desloca(int idGerador,int dx,int dy);
    static void MudaDirecaoParticulas(int idGerador,int dx,int dy);
    static void MudaRotacaoParticulas(int idGerador,float angPerSec);
    static void MudaCorParticulas(int idGerador,PIG_Cor cor);
    static void MudaEscalaParticulas(int idGerador,float escalaInicial,float escalaFinal);
    static void SetPivoParticulas(int idGerador,int pivoX,int pivoY);
    static void SetPivoParticulas(int idGerador,float pivoX,float pivoY);
    static int CriaParticula(int idGerador,int fadingOut=0,int minX=-50,int minY=-50,int maxX=LARG_TELA+50,int maxY=ALT_TELA+50,float maxTempo=9999999.9);
    static void MoveParticulas(int idGerador);
    static int GetQtdAtivas(int idGerador);
    static void Desenha(int idGerador);
    static int Colisao(int idGerador,CObjeto *obj);

private:
    //static SDL_Renderer *render;
    static int totalGeradores;
    static CPoolNumeros *numGeradores;
    static CGeradorParticulas *geradores[MAX_GERADORPARTICULAS];
};

#endif
