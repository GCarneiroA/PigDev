
#ifndef CPIGGAUGE_H
#define CPIGGAUGE_H

#include "cpigcomponente.h"

typedef enum
{
    GAUGE_CIMA_BAIXO,
    GAUGE_BAIXO_CIMA,
    GAUGE_ESQ_DIR,
    GAUGE_DIR_ESQ
} PIG_GaugeCrescimentoBarra;

class CPigGauge : public CPigComponente
{
public:
    CPigGauge(int idComponente,int px, int py,int altura,int largura,std::string imgGauge,int retiraFundo=1,int janela=0);
    CPigGauge(std::string nomeArqParam);

    static CPigGauge LeArquivoParametros(std::string nomeArqParam);
    void SetValorMinMax(int minimo,int maximo);
    void AvancaBarra(float valor);
    void SetFrames(SDL_Rect fBase,SDL_Rect fBarra);
    void SetDistanciaXYBarra(int dx,int dy);
    void SetPorcentagemConcluida(float porcentagem);
    void SetDelta(float valor);
    void AvancaDelta();
    float GetPorcentagemConcluida();
    void SetOrientacaoBarra(PIG_GaugeCrescimentoBarra orientacao);
    int Desenha();
    float GetValorBarraAtual();
    void SetValorBarraAtual(float valor);
    void ZeraValor();

private:
    SDL_Rect frameBarra,frameBase;
    double delta,porcentagemConcluida;
    double valorMax,valorMin,valorAtual;
    int xBarra,yBarra,altBarra,largBarra;
    PIG_GaugeCrescimentoBarra orientacaoCrescimento;

    void DefineEstado(PIG_EstadoComponente estadoComponente);
    int OnMouseOn();
    int OnMouseOff();
    int TrataEvento(PIG_Evento evento);

    SDL_Rect GeraClip(SDL_Rect barra);
};

#endif
