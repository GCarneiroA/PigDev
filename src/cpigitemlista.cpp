
#include "cpigitemlista.h"
#include "cmouse.h"
#include "cgerenciadoraudios.h"
#include "ctimer.h"

CPigItemLista::CPigItemLista(int idComponente,int px, int py, int altItem,int largItem,int larguraLista,int posXLista,std::string nomeArq, int retiraFundo,int janela)
    : CPigComponente(idComponente,px,py,altItem,largItem,nomeArq,retiraFundo,janela){
            IniciaBase(larguraLista,posXLista);
    }

CPigItemLista::CPigItemLista(int idComponente,int px, int py,int altItem,int largItem,int larguraLista,int posXLista,int janela):
        CPigComponente(idComponente,px,py,altItem,largItem,janela){
            IniciaBase(larguraLista,posXLista);
    }

    int CPigItemLista::TrataEvento(PIG_Evento evento){

        if (evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento.mouse.acao);

        return 0;
    }

    int CPigItemLista::Desenha(){

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);
        DesenhaLabel();

        return 1;
    }

    void CPigItemLista::SetPosItem(PIG_PosicaoComponente pos){
        posItem = pos;
        Move(xBase,y);
    }

    void CPigItemLista::Move(int nx,int ny){
        if(posItem == PIG_COMPONENTE_DIR_CENTRO) AlinhaDireita(nx,ny);
        if(posItem == PIG_COMPONENTE_ESQ_CENTRO) AlinhaEsquerda(nx,ny);
        xBase = nx;
    }



    void CPigItemLista::DefineEstado(PIG_EstadoComponente estadoComponente){}
    int CPigItemLista::OnMouseOn(){return 0;}
    int CPigItemLista::OnMouseOff(){return 0;}

    int CPigItemLista::OnMouseClick(){
        DefineEstado(COMPONENTE_ACIONADO);
        if (timer) delete timer;
        timer = new CTimer(false);
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return 1;
    }

    int CPigItemLista::MouseSobre(int mx, int my){
        SDL_Point p={mx,my};
        SDL_Rect r={xBase,y,largBase,alt};

        antesOn = agoraOn;
        agoraOn = SDL_PointInRect(&p,&r);
        if (agoraOn&&!antesOn){
            OnMouseOn();
            return 1;
        }else if(!agoraOn&&antesOn){
            OnMouseOff();
            return -1;
        }
        return 0;
    }

    int CPigItemLista::TrataMouse(int acao){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn)
            if (acao==MOUSE_PRESSIONADO) return OnMouseClick();

        return 0;
    }

    void CPigItemLista::AlinhaDireita(int nx,int ny){
        CVisual::Move(nx+largBase-larg,ny);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_ESQ_CENTRO);
    }

    void CPigItemLista::AlinhaEsquerda(int nx,int ny){
        CVisual::Move(nx,ny);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_DIR_CENTRO);
    }

    void CPigItemLista::IniciaBase(int larguraLista,int posXLista){

        timer = NULL;
        largBase = larguraLista;
        xBase = posXLista;
        posItem = PIG_COMPONENTE_ESQ_CENTRO;

    }
