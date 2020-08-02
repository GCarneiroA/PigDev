
#include "cparticula.h"
#include "cgerenciadortimers.h"
#include "ctimer.h"

CParticula::CParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, std::string nomeArq,int usaGerenciadorTimer,int idJanela):
        CAnimacao(nomeArq,usaGerenciadorTimer,NULL,1,idJanela){
        tenhoAnimacaoBase = 0;
        IniciaBase(x,y,deslocX,deslocY,vida,anguloRot,escalaIni,escalaFim,fadeOut,usaGerenciadorTimer);
    }

CParticula::CParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, CAnimacao *animacaoBase,int usaGerenciadorTimer,int idJanela):
        CAnimacao(animacaoBase,usaGerenciadorTimer,NULL,1,idJanela){
        tenhoAnimacaoBase = 1;
        IniciaBase(x,y,deslocX,deslocY,vida,anguloRot,escalaIni,escalaFim,fadeOut,usaGerenciadorTimer);
        SetDimensoes(alt,larg);//para definir o valor de escalaIniX e escalaIniY
    }

CParticula::CParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, CObjeto *objBase,int usaGerenciadorTimer,int idJanela):
        CAnimacao(objBase,usaGerenciadorTimer,NULL,1,idJanela){
        tenhoAnimacaoBase = 0;
        IniciaBase(x,y,deslocX,deslocY,vida,anguloRot,escalaIni,escalaFim,fadeOut,usaGerenciadorTimer);
        SetDimensoes(alt,larg);//para definir o valor de escalaIniX e escalaIniY
    }

    void CParticula::DefineLimites(int xMenor,int xMaior,int yMenor,int yMaior, float tempoMax){
        menorX = xMenor;
        maiorX = xMaior;
        menorY = yMenor;
        maiorY = yMaior;
        limTempo = tempoMax;
    }

    CParticula::~CParticula(){
        if (timer){
            delete timer;
        }else{
            CGerenciadorTimers::DestroiTimer(idTimer);
        }
    }

    void CParticula::Move(){
        if (!viva) return;
        float decorrido;
        if (timer){
            decorrido = timer->GetTempoDecorrido();
        }else{
            decorrido = CGerenciadorTimers::GetTempoDecorrido(idTimer);
        }
        float porcTempoVida = decorrido/limTempo;
        if (porcTempoVida>1.0f){
            viva = false;
            return;
        }

        if (fading)
            CAnimacao::SetOpacidade(255*(1-porcTempoVida));

        float fatorDim = escalaInicial*(1-porcTempoVida)+escalaFinal*(porcTempoVida);
        CAnimacao::SetDimensoes(altOriginal*escalaIniY*fatorDim,largOriginal*escalaIniX*fatorDim);
        CAnimacao::SetPivo(0.5f,0.5f);
        CAnimacao::SetAngulo(decorrido*angRot);

        //int x = xini + dx*decorrido;
        //int y = yini + dy*decorrido;

        CAnimacao::Move(inix+dx*decorrido,iniy+dy*decorrido);
        viva = (x>menorX)&&(x<maiorX)&&(y>menorY)&&(y<maiorY);
    }

    void CParticula::SetDimensoes(int altura, int largura){
        CAnimacao::SetDimensoes(altura,largura);
        escalaIniX = largura*1.0/largOriginal;
        escalaIniY = altura*1.0/altOriginal;
    }

    void CParticula::MudaDirecao(int deslocX,int deslocY){
        dx = deslocX;
        dy = deslocY;
    }

    int CParticula::Colisao(CObjeto *outro){
        int resp = CAnimacao::Colisao(outro);
        if (resp){
            hp--;
            viva = hp>0;
        }
        return resp;
    }

    int CParticula::Colisao(CParticula *outra){
        int resp = CAnimacao::Colisao(outra);
        if (resp){
            hp--;
            viva = hp>0;

            outra->hp--;
            outra->viva = hp> 0;
        }
        return resp;
    }


void CParticula::IniciaBase(int x, int y, int deslocX, int deslocY, int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, int usaGerenciadorTimer){
    inix = x;
    iniy = y;
    dx = deslocX;
    dy = deslocY;
    hp = vida;
    angRot = anguloRot;
    escalaInicial = escalaIni;
    escalaFinal = escalaFim;
    escalaIniX = escalaIniY = 1.0;
    fading = fadeOut;

    if (usaGerenciadorTimer){
        timer = NULL;
        idTimer = CGerenciadorTimers::CriaTimer();
    }else{
        timer = new CTimer(false);
        idTimer = -1;
    }

    viva = 1;
}
