
#include "cpigareadetexto.h"

#include <SDL2/SDL_rect.h>

#include <fstream>

#include "cmouse.h"
#include "cpigerroarquivo.h"
#include "cpigerroparametro.h"
#include "cgerenciadorfontes.h"
#include "cgerenciadorjanelas.h"

CPigAreaDeTexto::CPigAreaDeTexto(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars,int retiraFundo,int janela)
    :CPigCaixaTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,false,retiraFundo,janela){ // A altura � um vetor, mas eu preciso dela, entao eu acabei colocando como o tamanho da fonte, qualquer coisa s� mudar aqui
            espacoEntreLinhas = 0;
            yCursor = yBase = yBaseOriginal = y+altura-altLetra - margemVertCima;
            xCursor = xBase = xBaseOriginal = x + margemHorEsq;
            largMax = largura;
            linhasPauta = false;
            corLinhasTexto = PRETO;
            scrollHorizontalAtivado = scrollVerticalAtivado = false;
            scrollHorizontal = scrollVertical = NULL;
            largReal = larg;
            altReal = alt;
            xOriginal = x;
            yOriginal = y;
            AjustaAlinhamento();
        }

CPigAreaDeTexto::CPigAreaDeTexto(std::string nomeArqParam):CPigAreaDeTexto(LeArquivoParametros(nomeArqParam)){}

CPigAreaDeTexto::~CPigAreaDeTexto(){
        linhas.clear();
    }

    CPigAreaDeTexto CPigAreaDeTexto::LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,maxCars = 200,retiraFundo=1,janela=0;
        std::string nomeArq = "",variavel;

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
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "maxCars") arquivo >> maxCars;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

        if(nomeArq == "") throw CPigErroParametro("nomeArq",nomeArqParam);

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPigAreaDeTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,retiraFundo,janela);

    }

/***************Novos M�todos**************/

    void CPigAreaDeTexto::SetScrollBarVertical(int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle,int retiraFundoTrilha){
        scrollVertical = new CPigScrollBar(id + 1,x + larg,y,larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha,idJanela);
        scrollVertical->SetOrientacao(VERTICAL);
        int posYUltLinha = yBase - ((espacoEntreLinhas + altLetra)*linhas.size());
        scrollVertical->SetValorMinMax(yBase,posYUltLinha);
        scrollVertical->MudaOrientacaoCrescimento();
        scrollVertical->SetSetasAtivadas(false);
        scrollVerticalAtivado = false;
        scrollVertical->DefineEstado(COMPONENTE_INVISIVEL);
        SetPosPadraoScrollVertical(PIG_COMPONENTE_DIR_CENTRO);
    }

    int CPigAreaDeTexto::SetBotoesScrollBarVertical(int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1,int retiraFundoB2){
        if(!scrollVertical) return -1;
        scrollVertical->SetBotoes(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
        return 1;
    }

    void CPigAreaDeTexto::SetScrollBarHorizontal(int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle,int retiraFundoTrilha){
        scrollHorizontal = new CPigScrollBar(id + 1,x,y - larguraTotal,larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha,idJanela);
        int maiorTamLinha = GetLarguraLinhaMaior();
        scrollHorizontal->SetValorMinMax(xBaseOriginal,xBaseOriginal + maiorTamLinha);
        scrollHorizontal->MudaOrientacaoCrescimento();
        scrollHorizontal->SetSetasAtivadas(false);
        scrollHorizontalAtivado = false;
        scrollHorizontal->DefineEstado(COMPONENTE_INVISIVEL);
        SetPosPadraoScrollHorizontal(PIG_COMPONENTE_BAIXO_CENTRO);
    }

    int CPigAreaDeTexto::SetBotoesScrollBarHorizontal(int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1,int retiraFundoB2){
        if(!scrollHorizontal) return -1;
        scrollHorizontal->SetBotoes(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
        return 1;
    }

    void CPigAreaDeTexto::SetPosPadraoScrollHorizontal(PIG_PosicaoComponente pos){
        scrollHorizontal->SetPosPadraoExternaComponente(pos,this);
    }

    void CPigAreaDeTexto::SetPosPadraoScrollVertical(PIG_PosicaoComponente pos){
        scrollVertical->SetPosPadraoExternaComponente(pos,this);
    }

    void CPigAreaDeTexto::Move(int px,int py){
        CVisual::Move(px,py);
        xOriginal = px;
        yOriginal = py;
        if(scrollHorizontal) scrollHorizontal->SetPosPadraoExternaComponente(scrollHorizontal->GetPosComponente(),this);
        if(scrollVertical) scrollVertical->SetPosPadraoExternaComponente(scrollVertical->GetPosComponente(),this);
        ResetaValoresBase();
    }

    void CPigAreaDeTexto::MoveScrollBarHorizontal(int px,int py){
        if(scrollHorizontal) scrollHorizontal->Move(px,py);
    }

    void CPigAreaDeTexto::MoveScrollBarVertical(int px,int py){
        if(scrollVertical) scrollVertical->Move(px,py);
    }

    void CPigAreaDeTexto::SetDimensoes(int altura,int largura){
        CVisual::SetDimensoes(altura,largura);
        largReal = largura;
        altReal = altura;
        ResetaValoresBase();
    }

/***************M�todos Modificados**************/

    int CPigAreaDeTexto::Desenha()
    {
        //imagem de fundo
        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        DesenhaMarcacaoMargem();

        if(scrollVertical) scrollVertical->Desenha();
        if(scrollHorizontal) scrollHorizontal->Desenha();

        SDL_Rect r={x+margemHorEsq,altJanela-y-alt+margemVertCima,larg-(margemHorEsq+margemHorDir),alt-(margemVertBaixo+margemVertCima)};
        SDL_RenderSetClipRect(renderer,&r);

        DesenhaCursor();//desenha o cursor (se estiver em edi��o)
        CGerenciadorFontes::EscreverLonga(texto,xBase,yBase,largMax,(espacoEntreLinhas + altLetra),fonteTexto,CPIG_TEXTO_ESQUERDA);
        if(linhasPauta) DesenhaLinhasHorizontais();

        //desbloqueia o desenho fora da area do componente
        SDL_RenderSetClipRect(renderer,NULL);

        DesenhaLabel();
        return 1;
    }

    void CPigAreaDeTexto::SetFonteTexto(int fonte) 
    {
        CPigCaixaTexto::SetFonteTexto(fonte);
        ResetaValoresBase();
    }

/*******************************************/

    //define a cor da linhas horizontais
    void CPigAreaDeTexto::SetLinhasAbaixoTexto(bool visivel,PIG_Cor cor){
        corLinhasTexto = cor;
        linhasPauta = visivel;
    }

    //define a largura m�xima do texto
    void CPigAreaDeTexto::SetLargMaxTexto(int largMaxTexto){
        largMax = largMaxTexto;
        AjustaAlinhamento();
    }

    int CPigAreaDeTexto::TrataEvento(PIG_Evento evento)
    {
        CPigCaixaTexto::TrataEvento(evento);
        if(scrollVerticalAtivado) TrataScrollBarVertical(evento);
        if(scrollHorizontalAtivado) TrataScrollBarHorizontal(evento);
        return 0;
    }

    //define o espa�amento entre as linhas
    void CPigAreaDeTexto::SetEspacoEntreAsLinhas(int espaco){
        espacoEntreLinhas = espaco;
    }

    int CPigAreaDeTexto::SetTexto(std::string frase)
    {
        CPigCaixaTexto::SetTexto(frase);
        AjustaAlinhamento();
        return 0;
    }

    void CPigAreaDeTexto::SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima){
        margemVertCima = vertCima;
        margemVertBaixo = vertBaixo;
        margemHorDir = horDir;
        margemHorEsq = horEsq;
        ResetaValoresBase();
        AjustaAlinhamento();
    }

    //recupera o texto separado em linhas
    std::vector<std::string> CPigAreaDeTexto::GetLinhasTexto(){
        return linhas;
    }





    //Recupera todo o texto da �rea
    std::string CPigAreaDeTexto::GetTextoVisivel(){
        return GetTexto();
    }

/***************Novos M�todos**************/

    void CPigAreaDeTexto::TrataScrollBarVertical(PIG_Evento evento){
        scrollVertical->TrataEvento(evento);

        int valorAtual = scrollVertical->GetValorAtual();
        if(valorAtual!=yBase){
            yBase = valorAtual;
            scrollVertical->SetValorMinMax(yBaseOriginal,yBaseOriginal + ((espacoEntreLinhas + altLetra)*(linhas.size()-1)));
            scrollVertical->SetValorAtual(yBase);
            yCursor = yBase - ( (espacoEntreLinhas + altLetra) * GetLinhaDeUmaPos(posCursor));
        }
    }

    void CPigAreaDeTexto::TrataScrollBarHorizontal(PIG_Evento evento){
        scrollHorizontal->TrataEvento(evento);

        int valorAtual = scrollHorizontal->GetValorAtual();
        if(xBase != valorAtual){
            xBase = valorAtual;
            std::string aux;
            int posInicial = GetPosInicialDeUmaLinha(GetLinhaDeUmaPos(posCursor));
            scrollHorizontal->SetValorMinMax(xBaseOriginal - GetLarguraLinhaMaior() + (larg - (margemHorDir+margemHorEsq)),xBaseOriginal);
            scrollHorizontal->SetValorAtual(xBase);
            aux.assign(GetTextoVisivel(),posInicial,posCursor - posInicial);
            xCursor = xBase + CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto);
        }
    }

    //Verifica se � necess�rio acionar a ScrollBarVertical quando o texto � modificado
    void CPigAreaDeTexto::AcionaScrollBarVertical(){
        int temp;
        scrollVerticalAtivado = ((espacoEntreLinhas + altLetra)*(linhas.size())) > (alt - (margemVertBaixo+margemVertCima));
        if(!scrollVerticalAtivado)scrollVertical->DefineEstado(COMPONENTE_INVISIVEL);
        else scrollVertical->DefineEstado(COMPONENTE_NORMAL);
    }

    //Verifica se � necess�rio acionar a ScrollBarHorizontal quando o texto � modificado
    void CPigAreaDeTexto::AcionaScrollBarHorizontal(){
        int temp;
        scrollHorizontalAtivado = GetLarguraLinhaMaior() > (larg - (margemHorDir+margemHorEsq));
        if(!scrollHorizontalAtivado)scrollHorizontal->DefineEstado(COMPONENTE_INVISIVEL);
        else scrollHorizontal->DefineEstado(COMPONENTE_NORMAL);
    }

    int CPigAreaDeTexto::GetLarguraLinhaMaior(){
        int tamMaior = 0;
        int temp = 0;
        for(std::string linha : linhas){
            temp = CGerenciadorFontes::GetLarguraPixels(linha,fonteTexto);
            tamMaior = (temp > tamMaior) ? (temp):(tamMaior);
        }
        return tamMaior;
    }


/***************M�todos Modificados**************/

    //Desenha um contorno baseado nas dimensoes reais da �rea(somando a �rea em si e a scroll bar)
    void CPigAreaDeTexto::DesenhaMarcacaoMargem(){
        CGerenciadorJanelas::DesenhaLinhaSimples(x+margemHorEsq,y+margemVertBaixo,x+ margemHorEsq,y+alt-margemVertCima,BRANCO);
        CGerenciadorJanelas::DesenhaLinhaSimples(x+larg-margemHorDir,y+margemVertBaixo,x+larg-margemHorDir,y+alt-margemVertCima,BRANCO);

        CGerenciadorJanelas::DesenhaLinhaSimples(x+margemHorEsq,y+alt-margemVertCima,x+larg-margemHorDir,y+alt-margemVertCima,BRANCO);
        CGerenciadorJanelas::DesenhaLinhaSimples(x+margemHorEsq,y+margemVertBaixo,x+larg-margemHorDir,y+margemVertBaixo,BRANCO);
    }

    //Volta a base e o cursor para o in�cio
    void CPigAreaDeTexto::ResetaValoresBase(){
        yCursor = yBase = yBaseOriginal = y+alt-altLetra-margemVertCima;
        xCursor = xBase = xBaseOriginal = x + margemHorEsq;
        AjustaAlinhamento();
    }

    //Serve no caso em que o y do cursor fica fora da �rea vis�vel
    void CPigAreaDeTexto::AjustaBaseTextoEixoY(){
        while(yCursor < y + margemVertBaixo){
            yBase+=1;
            yCursor+=1;
        }
        while(yCursor > y + alt - altLetra - margemVertCima){
            yBase-=1;
            yCursor-=1;
        }
    }

    //Ajusta o alinhamento do texto quando ocorre alguma modifica��o
    void CPigAreaDeTexto::AjustaAlinhamento() 
    {
        std::string textoBase = GetTextoVisivel();
        std::string aux;

        linhas = CGerenciadorFontes::ExtraiLinhasString(textoBase,largMax,fonteTexto);

        int linhaPos = GetLinhaDeUmaPos(posCursor);
        int posInicial = GetPosInicialDeUmaLinha(linhaPos);

        aux.assign(textoBase,posInicial,posCursor - posInicial);

        yCursor = yBase - ( (espacoEntreLinhas + altLetra)*GetLinhaDeUmaPos(posCursor));
        xCursor = xBase + CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto);

        if(scrollVertical) AcionaScrollBarVertical();
        if(scrollHorizontal) AcionaScrollBarHorizontal();

        AjustaBaseTextoEixoX(CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto));
        AjustaBaseTextoEixoY();

        if(scrollHorizontalAtivado) scrollHorizontal->SetValorAtual(xBase);
        if(scrollVerticalAtivado) scrollVertical->SetValorAtual(yBase);

    }

/*******************************************/

    //trata o evento do botao esquerdo
    int CPigAreaDeTexto::TrataMouseBotaoEsquerdo(SDL_Point p,int inicioLinha){
        int posInicial = GetPosInicialDeUmaLinha(GetLinhaComMouseEmCima());
        int linha = GetLinhaComMouseEmCima();
        //printf("pos %d linha %d\n",posInicial,linha);
        TrataMouseBotaoEsquerdoESobeDesceCursor(p,posInicial,linha);
        return 0;
    }

    //Trata evento botao esquerdo e sobe e desce o cursor pelas setas
    int CPigAreaDeTexto::TrataMouseBotaoEsquerdoESobeDesceCursor(SDL_Point p,int inicioLinha,int linha){
        int delta = p.x-xBase;

        if(linha!=-1){
            if(delta < CGerenciadorFontes::GetLarguraPixels(linhas[linha],fonteTexto)){
                CPigCaixaTexto::TrataMouseBotaoEsquerdo(p,inicioLinha);
            }else{
                posCursor = inicioLinha + linhas[linha].size();
            }
        }

        AjustaAlinhamento();
        if (estado==COMPONENTE_NORMAL)
            DefineEstado(COMPONENTE_EDITANDO);

        return 1;
    }


    int CPigAreaDeTexto::TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p)
    {
        return 1;
    }//n�o usa o bot�o direito

    //
    int CPigAreaDeTexto::GetLinhaComMouseEmCima(){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        int yLinha=0;

        for(int i=0;i<linhas.size();i++){

            yLinha = yBase - ((espacoEntreLinhas + altLetra)*i);
            if(p.y > yLinha && p.y <(yLinha + (espacoEntreLinhas + altLetra)) ){
                return i;
            }
        }
        return linhas.size()-1;
    }

    //
    int CPigAreaDeTexto::GetPosInicialDeUmaLinha(int linha){
        if (linhas.size()==0) return 0;
        int posPercorridas = 0;

        for(int i=0;i<linhas.size();i++){
            if(linha == i){
                return posPercorridas;
            }

            posPercorridas += linhas[i].size();
        }

        return posPercorridas - linhas[linhas.size()-1].size();
    }

    //
    int CPigAreaDeTexto::GetLinhaDeUmaPos(int pos){
        if (linhas.size()==0) return 0;
        int qntLinhas = 0;

        for(int i=0;i<linhas.size();i++){
            qntLinhas+=linhas[i].size();

            if(qntLinhas >= pos){
                return i;
            }
        }

        return 0;
    }

    //
    void CPigAreaDeTexto::DesenhaLinhasHorizontais(){
        int yLinha = yBase;
        int xLinha = x;
        int i=0;

        while(yLinha >= y){
            CGerenciadorJanelas::DesenhaLinhaSimples(xLinha,yLinha,xLinha+larg,yLinha,corLinhasTexto);
            i++;
            yLinha = yBase - ((espacoEntreLinhas + altLetra) *i);
        }
    }

    //move o cursor uma linha para cima
    int CPigAreaDeTexto::SobeCursor(){
        SDL_Point p;
        p.x = xCursor;
        p.y = yCursor;
        int total =0;

        int linhaCursor = GetLinhaDeUmaPos(posCursor);

        if(linhaCursor > 0) return TrataMouseBotaoEsquerdoESobeDesceCursor(p,GetPosInicialDeUmaLinha(linhaCursor-1),linhaCursor-1);

        return 0;

    }

    //move o cursor uma linha para baixo
    int CPigAreaDeTexto::DesceCursor(){
        SDL_Point p;
        p.x = xCursor;
        p.y = yCursor;

        int linhaCursor = GetLinhaDeUmaPos(posCursor);

        if(linhaCursor < linhas.size()-1 ) return TrataMouseBotaoEsquerdoESobeDesceCursor(p,GetPosInicialDeUmaLinha(linhaCursor+1),linhaCursor+1);

        return 0;

    }

    //PulaLinha com Enter
    int CPigAreaDeTexto::PulaLinha()
    {
        std::string aux = "";
        std::string auxB = "";

        aux.assign(texto,0,posCursor);
        auxB += aux;
        auxB += '\n';
        aux.assign(texto,posCursor,texto.size() - posCursor);
        auxB +=aux;

        texto = auxB;
        AvancaCursor();
        
        return 0;
    }
