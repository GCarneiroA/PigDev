
#ifndef CPIGDROPDOWN_H
#define CPIGDROPDOWN_H

#include "cpigcomponente.h"

#include "cpiglista.h"
#include "cpigitemlista.h"

class CTimer;

class CPigDropDown : public CPigComponente
{
public:
    CPigDropDown(int idComponente,int px, int py, int altura,int largura,int alturaLista,std::string nomeArq,std::string fundoLista,int retiraFundoLista,int retiraFundo=1,int janela=0);
    CPigDropDown(std::string nomeArqParam);
    ~CPigDropDown();

    static CPigDropDown LeArquivoParametros(std::string nomeArqParam);
    int TrataEvento(PIG_Evento evento)override;
    void CriaItem(std::string texto,std::string imagemSecundaria = "",int largImg = 0,int retiraFundoImg = 1);
    void SetItemSelecionado(int indice);
    void MoveLista(PIG_PosicaoComponente pos);
    void SetPosPersonalizadaLista(int posX,int posY);
    void SetFonteItens(int fonte);
    CPigItemLista *GetItemMarcadoLista();
    int GetPosItemMarcadoLista();
    int Desenha();
    void SetPosItensLista(PIG_PosicaoComponente pos);

private:
    int OnMouseOn();
    int OnMouseOff();
    void TrataLista(PIG_Evento evento);
    int OnMouseClick();
    int TrataMouse(int acao);
    void DefineEstado(PIG_EstadoComponente estadoComponente);

    CPigLista *lista;
    PIG_PosicaoComponente posLista;
    bool marcado;
    int xLista,yLista;
    CTimer *timer;
    CPigItemLista *itemSelecionado;
};

#endif
