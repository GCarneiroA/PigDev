
#ifndef CPIGRADIOBOX_H
#define CPIGRADIOBOX_H

#include "cpigbox.h"

class CPigRadioBox : public CPigBox
{
public:
    CPigRadioBox(int idComponente, int posX, int posY, int largura,std::string nomeArqFundo,std::string nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1,int janela = 0);
    CPigRadioBox(int idComponente, int posX, int posY, int largura,std::string nomeArqItem,int alturaItem, int larguraItem, int espacoVertical,int janela = 0);
    CPigRadioBox(std::string nomeArqParam);
    static CPigRadioBox LeArquivoParametros(std::string nomeArqParam);
    void CriaItem(std::string itemLabel, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1);
    int TrataEvento(PIG_Evento evento)override;
    int GetMarcado();
    int SetMarcado(int indice, bool marcado);

private:
    int itemMarcado;
};

#endif
