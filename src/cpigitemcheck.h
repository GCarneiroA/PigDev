
#ifndef CPIGITEMCHECK_H
#define CPIGITEMCHECK_H

#include "cpigcomponente.h"

class CTimer;

class CPigItemCheck : public CPigComponente
{
public:

    CPigItemCheck(int idComponente,int px, int py, int alt,int larg,std::string nomeArq,std::string labelItem,int retiraFundo=1,int janela=0);
    ~CPigItemCheck();
    bool GetMarcado();
    void SetMarcado(bool estadoMarcado);
    bool GetHabilitado();
    void SetHabilitado(bool estadoHabilitado);
    void DefineEstado(PIG_EstadoComponente estadoComponente)override;
    int TrataEvento(PIG_Evento evento);
    int Desenha();
    void AlinhaDireita(int largTotal);
    void AlinhaEsquerda(int largTotal);
    int SetPosicaoPadraoLabel(PIG_PosicaoComponente pos) override;
    int SetPosicaoPersonalizadaLabel(int rx, int ry) override;
private:
    CTimer *timer;
    int largFrame;
    bool marcado;

    int TrataMouse(int acao);
    int OnMouseOn();
    int OnMouseOff();
    int OnMouseClick();
};

#endif
