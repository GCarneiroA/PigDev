
#include "cpigitemcheck.h"

#include "cmouse.h"
#include "cgerenciadoraudios.h"

#include "ctimer.h"

CPigItemCheck::CPigItemCheck(int idComponente,int px, int py, int alt,int larg,std::string nomeArq,std::string labelItem,int retiraFundo,int janela)
    : CPigComponente(idComponente,px,py,alt,larg,nomeArq,janela){
        timer = NULL;
        largFrame = largOriginal/6;
        marcado = false;
        SetPosicaoPadraoLabel(PIG_COMPONENTE_DIR_CENTRO);
        SetLabel(labelItem);
        DefineEstado(COMPONENTE_NORMAL);
    }

CPigItemCheck::~CPigItemCheck(){
        if (timer)
            delete timer;
    }

    bool CPigItemCheck::GetMarcado(){
        return marcado;
    }

    void CPigItemCheck::SetMarcado(bool estadoMarcado){
        marcado = estadoMarcado;
        DefineEstado(estado);
    }

    bool CPigItemCheck::GetHabilitado(){
        if (estado==COMPONENTE_DESABILITADO)
            return false;
        else return true;
    }

    void CPigItemCheck::SetHabilitado(bool estadoHabilitado){
        if (estadoHabilitado)
            DefineEstado(COMPONENTE_NORMAL);
        else DefineEstado(COMPONENTE_DESABILITADO);
    }

    void CPigItemCheck::DefineEstado(PIG_EstadoComponente estadoComponente){
        SDL_Rect r = {0,0,largFrame,altOriginal};
        estado = estadoComponente;
        switch(estado){
        case COMPONENTE_NORMAL:
            if (marcado)
                r.x = largFrame;
            break;
        case COMPONENTE_MOUSEOVER:
            if (marcado)
                r.x = 5*largFrame;
            else r.x = 4*largFrame;
            break;
        case COMPONENTE_DESABILITADO:
            if (marcado)
                r.x = 3*largFrame;
            else r.x = 2*largFrame;
            break;
        }
        DefineFrame(r);
    }

    int CPigItemCheck::TrataEvento(PIG_Evento evento){
        if (estado==COMPONENTE_DESABILITADO||estado==COMPONENTE_INVISIVEL)
            return -1;
        if (evento.tipoEvento==EVENTO_MOUSE){
            return TrataMouse(evento.mouse.acao);
        }else if (evento.tipoEvento==EVENTO_TECLADO){
            return 0;//TrataTeclado(evento);
        }

        return 0;
    }

    int CPigItemCheck::Desenha()
    {
        SDL_RenderCopyEx(renderer,text,&frame,&dest,-angulo,NULL,flip);
        DesenhaLabel();
        EscreveHint();
        return 0;
    }

    void CPigItemCheck::AlinhaDireita(int largTotal){
        Move(x+largTotal-larg,y);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_ESQ_CENTRO);
    }

    void CPigItemCheck::AlinhaEsquerda(int largTotal){
        Move(x-largTotal+larg,y);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_DIR_CENTRO);
    }

    //define a posi��o do label (dentre posi��es pr�-estabelecidas)
    int CPigItemCheck::SetPosicaoPadraoLabel(PIG_PosicaoComponente pos) {
        if (pos!=PIG_COMPONENTE_ESQ_CENTRO)
            pos = PIG_COMPONENTE_DIR_CENTRO;
        CPigComponente::SetPosicaoPadraoLabel(pos);
        return 0;
    }

    //define a posi��o do label (posi��o arbiraria, relativa � posi��o do componente)
    int CPigItemCheck::SetPosicaoPersonalizadaLabel(int rx, int ry) {
        return 0;
    }

    int CPigItemCheck::TrataMouse(int acao){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if (acao==MOUSE_PRESSIONADO){
            if (agoraOn){
                return OnMouseClick();
            }
        }
        return 0;
    }

    int CPigItemCheck::OnMouseOn(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_MOUSEOVER);
        return 1;
    }

    int CPigItemCheck::OnMouseOff(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_NORMAL);
        return 1;
    }

    int CPigItemCheck::OnMouseClick(){
        if (timer) delete timer;
        timer = new CTimer(false);
        marcado = !marcado;
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        DefineEstado(COMPONENTE_MOUSEOVER);
        return 1;
    }
