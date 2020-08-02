
#include "cpigcomponente.h"

#include "cmouse.h"
#include "cgerenciadorfontes.h"
#include "cgerenciadorjanelas.h"


CPigComponente::CPigComponente(int idComponente,int px,int py, int altura, int largura, int janela)
    :CVisual(altura, largura, "",janela){
        IniciaBase(idComponente,px,py);
    }

CPigComponente::CPigComponente(int idComponente,int px,int py, int altura, int largura, std::string nomeArq,int retiraFundo,int janela)
    :CVisual(nomeArq,retiraFundo,NULL,janela){
        IniciaBase(idComponente,px,py);
        CVisual::SetDimensoes(altura,largura);
    }

CPigComponente::~CPigComponente(){
        hint.clear();
        label.clear();
    }

    int CPigComponente::GetId(){
        return id;
    }

    void CPigComponente::SetHint(std::string novoHint){
        hint = novoHint;
    }

    void CPigComponente::SetLabel(std::string novoLabel){
        label = novoLabel;
    }

    void CPigComponente::SetAudio(int idAudio){
        audioComponente = idAudio;
    }

    void CPigComponente::SetFonteHint(int fonte){
        fonteHint = fonte;
    }

    void CPigComponente::SetFonteLabel(int fonte){
        fonteLabel = fonte;
        altLetraLabel = CGerenciadorFontes::GetTamanhoBaseFonte(fonteLabel)+CGerenciadorFontes::GetFonteDescent(fonteLabel);
    }

    std::string CPigComponente::GetLabel(){
        return label;
    }

    int CPigComponente::SetPosicaoPadraoLabel(PIG_PosicaoComponente pos){
        posLabel = pos;
        return 1;
    }

    int CPigComponente::SetPosicaoPersonalizadaLabel(int rx, int ry){
        labelX = rx;
        labelY = ry;
        posLabel = PIG_COMPONENTE_PERSONALIZADA;
        return 1;
    }

    PIG_EstadoComponente CPigComponente::GetEstado(){
        return estado;
    }

    PIG_PosicaoComponente CPigComponente::GetPosComponente(){
        return posComponente;
    }

    void CPigComponente::SetPosPadraoExternaComponente(PIG_PosicaoComponente pos,CPigComponente *componenteAssociado){
        int xComponente,yComponente,altComponente,largComponente;
        int largura,altura;

        posComponente = pos;
        componenteAssociado->GetDimensoes(altComponente,largComponente);
        componenteAssociado->GetXY(xComponente,yComponente);
        this->GetDimensoes(altura,largura);

        switch(pos){
        case PIG_COMPONENTE_CIMA_CENTRO:
            Move(xComponente + (largComponente - largura)/2,yComponente+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_ESQ:
            Move(xComponente,yComponente+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_DIR:
            Move(xComponente + largComponente - largura,yComponente+altComponente);
            break;
        case PIG_COMPONENTE_BAIXO_CENTRO:
            Move(xComponente + (largComponente - largura)/2,yComponente - altura);
            break;
        case PIG_COMPONENTE_BAIXO_ESQ:
            Move(xComponente,yComponente - altura);
            break;
        case PIG_COMPONENTE_BAIXO_DIR:
            Move(xComponente + largComponente - largura,yComponente - altura);
            break;
        case PIG_COMPONENTE_DIR_BAIXO:
            Move(xComponente + largComponente,yComponente);
            break;
        case PIG_COMPONENTE_DIR_CENTRO:
            Move(xComponente + largComponente,yComponente + (altComponente - altura)/2);
            break;
        case PIG_COMPONENTE_DIR_CIMA:
            Move(xComponente + largComponente,yComponente + altComponente - altura);
            break;
        case PIG_COMPONENTE_ESQ_BAIXO:
            Move(xComponente - largura,yComponente);
            break;
        case PIG_COMPONENTE_ESQ_CIMA:
            Move(xComponente - largura,yComponente + altComponente - altura);
            break;
        case PIG_COMPONENTE_ESQ_CENTRO:
            Move(xComponente - largura,yComponente + (altComponente - altura)/2);
            break;
        case PIG_COMPONENTE_CENTRO_CENTRO:
            Move(xComponente + (largComponente - largura)/2,yComponente + (altComponente - altura)/2);
            break;
        }
    }

    void CPigComponente::SetPosPadraoComponente(PIG_Ancora ancora){
        int largTela,altTela;
        int altura,largura;
        largTela = CGerenciadorJanelas::GetLargura(idJanela);
        altTela = CGerenciadorJanelas::GetAltura(idJanela);

        this->GetDimensoes(altura,largura);

        switch(ancora){
        case SUL:
            Move((largTela - largura)/2,0);
            break;
        case SUDOESTE:
            Move(0,0);
            break;
        case SUDESTE:
            Move(largTela - largura,0);
            break;
        case NORTE:
            Move((largTela - largura)/2,altTela - altura);
            break;
        case NOROESTE:
            Move(0,altTela - altura);
            break;
        case NORDESTE:
            Move(largTela - largura,altTela - altura);
            break;
        case CENTRO:
            Move((largTela - largura)/2,(altTela - altura)/2);
            break;
        case OESTE:
            Move(0,(altTela - altura)/2);
            break;
        case LESTE:
            Move(largTela - largura,(altTela - altura)/2);
            break;
        }
    }

    void CPigComponente::IniciaBase(int idComponente, int px, int py){
        id = idComponente;
        hint = label = "";
        SetFonteHint(0);
        SetFonteLabel(0);
        audioComponente = -1;
        estado = COMPONENTE_NORMAL;
        posLabel = PIG_COMPONENTE_CENTRO_CENTRO;
        x = px;
        y = py;
        agoraOn = antesOn = 0;
    }

    void CPigComponente::EscreveHint(){
        if (agoraOn&&hint!=""){
            int mx,my;
            CMouse::PegaXY(mx,my);
            CGerenciadorFontes::EscreverString(hint,mx+16,my+5,fonteHint);
        }
    }

    int CPigComponente::MouseSobre(int mx, int my){
        if (estado==COMPONENTE_INVISIVEL)
            return 0;

        SDL_Point p={mx,my};
        SDL_Rect r={x,y,larg,alt};

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

    void CPigComponente::DesenhaLabel(){
        //printf("vai <%s> %d\n",label.c_str(),fonteLabel);
        if (label!="") {
            switch(posLabel){
            case PIG_COMPONENTE_CIMA_CENTRO:
                CGerenciadorFontes::EscreverString(label,x+larg/2,y+alt+5,fonteLabel,CPIG_TEXTO_CENTRO);
                break;
            case PIG_COMPONENTE_CIMA_DIR:
                CGerenciadorFontes::EscreverString(label,x+larg,y+alt+5,fonteLabel,CPIG_TEXTO_DIREITA);
                break;
            case PIG_COMPONENTE_CIMA_ESQ:
                CGerenciadorFontes::EscreverString(label,x,y+alt+5,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_BAIXO_CENTRO:
                CGerenciadorFontes::EscreverString(label,x+larg/2,y-altLetraLabel,fonteLabel,CPIG_TEXTO_CENTRO);
                break;
            case PIG_COMPONENTE_BAIXO_DIR:
                CGerenciadorFontes::EscreverString(label,x+larg,y-altLetraLabel,fonteLabel,CPIG_TEXTO_DIREITA);
                break;
            case PIG_COMPONENTE_BAIXO_ESQ:
                CGerenciadorFontes::EscreverString(label,x,y-altLetraLabel,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_ESQ_BAIXO:
                CGerenciadorFontes::EscreverString(label,x-5,y,fonteLabel,CPIG_TEXTO_DIREITA);
                break;
            case PIG_COMPONENTE_ESQ_CENTRO:
                CGerenciadorFontes::EscreverString(label,x-5,y+(alt-altLetraLabel)/2,fonteLabel,CPIG_TEXTO_DIREITA);
                break;
            case PIG_COMPONENTE_ESQ_CIMA:
                CGerenciadorFontes::EscreverString(label,x-5,y + (alt-altLetraLabel),fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_DIR_BAIXO:
                CGerenciadorFontes::EscreverString(label,x+larg+5,y,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_DIR_CENTRO:
                CGerenciadorFontes::EscreverString(label,x+larg+5,y + (alt-altLetraLabel)/2,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_DIR_CIMA:
                CGerenciadorFontes::EscreverString(label,x+larg+5,y + (alt-altLetraLabel),fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            case PIG_COMPONENTE_CENTRO_CENTRO:
                CGerenciadorFontes::EscreverString(label,x+larg/2,y+(alt-altLetraLabel)/2,fonteLabel,CPIG_TEXTO_CENTRO);
                break;
            case PIG_COMPONENTE_PERSONALIZADA:
                CGerenciadorFontes::EscreverString(label,labelX,labelY,fonteLabel,CPIG_TEXTO_ESQUERDA);
                break;
            }
        }
    }


