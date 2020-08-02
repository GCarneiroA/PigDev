
#include "cpigradiobox.h"

#include <fstream>

#include "cpigerroarquivo.h"
#include "cpigerroparametro.h"

    CPigRadioBox::CPigRadioBox(int idComponente, int posX, int posY, int largura,std::string nomeArqFundo,std::string nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo,int janela)
        : CPigBox(idComponente,posX,posY,largura,nomeArqFundo,nomeArqItem,alturaItem,larguraItem,espacoVertical,retiraFundo,janela)
    {
        itemMarcado = -1;
    }

    CPigRadioBox::CPigRadioBox(int idComponente, int posX, int posY, int largura,std::string nomeArqItem,int alturaItem, int larguraItem, int espacoVertical,int janela)
        : CPigBox(idComponente,posX,posY,largura,nomeArqItem,alturaItem,larguraItem,espacoVertical,janela)
    {
        itemMarcado = -1;
    }

    CPigRadioBox::CPigRadioBox(std::string nomeArqParam)
        : CPigRadioBox(LeArquivoParametros(nomeArqParam))
    {
    }

    CPigRadioBox CPigRadioBox::LeArquivoParametros(std::string nomeArqParam)
    {
        std::ifstream arquivo;
        int idComponente,px,py,alturaItem,larguraItem,largura,espacoVertical,retiraFundo=1,janela=0;
        std::string nomeArqFundo = "",nomeArqItem = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "largura") arquivo >> largura;
            if(variavel == "alturaItem") arquivo >> alturaItem;
            if(variavel == "larguraItem") arquivo >> larguraItem;
            if(variavel == "nomeArqFundo") arquivo >> nomeArqFundo;
            if(variavel == "nomeArqItem") arquivo >> nomeArqItem;
            if(variavel == "espacoVertical") arquivo >> espacoVertical;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
       if(nomeArqItem == "") throw CPigErroParametro("nomeArqItem",nomeArqParam);

       if(nomeArqFundo == ""){
            return CPigRadioBox(idComponente,px,py,largura,nomeArqItem,alturaItem,larguraItem,espacoVertical,retiraFundo);
       }else{
            return CPigRadioBox(idComponente,px,py,largura,nomeArqFundo,nomeArqItem,alturaItem,larguraItem,espacoVertical,retiraFundo);
       }

    }

    void CPigRadioBox::CriaItem(std::string itemLabel, bool itemHabilitado, int audio, std::string hintMsg, int retiraFundo)
    {
        alt =( espacoLinha*itens.size() ) + ( altItem*(itens.size()+1) );
        CPigItemCheck *item = new CPigItemCheck(itens.size(),x,y+(espacoLinha + altItem)*(itens.size()),altItem,largItem,nomeImgItem,itemLabel,retiraFundo,idJanela);
        itens.push_back(item);
        SetDimensoes(alt,larg);
        item->SetHint(hintMsg);
        if (audio==-1)
            audio = audioComponente;//audio padrao do radiobox
        item->SetAudio(audio);
        item->SetMarcado(false);
        item->SetHabilitado(itemHabilitado);
    }

    int CPigRadioBox::TrataEvento(PIG_Evento evento)
    {
        for (int i=0;i<itens.size();i++){
            if (itens[i]->TrataEvento(evento)==1 && itens[i]->GetMarcado()){
                itemMarcado = i;
            }
        }
        if (itemMarcado!=-1){
            for (int i=0;i<itens.size();i++){
                if (i!=itemMarcado)
                    itens[i]->SetMarcado(false);
            }
            return 1;
        }
        return 0;
    }

    int CPigRadioBox::GetMarcado()
    {
        return itemMarcado;
    }

    int CPigRadioBox::SetMarcado(int indice, bool marcado)
    {
        if (indice<0||indice>=itens.size()) return 0;
        if (marcado){
            itemMarcado = indice;
            for (CPigItemCheck* i: itens) i->SetMarcado(false);
        }
        itens[indice]->SetMarcado(marcado);
        return 1;
    }
