
#include "cpigcheckbox.h"

#include <fstream>

#include "cpigerroarquivo.h"
#include "cpigerroparametro.h"


CPigCheckBox::CPigCheckBox(int idComponente, int posX, int posY, int largura, std::string nomeArqFundo,std::string nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo,int janela)
    : CPigBox(idComponente,posX,posY,largura,nomeArqFundo,nomeArqItem,alturaItem,larguraItem,espacoVertical,retiraFundo,janela)
{
}

CPigCheckBox::CPigCheckBox(int idComponente, int posX, int posY, int largura, std::string nomeArqItem,int alturaItem, int larguraItem, int espacoVertical,int janela)
    : CPigBox(idComponente,posX,posY,largura,nomeArqItem,alturaItem,larguraItem,espacoVertical,janela)
{
}

CPigCheckBox::CPigCheckBox(std::string nomeArqParam)
    : CPigCheckBox(LeArquivoParametros(nomeArqParam))
{
}

    CPigCheckBox CPigCheckBox::LeArquivoParametros(std::string nomeArqParam){

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
            return CPigCheckBox(idComponente,px,py,largura,nomeArqItem,alturaItem,larguraItem,espacoVertical);
       }else{
            return CPigCheckBox(idComponente,px,py,largura,nomeArqFundo,nomeArqItem,alturaItem,larguraItem,espacoVertical);
       }

    }

    void CPigCheckBox::CriaItem(std::string itemLabel, bool itemMarcado, bool itemHabilitado, int audio, std::string hintMsg, int retiraFundo){
        alt =( espacoLinha*itens.size() ) + ( altItem*(itens.size()+1) );
        CPigItemCheck *item = new CPigItemCheck(itens.size(),x,y+(espacoLinha + altItem)*(itens.size()),altItem,largItem,nomeImgItem,itemLabel,retiraFundo,idJanela);
        itens.push_back(item);
        SetDimensoes(alt,larg);
        item->SetHint(hintMsg);
        if (audio==-1)
            audio = audioComponente;//audio padrao do componente
        item->SetAudio(audio);
        item->SetMarcado(itemMarcado);
        item->SetHabilitado(itemHabilitado);
    }

    int CPigCheckBox::TrataEvento(PIG_Evento evento){
        int resp = 0;
        for (CPigItemCheck* i: itens)
            resp += i->TrataEvento(evento);
         return resp;
    }

    void CPigCheckBox::SetMarcadoTodos(bool marcado){
        for (CPigItemCheck* i: itens)
            i->SetMarcado(false);
    }

    int CPigCheckBox::SetMarcadoItem(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return -1;
        itens[indice]->SetMarcado(marcado);
        return 1;
    }

    std::vector <int> CPigCheckBox::GetItensMarcados(){

        std::vector <int> resp;
        for(int i=0;i<itens.size();i++)
            if(itens[i]->GetMarcado())resp.push_back(i);

        return resp;

    }

