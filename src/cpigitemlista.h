
#ifndef CPIGITEMLISTA_H
#define CPIGITEMLISTA_H

#include "cpigcomponente.h"

class CTimer;

class CPigItemLista : public CPigComponente
{

public:
    CPigItemLista(int idComponente,int px, int py, int altItem,int largItem,int larguraLista,int posXLista,std::string nomeArq, int retiraFundo=1,int janela=0);
    CPigItemLista(int idComponente,int px, int py,int altItem,int largItem,int larguraLista,int posXLista,int janela=0);
    int TrataEvento(PIG_Evento evento);
    int Desenha();
    void SetPosItem(PIG_PosicaoComponente pos);
    void Move(int nx,int ny);

private:
    int largBase;
    int xBase;
    CTimer *timer;
    PIG_PosicaoComponente posItem;

    void DefineEstado(PIG_EstadoComponente estadoComponente);
    int OnMouseOn();
    int OnMouseOff();

    int OnMouseClick();
    int MouseSobre(int mx, int my);
    int TrataMouse(int acao);
    void AlinhaDireita(int nx,int ny);
    void AlinhaEsquerda(int nx,int ny);
    void IniciaBase(int larguraLista,int posXLista);
};

#endif
