
#ifndef CPIGBOX_H
#define CPIGBOX_H

#include "cpigcomponente.h"

#include "cpigitemcheck.h"

#include <vector>
#include <string>

#include "tipos_pig.h"

class CPigBox : public CPigComponente
{
public:
    CPigBox(int idComponente, int posX, int posY, int largura, std::string nomeArqFundo, std::string nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1,int janela = 0);
    CPigBox(int idComponente, int posX, int posY, int largura, std::string nomeArqItem,int alturaItem, int larguraItem, int espacoVertical,int janela = 0);
    ~CPigBox();
    void AlinhaDireita();
    void AlinhaEsquerda();
    int Desenha();
    int GetMarcadoItem(int indice);
    int SetAudioItem(int indice, int audio);
    int GetHabilitadoItem(int indice);
    int SetHabilitadoItem(int indice, bool habilitado);
    int SetHabilitado(bool habilitado);
    int SetLabelIndice(int indice, std::string label);
    void SetFonteHint(int fonte) override;
    void SetAudio(int audio) override;
    void Move(int nx,int ny);
    int OnMouseOn();
    int OnMouseOff();
    void DefineEstado(PIG_EstadoComponente estadoComponente);
    virtual int TrataEvento(PIG_Evento evento) = 0;

protected:
    int largItem,altItem;//altura e largura da imagem de cada item
    std::string nomeImgItem;//nome da imagem de cada item
    int espacoLinha; //espa�o vertical entre os itens
    PIG_PosicaoComponente posItens;
    std::vector<CPigItemCheck*> itens;

    void IniciaBase(int alturaItem, int larguraItem, int espacoVertical, std::string nomeArqItem);
};

#endif
