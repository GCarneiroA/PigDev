
#ifndef CJOGO_H
#define CJOGO_H

#include "tipos_pig.h"
#include "pigfuncoesbasicas.h"

#include <string>

class COffscreenRenderer;
class CTimer;

class CJogo
{
public:

    COffscreenRenderer *offRenderer;
    int cursorPadrao;

    CJogo(char *nome,int cursor=0,int altura=ALT_TELA,int largura=LARG_TELA);
    ~CJogo();
    PIG_Evento PegaEvento();
    void DefineFuncaoPintarArea(PIG_Cor (*funcao)(int,int,int,int,PIG_Cor,PIG_Cor));
    PIG_Teclado PegaTeclado();
    void IniciaInputTextoTela();
    void EncerraInputTextoTela();
    void IniciaDesenho(int idJanela=-1);
    void EncerraDesenho(int idJanela=-1);
    int GetEstado();
    int GetRodando();
    void SetEstado(int valor);
    float GetFPS();
    void PreparaOffScreenRenderer(int altura,int largura);
    void SalvaOffScreenBMP(char *nomeArquivo);
    void SalvaOffScreenPNG(char *nomeArquivo);
    int GetXCaneta();
    int GetYCaneta();
    void PintaAreaOffScreen(int px,int py,PIG_Cor cor,void *ponteiro);
    void PintarPoligono(int px[],int py[],int lados,PIG_Cor cor,int idJanela=0);
    void PintaFundoOffScreen(PIG_Cor cor);
    void DesenhaRetanguloOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor);
    void DesenhaRetanguloVazadoOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor);
    void DesenhaLinhaOffScreen(int x1,int y1,int x2,int y2,PIG_Cor cor);
    void MoveCanetaOffscreen(double nx,double ny);
    void AvancaCanetaOffscreen(double distancia);
    void MudaCorCanetaOffscreen(PIG_Cor novaCor);
    void GiraCanetaHorarioOffscreen(double angulo);
    void GiraCanetaAntiHorarioOffscreen(double angulo);
    void GiraCanetaAnguloFixoOffscreen(double angulo);
    double GetAngAtual();
private:
    PIG_Evento ultimoEvento;
    PIG_Teclado teclado;
    int contFPS,lastFPS;
    CTimer *timerFPS;
    int estado;
    int rodando;
    std::string diretorioAtual;
};

#endif
