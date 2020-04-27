class CPigCampoTextoESenha: public CPigCaixaTexto{

private:

    char mascara;//s�mbolo usado quando o campo for de senha
    std::string (CPigCampoTextoESenha::*GetTextoVisivelPtr)();//ponteiro para a fun��o que vai retornar o texto visivel

    //retorna o texto com a quantidade de s�mbolos (m�scara) igual ao tamanho da string com textobase
    std::string GetTextoMask(){
        std::string resp;
        resp.assign(texto.size(),mascara);
        return resp;
    }

    //recupera a string com o texto vis�vel (com m�scara de senha ou n�o)
    std::string GetTextoVisivel(){
        return (this->*GetTextoVisivelPtr)();
    }

    //desenha apenas o texto
    void DesenhaElementosEspecificos(){
        EscreverEsquerda((char*)GetTextoVisivel().c_str(),xBase,yBase,fonteTexto);
    }

    //ajusta o alinhamento do cursor
    void AjustaAlinhamento(){
        std::string textoBase = GetTextoVisivel();
        std::string aux;

        xBase = xBaseOriginal;

        aux.assign(textoBase,0,posCursor);
        xCursor = xBase + CalculaLarguraPixels((char*)aux.c_str(),fonteTexto);

        AjustaBaseTextoEixoX(CalculaLarguraPixels((char*)aux.c_str(),fonteTexto));
    }

public:

    CPigCampoTextoESenha(int idComponente,int px, int py, int alt,int larg,char *nomeArq,int fonteDoTexto = 0,int fonteDoLabel = 0,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1,int janela=0,bool campoSenha = false):
        CPigCaixaTexto(idComponente,px,py,alt,larg,nomeArq,fonteDoTexto,fonteDoLabel,maxCars,apenasNumeros,retiraFundo,janela){
            yBaseOriginal = y+margemVertBaixo;
            xBaseOriginal = x+margemHorEsq;
            yBase = yBaseOriginal;
            xBase = xBaseOriginal;
            xCursor = xBase;
            yCursor = yBase;
            mascara = '*';
            if(campoSenha){
                GetTextoVisivelPtr = &GetTextoMask;
            }else{
                GetTextoVisivelPtr = &GetTexto;
            }
    }

    //define as margens do componente
    void SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima){
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

    int TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p){return 1;}//n�o usa o bot�o direito

    int TrataMouseRodinha(PIG_Evento evento){return 1;}//n�o usa arodinha

    int SobeCursor(){return 1;} //n�o usa o SobeCursor

    int DesceCursor(){return 1;}//n�o usa o DesceCursor

    int PulaLinha(){return 1;}//n�o usa o PulaLinha
};

typedef CPigCampoTextoESenha PigCampoTextoESenha;
