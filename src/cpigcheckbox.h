
#ifndef CPIGCHECKBOX_H
#define CPIGCHECKBOX_H

#include "cpigbox.h"

class CPigCheckBox: public CPigBox
{
public:

    CPigCheckBox(int idComponente, int posX, int posY, int largura, std::string nomeArqFundo,std::string nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1,int janela = 0);
    CPigCheckBox(int idComponente, int posX, int posY, int largura, std::string nomeArqItem,int alturaItem, int larguraItem, int espacoVertical,int janela = 0);
    CPigCheckBox(std::string nomeArqParam);
    
    static CPigCheckBox LeArquivoParametros(std::string nomeArqParam);
    void CriaItem(std::string itemLabel, bool itemMarcado = false, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1);
    int TrataEvento(PIG_Evento evento)override;
    void SetMarcadoTodos(bool marcado);
    int SetMarcadoItem(int indice, bool marcado);

    std::vector <int> GetItensMarcados();

};

#endif
