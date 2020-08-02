
#include "cpigbotao.h"

#include <fstream>

#include "cmouse.h"
#include "cgerenciadoraudios.h"

#include "ctimer.h"

CPigBotao::CPigBotao(int idComponente,int px, int py, int alt,int larg,std::string nomeArq, int retiraFundo,int janela):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
            tecla = -1;//sem tecla de atalho
            acao = NULL;//n�o tem a��o registrada
            param = NULL;//n�o tem par�metro associado � a��o
            largFrame = largOriginal/4;
            DefineEstado(COMPONENTE_NORMAL);
            tempoRepeticao = 0.2;
            botaoRepeticao = false;
            SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
            timer = new CTimer(false);
        }

CPigBotao::CPigBotao(std::string nomeArqParam):CPigBotao(LeArquivoParametros(nomeArqParam)){
    }

    CPigBotao::~CPigBotao(){
        delete timer;
    }

    void CPigBotao::DefineAcao(AcaoBotao funcao,void *parametro){
        acao = funcao;
        param = parametro;
    }

    void CPigBotao::DefineAtalho(int teclaAtalho){
        tecla = teclaAtalho;
    }

    void CPigBotao::DefineCursor(PIG_EstadoComponente estado, int indiceMouse){
        //mouse[estado]=indiceMouse;
    }

    void CPigBotao::DefineTempoRepeticao(double segundos){
        tempoRepeticao = segundos;
    }

    void CPigBotao::DefineBotaoRepeticao(bool repeticao){
        botaoRepeticao = repeticao;
    }

    void CPigBotao::DefineEstado(PIG_EstadoComponente estadoComponente){
        SDL_Rect r={0,0,largFrame,altOriginal};
        estado = estadoComponente;
        switch(estado){
        case COMPONENTE_NORMAL:
            break;
        case COMPONENTE_MOUSEOVER:
            r.x += largFrame;
            break;
        case COMPONENTE_ACIONADO:
            r.x += 2*largFrame;
            break;
        case COMPONENTE_DESABILITADO:
            r.x += 3*largFrame;
            break;
        }
        DefineFrame(r);
    }

    int CPigBotao::TrataEvento(PIG_Evento evento){
        if (estado == COMPONENTE_DESABILITADO || estado == COMPONENTE_INVISIVEL) return -1;
        if (evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento);
        if (evento.tipoEvento == EVENTO_TECLADO) return TrataTeclado(evento);
        return 0;
    }

    int CPigBotao::Desenha(){

        if (estado==COMPONENTE_INVISIVEL) return 0;

        TrataTimer();

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        DesenhaLabel();
        EscreveHint();

        return 1;
    }



    int CPigBotao::TrataMouse(PIG_Evento evento){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn){
            if (evento.mouse.acao==MOUSE_PRESSIONADO)
                return OnMouseClick();
        }

        return 0;
    }

    int CPigBotao::TrataTeclado(PIG_Evento evento){
        if (evento.teclado.acao==TECLA_PRESSIONADA&&evento.teclado.tecla==tecla)
            if (timer->GetTempoDecorrido()>tempoRepeticao)
                return OnMouseClick();

        return 0;
    }

    void CPigBotao::TrataTimer(){
        //if (timer->GetTempoDecorrido()<tempoRepeticao){
            //if(estado!=COMPONENTE_DESABILITADO)
            //    DefineEstado(COMPONENTE_ACIONADO);
        if (timer->GetTempoDecorrido()>=tempoRepeticao){
            if (estado==COMPONENTE_ACIONADO){
                if (agoraOn){
                    if (botaoRepeticao&&CMouse::GetEstadoBotaoEsquerdo()==MOUSE_PRESSIONADO){
                        OnMouseClick();
                    }else DefineEstado(COMPONENTE_MOUSEOVER);
                }else DefineEstado(COMPONENTE_NORMAL);
            }
        }
    }

    int CPigBotao::OnMouseClick(){
        DefineEstado(COMPONENTE_ACIONADO);
        timer->Reinicia(false);
        if (acao) acao(id,param);//rever se NULL � necess�rio
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return 1;
    }

    int CPigBotao::OnMouseOn(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_MOUSEOVER);
        return 1;
    }

    int CPigBotao::OnMouseOff(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_NORMAL);
        return 1;
    }

    CPigBotao CPigBotao::LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,retiraFundo = 0,janela = 0;

        std::string nomeArq = "",variavel,valor,palavra;

        arquivo.open(nomeArqParam);
        //if(!arquivo.is_open()) printf("falha ler arquivo\n");
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> palavra;
            if(palavra == "idComponente") arquivo >> idComponente;
            if(palavra == "px") arquivo >> px;
            if(palavra == "py") arquivo >> py;
            if(palavra == "altura") arquivo >> altura;
            if(palavra == "largura") arquivo >> largura;
            if(palavra == "nomeArq") arquivo >> nomeArq;
            if(palavra == "retiraFundo") arquivo >> retiraFundo;
            if(palavra == "janela") arquivo >> janela;
        }
        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        return CPigBotao(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela);
    }

