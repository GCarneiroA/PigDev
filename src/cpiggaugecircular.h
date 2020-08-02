
#ifndef CPIGGAUGECIRCULAR_H
#define CPIGGAUGECIRCULAR_H

#include "cpigcomponente.h"

class COffscreenRenderer;

class CPigGaugeCircular : public CPigComponente
{
public:
    CPigGaugeCircular(int idComponente,int px, int py,int altura,int largura,int raioInterior,int janela=0);
    CPigGaugeCircular(int idComponente,int px, int py,int altura,int largura,int raioInterior,std::string nomeArq,int retiraFundo=1,int janela=0);
    ~CPigGaugeCircular();
    void SetRaioInterno(int valorRaio);
    void SetAnguloBase(double novoAng);
    void SetDeltaAngulo(double novoDelta);
    void IncrementaValor(int delta);
    void SetValorMax(int novoValor);
    void SetValorMin(int novoValor);
    void SetCorInicial(PIG_Cor cor);
    void SetCorFinal(PIG_Cor cor);
    void SetCorFundo(PIG_Cor cor);
    int GetValor();
    std::string GetValorString();
    int GetValorMax();
    int GetValorMin();
    void AtualizaValor(int novoValor);
    void AtualizaTextura();
    int Desenha();

private:
    double angBase,deltaAng;
    int raioInterno;
    PIG_Cor corInicial,corFinal,corFundo;
    COffscreenRenderer *off;
    bool crescimentoHorario;
    int valor,valorMin,valorMax;
    double porcentagemConcluida;
    SDL_Texture *textGauge;

    void DefineEstado(PIG_EstadoComponente estadoComponente);
    int OnMouseOn();
    int OnMouseOff();
    int TrataEvento(PIG_Evento evento);

};

#endif
