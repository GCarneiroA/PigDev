
#include "cpigscrollbar.h"

#include <fstream>

#include "pigfuncoesbasicas.h"
#include "cmouse.h"
#include "cpigerroarquivo.h"
#include "cpigerroparametro.h"


 int CPigScrollBar::AcaoSetas(int idBotao, void* pontObjeto){
        CPigScrollBar *scroll = (CPigScrollBar*) pontObjeto;
        if (idBotao==scroll->id+1){
            scroll->AvancaHandle(scroll->vAtual,-scroll->deltaBotao);
        }else if (idBotao==scroll->id+2){
            scroll->AvancaHandle(scroll->vAtual,scroll->deltaBotao);
        }
    }

/***************Novos M�todos**************/


/***************M�todos Modificados**************/

    void CPigScrollBar::AjustaOrientacao(){
        if(orientacao == HORIZONTAL){
            CVisual::SetDimensoes(largura,comprimento - (2*altBotoes));
            largReal = comprimento;
            altReal = largura;
            CVisual::Move(xOriginal+altBotoes,yOriginal);
            if(botao1 && botao2){
                botao1->Move(xOriginal,yOriginal);
                botao2->Move(xOriginal + comprimento - altBotoes,yOriginal);
            }
            handle->Move(xOriginal+altBotoes +porcentagemConcluida*largUtil,yOriginal);
            handle->SetDimensoes(largura,largHandle);
            SetValorMinMax(vMin,vMax);
        }else{
            CVisual::SetDimensoes(comprimento - (2*altBotoes),largura);
            largReal = largura;
            altReal = comprimento;
            CVisual::Move(xOriginal,yOriginal+altBotoes);
            if(botao1 && botao2){
                botao1->Move(xOriginal,yOriginal);
                botao2->Move(xOriginal,yOriginal + comprimento - altBotoes);
            }
            handle->Move(xOriginal,yOriginal + altBotoes+porcentagemConcluida*largUtil);
            handle->SetDimensoes(largHandle,largura);
            SetValorMinMax(vMin,vMax);
        }
        AvancaHandle(vAtual);
    }

    void CPigScrollBar::AjustaHandle(){
        if(orientacao == HORIZONTAL){
            if(orientacaoCrescimento)handle->Move(xOriginal+altBotoes +porcentagemConcluida*largUtil,yOriginal);
            else handle->Move(x + larg - largHandle - porcentagemConcluida*largUtil,yOriginal);
        }else{
            if(orientacaoCrescimento)handle->Move(xOriginal,yOriginal + altBotoes + porcentagemConcluida*largUtil);
            else handle->Move(xOriginal,yOriginal + altBotoes + alt - largHandle - porcentagemConcluida*largUtil);
        }
    }

    //Recebe um valor e move o handle de forma proporcional
    int CPigScrollBar::AvancaHandle(int novoValor,int delta){
        if(!orientacaoCrescimento) delta = -delta;
        vAtual = PIGLimitaValor(novoValor + delta,vMin,vMax);
        porcentagemConcluida = (1.0 * (vAtual - vMin))/(vMax - vMin);
        AjustaHandle();
        if (acao) acao(id,porcentagemConcluida,param);
    }

/*******************************************/
    void CPigScrollBar::TrataClickTrilha(int px,int py){
        if(orientacao == HORIZONTAL){
            if(orientacaoCrescimento)porcentagemConcluida = (1.0 * ((px - largHandle/2) - x))/(largUtil);
            else porcentagemConcluida = (1.0 * (x + larg - (px + largHandle/2)))/(largUtil);
        }else{
            if(orientacaoCrescimento) porcentagemConcluida = (1.0 * ((py - largHandle/2) - y))/(largUtil);
            else porcentagemConcluida = (1.0 * (y + alt - (py + largHandle/2)))/(largUtil);
        }

        AvancaHandle(porcentagemConcluida*(vMax - vMin) + vMin,0);
    }

    int CPigScrollBar::TrataBotoes(PIG_Evento evento){
        if(botao1 && botao2){
            if(botao1->TrataEvento(evento) || botao2->TrataEvento(evento)) return 1;
        }
        return 0;
    }

    int CPigScrollBar::TrataRodinha(PIG_Evento evento){
        if(evento.mouse.relY == 1){
            AvancaHandle(vAtual,deltaRodinha);
            return 1;
        }else{
            AvancaHandle(vAtual,-deltaRodinha);
            return 1;
        }
        return 0;
    }

    int CPigScrollBar::TrataMouse(PIG_Evento evento){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(orientacao == VERTICAL)
            if(evento.mouse.acao == MOUSE_RODINHA) return TrataRodinha(evento);

        if (agoraOn){
            if(evento.mouse.acao == MOUSE_PRESSIONADO){
                if(evento.mouse.botao == MOUSE_ESQUERDO){
                    if(evento.mouse.cliques == 1){
                        TrataClickTrilha(p.x,p.y);
                        handle->DefineEstado(COMPONENTE_ACIONADO);
                    }
                }
            }
            if(handle->GetEstado() == COMPONENTE_ACIONADO) TrataClickTrilha(p.x,p.y);

            if(evento.mouse.acao == MOUSE_LIBERADO) handle->DefineEstado(COMPONENTE_NORMAL);

            return 1;
        }
        return 0;
    }

    int CPigScrollBar::TrataTeclado(PIG_Evento evento){
        if(evento.teclado.acao == TECLA_PRESSIONADA){
            if(orientacao == HORIZONTAL){
                if(evento.teclado.tecla== TECLA_DIREITA) AvancaHandle(vAtual,deltaTeclado);
                if(evento.teclado.tecla == TECLA_ESQUERDA) AvancaHandle(vAtual,-deltaTeclado);
            }else{
                if(evento.teclado.tecla== TECLA_CIMA) AvancaHandle(vAtual,deltaTeclado);
                if(evento.teclado.tecla == TECLA_BAIXO) AvancaHandle(vAtual,-deltaTeclado);
            }
            return 1;
        }
        return 0;
    }

    void CPigScrollBar::DefineEstadoComponentes(PIG_EstadoComponente estado){
        if(botao1 && botao2){
            botao1->DefineEstado(estado);
            botao2->DefineEstado(estado);
        }
        handle->DefineEstado(estado);
    }

    int CPigScrollBar::OnMouseOn(){return 0;}
    int CPigScrollBar::OnMouseOff(){return 0;}


    CPigScrollBar::CPigScrollBar(int idComponente,int px, int py,int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle,int retiraFundoTrilha,int janela)
        : CPigComponente(idComponente,px,py,larguraTotal,comprimentoTotal,imgTrilha,retiraFundoTrilha,janela)
    {
            botao1 = botao2 = NULL;
            vMin = vAtual = 0;
            vMax = 100;
            porcentagemConcluida = 0;
            orientacao = HORIZONTAL;
            xOriginal = x;
            yOriginal = y;
            largReal = comprimento = comprimentoTotal;
            altReal = largura = larguraTotal;
            altBotoes = 0;
            deltaBotao = 1;
            deltaTeclado = deltaRodinha = 10;
            largHandle = larguraHandle;
            handle = new CPigBotao(0,x + altBotoes,y,largura,largHandle,imgHandle,retiraFundoHandle,idJanela);
            handle->DefineBotaoRepeticao(true);
            handle->DefineTempoRepeticao(0.01);
            largUtil = comprimento - (2*altBotoes) - largHandle;
            DefineEstado(COMPONENTE_NORMAL);
            acao = NULL;
            param = NULL;
            orientacaoCrescimento = true;
            setasAtivadas = true;
            AjustaOrientacao();
            AjustaHandle();
    }

    CPigScrollBar::CPigScrollBar(std::string nomeArqParam)
        : CPigScrollBar(LeArquivoParametros(nomeArqParam))
    {
    }

    CPigScrollBar::~CPigScrollBar(){
        if (botao1) delete botao1;
        if (botao2) delete botao2;
        delete handle;
    }

    CPigScrollBar CPigScrollBar::LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,larguraTotal,larguraHandle,comprimentoTotal,retiraFundoHandle=1,retiraFundoTrilha=1,janela=0;
        std::string imgHandle = "",imgTrilha = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPigErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "larguraTotal") arquivo >> larguraTotal;
            if(variavel == "larguraHandle") arquivo >> larguraHandle;
            if(variavel == "comprimentoTotal") arquivo >> comprimentoTotal;
            if(variavel == "imgHandle") arquivo >> imgHandle;
            if(variavel == "imgTrilha") arquivo >> imgTrilha;
            if(variavel == "retiraFundoHandle") arquivo >> retiraFundoHandle;
            if(variavel == "retiraFundoTrilha") arquivo >> retiraFundoTrilha;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

        if(imgHandle == "") throw CPigErroParametro("imgHandle",nomeArqParam);
        if(imgTrilha == "") throw CPigErroParametro("imgTrilha",nomeArqParam);

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPigScrollBar(idComponente,px,py,larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha,janela);
    }

    void CPigScrollBar::SetBotoes(int alturaBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1,int retiraFundoB2){
        if (botao1==NULL){
            botao1 = new CPigBotao(id + 1,xOriginal,yOriginal,alturaBotoes,largura,imgBotao1,retiraFundoB1,idJanela);
            botao2 = new CPigBotao(id + 2,xOriginal,yOriginal,alturaBotoes,largura,imgBotao2,retiraFundoB2,idJanela);
            botao1->DefineAcao(AcaoSetas,this);
            botao2->DefineAcao(AcaoSetas,this);
            botao1->DefineBotaoRepeticao(true);
            botao2->DefineBotaoRepeticao(true);
            botao1->DefineTempoRepeticao(0.01);
            botao2->DefineTempoRepeticao(0.01);
            altBotoes = alturaBotoes;
            largUtil = comprimento - (2*altBotoes) - largHandle;
            DefineEstado(estado);
            AjustaOrientacao();
        }
    }

    void CPigScrollBar::SetOrientacao(Pig_Orientacao novaOrientacao){
        orientacao = novaOrientacao;
        AjustaOrientacao();
    }

    int CPigScrollBar::TrataEvento(PIG_Evento evento){

        if(estado == COMPONENTE_DESABILITADO || estado == COMPONENTE_INVISIVEL) return -1;
        handle->TrataEvento(evento);
        if(TrataBotoes(evento))return 1;

        if(evento.tipoEvento == EVENTO_NULO) return 0;
        if(evento.tipoEvento == EVENTO_TECLADO && setasAtivadas) return TrataTeclado(evento);
        if(evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento);

        return 0;
    }

    void CPigScrollBar::DefineEstado(PIG_EstadoComponente estadoComponente){
        estado = estadoComponente;
        DefineEstadoComponentes(estado);
    }

/***************Novos M�todos**************/

    void CPigScrollBar::GetDimensoes(int &altura,int &largura)
    {
        altura = altReal;
        largura = largReal;
    }

    void CPigScrollBar::GetDimensoesTrilha(int &altura,int &largura){
        CVisual::GetDimensoes(altura,largura);
    }

    void CPigScrollBar::SetSetasAtivadas(bool estado){
        setasAtivadas = estado;
    }

    void CPigScrollBar::MudaOrientacaoCrescimento(){
        orientacaoCrescimento = !orientacaoCrescimento;
        AvancaHandle(vAtual);
    }

    void CPigScrollBar::SetDimensoes(int largura,int comprimento){
        this->largura = largura;
        this->comprimento = comprimento;
        largUtil = comprimento - (2*altBotoes) - largHandle;
        AjustaOrientacao();
    }

    void CPigScrollBar::Move(int px,int py){
        xOriginal = px;
        yOriginal = py;
        AjustaOrientacao();

    }


/***************M�todos Modificados**************/

    void CPigScrollBar::SetDeltas(int dBotao,int dRodinha,int dTeclado){
        deltaBotao = dBotao;
        deltaRodinha = dRodinha;
        deltaTeclado = dTeclado;
    }

/*******************************************/

    int CPigScrollBar::Desenha(){
        if(estado == COMPONENTE_INVISIVEL) return -1;

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        if(botao1 && botao2){
            botao1->Desenha();
            botao2->Desenha();
        }
        handle->Desenha();
        return 0;
    }

    int CPigScrollBar::GetValorAtual(){
        return vAtual;
    }

    void CPigScrollBar::SetValorMinMax(int minimo,int maximo){
        vMin = minimo;
        vMax = maximo;
        vAtual = PIGLimitaValor(vAtual, vMin,vMax);
        AvancaHandle(vAtual);
    }

    void CPigScrollBar::SetValorAtual(int valor){
        AvancaHandle(valor);
    }
