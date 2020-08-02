
#ifndef CPIGLISTA_H
#define CPIGLISTA_H

#include "cpigcomponente.h"
#include "cpigitemlista.h"

#include <string>
#include <vector>

class CPigLista : public CPigComponente
{
public:

    CPigLista(int idComponente,int px, int py,int altura,int largura,int alturaItens,std::string nomeArq,int retiraFundo=1,int janela=0);
    CPigLista(std::string nomeArqParam);

    ~CPigLista();
    static CPigLista LeArquivoParametros(std::string nomeArqParam);
    int Desenha() override;
    int TrataEvento(PIG_Evento evento);
    int CriaItem(std::string texto,std::string imagem = "",int largImg = 0,int retiraFundoImg = 1);
    int GetPosItemMarcado();
    void SetRetanguloMarcacao(bool status);
    void SetFonteItensLista(int fonte);
    CPigItemLista *GetItemMarcado();
    CPigItemLista *GetItem(int indice);
    void Move(int nx,int ny);
    void SetPosItensLista(PIG_PosicaoComponente pos);

private:
    int fonteItens;
    int qntItens;
    int altItem;
    int itemMarcado;
    std::vector <CPigItemLista*> itens;
    bool retanguloMarcado;
    PIG_PosicaoComponente posItens;

    int OnMouseOn();
    int OnMouseOff();
    void DefineEstado(PIG_EstadoComponente estadoComponente);
    void IniciaBase(int alturaItens);
    void DesenhaRetanguloMarcacao();
    int GetItemSelecionado();
};

#endif
