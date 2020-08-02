
#include "cpigdropdown.h"

#include <fstream>

#include "cpigerroarquivo.h"
#include "cpigerroparametro.h"

#include "cmouse.h"
#include "cgerenciadoraudios.h"

#include "ctimer.h"

CPigDropDown::CPigDropDown(int idComponente,int px, int py, int altura,int largura,int alturaLista,std::string nomeArq,std::string fundoLista,int retiraFundoLista,int retiraFundo,int janela)
    : CPigComponente(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela)
{

            posLista = PIG_COMPONENTE_BAIXO_CENTRO;
            marcado = false;
            timer = NULL;
            posLabel = PIG_COMPONENTE_CIMA_CENTRO;
            xLista = 0;
            yLista = 0;
            itemSelecionado = NULL;
            lista = new CPigLista(id + 1,x,y,alturaLista,largura,altura,fundoLista,retiraFundoLista,idJanela);
            lista->SetRetanguloMarcacao(false);

    }

CPigDropDown::CPigDropDown(std::string nomeArqParam)
    : CPigDropDown(LeArquivoParametros(nomeArqParam))
{
}

CPigDropDown::~CPigDropDown()
{
        if(lista) delete lista;
        if(itemSelecionado) delete itemSelecionado;
        if(timer) delete timer;
    }

    CPigDropDown CPigDropDown::LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,alturaLista,retiraFundoLista = 0,retiraFundo = 0,janela = 0;

        std::string nomeArq = "",fundoLista = "",variavel;

        arquivo.open(nomeArqParam);
        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "altura") arquivo >> altura;
            if(variavel == "largura") arquivo >> largura;
            if(variavel == "nomeArq") arquivo >> nomeArq;
            if(variavel == "fundoLista") arquivo >> fundoLista;
            if(variavel == "alturaLista") arquivo >> alturaLista;
            if(variavel == "retiraFundoLista") arquivo >> retiraFundoLista;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }
        arquivo.close();
       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        if(nomeArq == "") throw CPigErroParametro("nomeArq",nomeArqParam);
        if(fundoLista == "") throw CPigErroParametro("fundoLista",nomeArqParam);

        return CPigDropDown(idComponente,px,py,altura,largura,alturaLista,nomeArq,fundoLista,retiraFundoLista,retiraFundo,janela);

    }

    int CPigDropDown::TrataEvento(PIG_Evento evento)
    {

        if(marcado) TrataLista(evento);

        if(evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento.mouse.acao);

        return 0;
    }

    void CPigDropDown::CriaItem(std::string texto,std::string imagemSecundaria,int largImg,int retiraFundoImg)
    {
        lista->CriaItem(texto,imagemSecundaria,largImg,retiraFundoImg);
    }

    void CPigDropDown::SetItemSelecionado(int indice){
        itemSelecionado = lista->GetItem(indice);
    }

    void CPigDropDown::MoveLista(PIG_PosicaoComponente pos){

        int alturaLista,larguraLista;
        lista->GetDimensoes(alturaLista,larguraLista);
        posLista = pos;

        switch(pos){

        case PIG_COMPONENTE_BAIXO_DIR:
            lista->Move(x + larg,y - alturaLista);break;

        case PIG_COMPONENTE_BAIXO_CENTRO:
            lista->Move(x + (larg-larguraLista)/2,y - alturaLista);break;

        case PIG_COMPONENTE_BAIXO_ESQ:
            lista->Move(x - larguraLista,y - alturaLista);break;

        case PIG_COMPONENTE_CIMA_CENTRO:
            lista->Move(x + (larg-larguraLista)/2,y+alt);break;

        case PIG_COMPONENTE_CIMA_DIR:
            lista->Move(x + larg,y + alt);break;

        case PIG_COMPONENTE_CIMA_ESQ:
            lista->Move(x - larguraLista,y + alt);break;

        case PIG_COMPONENTE_DIR_CIMA:
            lista->Move(x + larg,y);break;

        case PIG_COMPONENTE_DIR_BAIXO:
            lista->Move(x + larg,y + alt - alturaLista);break;

        case PIG_COMPONENTE_DIR_CENTRO:
            lista->Move(x + larg,y + (alt - alturaLista)/2);break;

        case PIG_COMPONENTE_ESQ_CIMA:
            lista->Move(x - larguraLista,y);break;

        case PIG_COMPONENTE_ESQ_BAIXO:
            lista->Move(x - larguraLista,y + alt - alturaLista);break;

        case PIG_COMPONENTE_ESQ_CENTRO:
            lista->Move(x - larguraLista,y + (alt - alturaLista)/2);break;

        case PIG_COMPONENTE_PERSONALIZADA:
            lista->Move(xLista,yLista);break;

        }

    }

    void CPigDropDown::SetPosPersonalizadaLista(int posX,int posY){
        xLista = posX;
        yLista = posY;
        posLista = PIG_COMPONENTE_PERSONALIZADA;
        MoveLista(posLista);
    }

    void CPigDropDown::SetFonteItens(int fonte){
        lista->SetFonteItensLista(fonte);
    }

    CPigItemLista *CPigDropDown::GetItemMarcadoLista(){
        return lista->GetItemMarcado();
    }

    int CPigDropDown::GetPosItemMarcadoLista(){
        return lista->GetPosItemMarcado();
    }

    int CPigDropDown::Desenha(){

        SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,NULL,flip);
        if(itemSelecionado !=NULL) itemSelecionado->Desenha();

        if(marcado)lista->Desenha();
        DesenhaLabel();

    }

    void CPigDropDown::SetPosItensLista(PIG_PosicaoComponente pos){
        lista->SetPosItensLista(pos);
    }


    int CPigDropDown::OnMouseOn(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_MOUSEOVER);
        return 1;
    }

    int CPigDropDown::OnMouseOff(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_NORMAL);
        return 1;
    }

    void CPigDropDown::TrataLista(PIG_Evento evento){
        if(lista->TrataEvento(evento)){
            CPigItemLista *item = new CPigItemLista(*lista->GetItemMarcado());
            item->Move(x,y);
            if(itemSelecionado!=NULL) delete itemSelecionado;
            itemSelecionado = item;
            marcado = false;
        }
    }

    int CPigDropDown::OnMouseClick(){
        if (timer) delete timer;
        timer = new CTimer(false);
        marcado = !(marcado == true);
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        DefineEstado(COMPONENTE_MOUSEOVER);
        return 1;
    }

    int CPigDropDown::TrataMouse(int acao){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if (acao==MOUSE_PRESSIONADO){
            if(agoraOn)
                return OnMouseClick();
            else marcado = false;
        }

        return 0;
    }

    void CPigDropDown::DefineEstado(PIG_EstadoComponente estadoComponente){}
