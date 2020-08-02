
#include "cpigcaixatexto.h"

#include "cmouse.h"
#include "cgerenciadorfontes.h"
#include "cgerenciadorjanelas.h"
#include "cgerenciadoraudios.h"

#include "pigfuncoesbasicas.h"

#include "ctimer.h"


CPigCaixaTexto::CPigCaixaTexto(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars,bool apenasNumeros,int retiraFundo,int janela):
        CPigComponente(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela){
        margemHorEsq = margemHorDir = margemVertCima = margemVertBaixo = 0;
        posLabel = PIG_COMPONENTE_ESQ_BAIXO;//posi��o padr�o do label
        //altLetra = CGerenciadorFontes::GetTamanhoBaseFonte(fonteTexto)+CGerenciadorFontes::GetFonteDescent(fonteTexto);
        posCursor = 0;//cursor no in�cio do texto
        cursorExibido = true;
        timer = NULL;//o timer s� ser� criado quando estiver editando
        SetFonteTexto(0);
        estado = COMPONENTE_NORMAL;
        maxCaracteres = maxCars;
        somenteNumeros = apenasNumeros;
        corCursor = PRETO;
    }

CPigCaixaTexto::~CPigCaixaTexto(){
        if (timer) delete timer;
    }

    //define o texto a ser mostrado no componente
    int CPigCaixaTexto::SetTexto(std::string frase){
        texto = frase;
        posCursor=0;
        return 1;
    }

    void CPigCaixaTexto::SetFonteTexto(int fonte){
        fonteTexto = fonte;
        altLetra = CGerenciadorFontes::GetTamanhoBaseFonte(fonteTexto)+CGerenciadorFontes::GetFonteDescent(fonteTexto);
        yBaseOriginal = y+alt-altLetra;
        //AjustaAlinhamento();
    }

    //recupera o texto armazenado no componente
    std::string CPigCaixaTexto::GetTexto(){
        return texto;
    }

    //trata eventos relativos ao componente
    int CPigCaixaTexto::TrataEvento(PIG_Evento evento){
        if (evento.tipoEvento==EVENTO_MOUSE){
            return TrataEventoMouse(evento);
        }else if (evento.tipoEvento==EVENTO_TECLADO){
            return TrataEventoTeclado(evento);
        }
    }

    //define a cor do cursor
    void CPigCaixaTexto::SetCorCursor(PIG_Cor cor){
        corCursor = cor;
    }

    //define o estado do componente
    void CPigCaixaTexto::DefineEstado(PIG_EstadoComponente estadoComponente){
        estado = estadoComponente;
        if (estado==COMPONENTE_EDITANDO){
            timer = new CTimer(false);
            SDL_StartTextInput();
        }else if (estado==COMPONENTE_NORMAL){
            SDL_StopTextInput();
            if (timer) delete timer;
        }
    }

    //reposiciona o componente
    void CPigCaixaTexto::Move(int nx, int ny){
        CPigComponente::Move(nx,ny);
        AjustaAlinhamento();
    }

    //desenha o cursor
    void CPigCaixaTexto::DesenhaCursor(){
        if (estado==COMPONENTE_EDITANDO){
            if (cursorExibido){
                CGerenciadorJanelas::DesenhaLinhaSimples(xCursor,yCursor,xCursor,yCursor+altLetra,corCursor,idJanela);
            }
            if (timer&&timer->GetTempoDecorrido()>1){
                cursorExibido = !cursorExibido;
                timer->Reinicia(false);
            }
        }
    }

    //trata os eventos de mouse poss�veis
    int CPigCaixaTexto::EventosMouse(PIG_Evento evento,SDL_Point p){
        if (evento.mouse.acao == MOUSE_PRESSIONADO){
            if (evento.mouse.botao == MOUSE_ESQUERDO)
                return TrataMouseBotaoEsquerdo(p);
            else if (evento.mouse.botao == MOUSE_DIREITO)
                return TrataMouseBotaoDireito(evento,p);
        }
    }

    //verifica se o evento ocorre dentro da �rea do componente
    int CPigCaixaTexto::TrataEventoMouse(PIG_Evento evento){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        SDL_Rect r = {x + margemHorEsq,y + margemVertBaixo,larg - (margemHorDir + margemHorEsq),alt - (margemVertBaixo + margemVertCima)};

        if (SDL_PointInRect(&p,&r)){
            return EventosMouse(evento,p);
        }
        return 0;
    }

    //trata teclas de movimenta��o do cursor
    int CPigCaixaTexto::TrataTeclasEspeciais(PIG_Evento evento){
        switch (evento.teclado.tecla){
            case TECLA_BACKSPACE:
                RetiraTextoBackSpace();return 1;
            case TECLA_DELETE:
                RetiraTextoDelete();return 1;
            case TECLA_DIREITA:
                AvancaCursor();return 1;
            case TECLA_ESQUERDA:
                VoltaCursor();return 1;
            case TECLA_CIMA:
                SobeCursor();return 1;
            case TECLA_BAIXO:
                DesceCursor();return 1;
            case TECLA_ENTER:
                PulaLinha();return 1;
        }
        return 0;
    }

    //trata os diversos tipos de eventos de teclado que podem ocorrer
    int CPigCaixaTexto::TrataEventoTeclado(PIG_Evento evento){
        if (evento.teclado.acao==TECLA_EDICAO) return 1;
        if (evento.teclado.acao==TECLA_INPUT){//caracteres normais
            if (AdicionaTexto( ConverteString(evento.teclado.texto).c_str() ) ){
                if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
                return 1;
            }
            return 0;
        }

        if (evento.teclado.acao==TECLA_PRESSIONADA){//teclas especiais
            TrataTeclasEspeciais(evento);
            return 1;
        }
        return 0;
    }

    //posiciona o cursor no eixo X (necess�rio, pois pode haver texto "escondido" � esquerda)
    void CPigCaixaTexto::AjustaBaseTextoEixoX(int largParcial){
        while(xCursor>x+larg - margemHorDir){
            xBase-=1;
            xCursor = xBase + largParcial;
        }
        while(xCursor <= x + margemHorEsq){
            xBase+=1;
            xCursor = xBase + largParcial;
        }
    }

    //posiciona o cursor uma posi��o � frente
    int CPigCaixaTexto::AvancaCursor(){
        if (posCursor>=texto.size()) return 0;//n�o tem caracter na frente do cursor
        posCursor++;
        AjustaAlinhamento();
        return 1;
    }

    //posiciona o cursor uma posi��o atr�s
    int CPigCaixaTexto::VoltaCursor(){
        if (posCursor==0) return 0;//n�o tem caractere atr�s do cursor
        posCursor--;
        AjustaAlinhamento();
        return 1;
    }

    //reira um caracter com a tecla backspace
    int CPigCaixaTexto::RetiraTextoBackSpace(){
        if (texto.size()==0||posCursor==0) return 0;//n�o tem caractere atr�s do cursor

        texto.erase(posCursor-1,1);//retira o caracter imediatamente atr�s do cursor e retrocede com ele
        VoltaCursor();

        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return 1;
    }

    //retira um caracter com a tecla delete
    int CPigCaixaTexto::RetiraTextoDelete(){
        if (texto.size()==0||posCursor>=texto.size()) return 0;//n�o tem caracter na frente do cursor

        texto.erase(posCursor,1);//retira o caracter imediatamente a frente do cursor

        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return 1;
    }

    //adiciona um texto (caracter ou string) na posi��o indicada pelo cursor (se poss�vel)
    int CPigCaixaTexto::AdicionaTexto(std::string frase){
        if (texto.size()+frase.size()>maxCaracteres) return 0;//ultrapassa o limite m�ximo de carcteres
        if (somenteNumeros&&!PIGSomenteNumeros(frase)) return 0;//n�o � n�mero

        texto.insert(posCursor,frase);

        AvancaCursor();
        return 1;
    }

    //converte caracteres especiais, como acentos por exemplo
    std::string CPigCaixaTexto::ConverteString(char *str){
        std::string resp(str);
        if (strlen(str)>1){
            if ((uint8_t)str[0]==195){
                resp = str[1]+64;
            }else if ((uint8_t)str[0]==194){
                resp = str[1];
            }

        }
        return resp;
    }

    //o botao esquerdo faz com que a edi��o do trexto comece ou que o cursor seja reposicionado
    int CPigCaixaTexto::TrataMouseBotaoEsquerdo(SDL_Point p,int inicioLinha){
        int delta = p.x-xBase;
        int largParcial = 0;
        int largUltimaLetra = 0;
        std::string textoBase = GetTextoVisivel();

        for (int i=inicioLinha;i<=textoBase.size();i++){
            std::string aux;

            aux.assign(textoBase,inicioLinha,i - inicioLinha);

            largParcial += CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto);

            if (delta<largParcial-largUltimaLetra){
                posCursor = i-1;
                if (textoBase[posCursor]=='\n')
                    posCursor--;
                AjustaAlinhamento();
                return 1;
            }

            largUltimaLetra = largParcial;
        }

        posCursor = texto.size();

        AjustaAlinhamento();
        if (estado==COMPONENTE_NORMAL)
            DefineEstado(COMPONENTE_EDITANDO);

        return 1;
    }
