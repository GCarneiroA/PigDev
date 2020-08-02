

#include "cpigcampotextoesenha.h"

#include <iostream>
#include <fstream>

#include "cpigerroarquivo.h"
#include "cpigerroparametro.h"

#include "cgerenciadorfontes.h"

CPigCampoTextoESenha::CPigCampoTextoESenha(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars, bool apenasNumeros, int retiraFundo,int janela,bool campoSenha)
    : CPigCaixaTexto(idComponente,px,py,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,janela)
{
            yBaseOriginal = y+margemVertBaixo;
            xBaseOriginal = x+margemHorEsq;
            yBase = yBaseOriginal;
            xBase = xBaseOriginal;
            xCursor = xBase;
            yCursor = yBase;
            mascara = '*';
            if(campoSenha){
                GetTextoVisivelPtr = &CPigCampoTextoESenha::GetTextoMask;
            }else{
                GetTextoVisivelPtr = &CPigCampoTextoESenha::GetTexto;
            }
    }

CPigCampoTextoESenha::CPigCampoTextoESenha(std::string nomeArqParam)
    : CPigCampoTextoESenha(LeArquivoParametros(nomeArqParam))
{
}

CPigCampoTextoESenha::~CPigCampoTextoESenha(){}

    CPigCampoTextoESenha CPigCampoTextoESenha::LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,maxCars = 200,retiraFundo=1,janela=0;
        bool apenasNumeros = false,campoSenha = false;

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
            if(variavel == "janela") arquivo >> janela;
            if(variavel == "maxCars") arquivo >> maxCars;
            if(variavel == "apenasNumeros") arquivo >> apenasNumeros;
            if(variavel == "campoSenha") arquivo >> campoSenha;
        }
        arquivo.close();

        if(nomeArq == "") throw CPigErroParametro("nomeArq",nomeArqParam);
       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;
        return CPigCampoTextoESenha(idComponente,px,py,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,janela,campoSenha);

    }

    //desenha o componente completo
    int CPigCampoTextoESenha::Desenha()
    {
        //imagem de fundo
        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        SDL_Rect r={x+margemHorEsq+1,altJanela-y-alt+margemVertCima,larg-(margemHorEsq+margemHorDir),alt-(margemVertBaixo+margemVertCima)};
        SDL_RenderSetClipRect(renderer,&r);

        CGerenciadorFontes::EscreverString(GetTextoVisivel(),xBase,yBase,fonteTexto,CPIG_TEXTO_ESQUERDA);
        DesenhaCursor();//desenha o cursor (se estiver em edi��o)

        //desbloqueia o desenho fora da area do componente
        SDL_RenderSetClipRect(renderer,NULL);

        DesenhaLabel();
        return 1;
    }

    //define as margens do componente
    void CPigCampoTextoESenha::SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima){
        margemVertCima = vertCima;
        margemVertBaixo = vertBaixo;
        margemHorDir = horDir;
        margemHorEsq = horEsq;
        yBaseOriginal = y+margemVertBaixo;
        xBaseOriginal = x+margemHorEsq;
        yBase = yBaseOriginal;
        xBase = xBaseOriginal;
        xCursor = xBase;
        yCursor = yBase;
        AjustaAlinhamento();
    }

    int CPigCampoTextoESenha::TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p)
    {
        return 1;
    }//n�o usa o bot�o direito

    int CPigCampoTextoESenha::TrataMouseRodinha(PIG_Evento evento)
    {
        return 1;
    }//n�o usa arodinha

    int CPigCampoTextoESenha::SobeCursor()
    {
        return 1;
    } //n�o usa o SobeCursor

    int CPigCampoTextoESenha::DesceCursor()
    {
        return 1;
    }//n�o usa o DesceCursor

    int CPigCampoTextoESenha::PulaLinha()
    {
        return 1;
    }//n�o usa o PulaLinha


  //retorna o texto com a quantidade de s�mbolos (m�scara) igual ao tamanho da string com textobase
    std::string CPigCampoTextoESenha::GetTextoMask(){
        std::string resp;
        resp.assign(texto.size(),mascara);
        return resp;
    }

    //recupera a string com o texto vis�vel (com m�scara de senha ou n�o)
    std::string CPigCampoTextoESenha::GetTextoVisivel(){
        return (this->*GetTextoVisivelPtr)();
    }

    //ajusta o alinhamento do cursor
    void CPigCampoTextoESenha::AjustaAlinhamento(){
        std::string textoBase = GetTextoVisivel();
        std::string aux;

        aux.assign(textoBase,0,posCursor);
        xCursor = xBase + CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto);

        AjustaBaseTextoEixoX(CGerenciadorFontes::GetLarguraPixels(aux,fonteTexto));
    }

