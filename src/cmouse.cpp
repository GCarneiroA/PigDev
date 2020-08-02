
#include "cmouse.h"
#include "cpigcursor.h"

int CMouse::cursorAtual;
bool CMouse::cursorProprio;
CPIGCursor *CMouse::cursores[MAX_CURSORES];
int CMouse::mx;
int CMouse::my;
int CMouse::estadoBotaoDireito;
int CMouse::estadoBotaoEsquerdo;
int CMouse::estadoBotaoCentral;

    void CMouse::Inicia(bool cursorCustomizado){
        cursorAtual = -1;
        cursorProprio = cursorCustomizado;
        SDL_ShowCursor(cursorProprio==false);
        for (int i=0;i<MAX_CURSORES;i++)
            cursores[i] = NULL;
    }

    void CMouse::Encerra(){
        for (int i=0;i<MAX_CURSORES;i++){
            if (cursores[i])
                delete cursores[i];
        }
    }

    int CMouse::GetEstadoBotaoDireito(){
        return estadoBotaoDireito;
    }

    int CMouse::GetEstadoBotaoCentral(){
        return estadoBotaoCentral;
    }

    int CMouse::GetEstadoBotaoEsquerdo(){
        return estadoBotaoEsquerdo;
    }

    void CMouse::PegaXY(int &x, int &y){
        x = mx;
        y = my;
    }

    void CMouse::ProcessaEvento(PIG_Evento evento){
        if (evento.tipoEvento!=EVENTO_MOUSE) {
            return;
        }
        if (evento.mouse.acao==MOUSE_PRESSIONADO||evento.mouse.acao==MOUSE_LIBERADO){
            switch(evento.mouse.botao){
            case MOUSE_DIREITO: estadoBotaoDireito = evento.mouse.acao;break;
            case MOUSE_CENTRAL: estadoBotaoCentral = evento.mouse.acao;break;
            case MOUSE_ESQUERDO: estadoBotaoEsquerdo = evento.mouse.acao;break;
            }
        }else if (evento.mouse.acao==MOUSE_MOVIDO){
            Move(evento.mouse.posX,evento.mouse.posY,evento.mouse.numeroJanela);
        }

    }

    void CMouse::MudaCursor(int indice){
        cursorAtual = indice;
    }

    void CMouse::Desenha(int idJanela){
        if (cursorAtual==-1) return;
        cursores[cursorAtual]->Desenha();
    }

    void CMouse::Move(int x,int y, int idJanela){
        mx = x;
        my = y;
        if (cursorAtual==-1) return;
        cursores[cursorAtual]->Move(x,y-32);
    }

    void CMouse::CarregaCursor(int indice,std::string nomeArquivo,int idJanela){
        if (cursores[indice]) delete cursores[indice];
        cursores[indice] = new CPIGCursor(nomeArquivo,1,idJanela);
        cursores[indice]->SetDimensoes(32,32);
        if (cursorAtual==-1) cursorAtual=indice;
    }
