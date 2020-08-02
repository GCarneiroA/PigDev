
#include "cpiggaugecircular.h"

#include "pigfuncoesbasicas.h"

#include "coffscreenrenderer.h"

PIG_Cor MixCor(PIG_Cor iniCor, PIG_Cor fimCor, double porc)
{
    PIG_Cor resp;
    resp.r = fimCor.r*porc + (iniCor.r)*(1-porc);
    resp.g = fimCor.g*porc + (iniCor.g)*(1-porc);
    resp.b = fimCor.b*porc + (iniCor.b)*(1-porc);
    resp.a = fimCor.a*porc + (iniCor.a)*(1-porc);
    return resp;
}

CPigGaugeCircular::CPigGaugeCircular(int idComponente,int px, int py,int altura,int largura,int raioInterior,int janela)
    : CPigComponente(idComponente,px,py,altura,largura,janela)
{

    angBase = 0;
    deltaAng = 360;
    raioInterno = raioInterior;
    valor = 0;
    valorMin = 0;
    valorMax = 100;
    porcentagemConcluida = 0.0;
    corInicial = corFinal = LARANJA;
    corFundo = PRETO;
    off = new COffscreenRenderer(altura,largura,3);

    Move(px,py);
    SetPivo(larg/2,alt/2);
    textGauge = NULL;
    AtualizaTextura();
    crescimentoHorario=true;
}

CPigGaugeCircular::CPigGaugeCircular(int idComponente,int px, int py,int altura,int largura,int raioInterior,std::string nomeArq,int retiraFundo,int janela)
    : CPigComponente(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela)
{

    angBase = 0;
    deltaAng = 360;
    raioInterno = raioInterior;
    valor = 0;
    valorMin = 0;
    valorMax = 100;
    porcentagemConcluida = 0.0;
    corInicial = corFinal = LARANJA;
    corFundo = PRETO;
    off = new COffscreenRenderer(altura,largura,3);

    Move(px,py);
    SetPivo(larg/2,alt/2);
    textGauge = NULL;
    AtualizaTextura();
    crescimentoHorario=true;
}

CPigGaugeCircular::~CPigGaugeCircular()
{
    delete off;
}

void CPigGaugeCircular::SetRaioInterno(int valorRaio)
{
    if (valorRaio<0||valorRaio>0.9*larg/2) return;

    raioInterno = valorRaio;
    //printf("atualizei %d\n",raioInterno);
    AtualizaTextura();
}

void CPigGaugeCircular::SetAnguloBase(double novoAng)
{
    angBase = novoAng;
    AtualizaTextura();
}

void CPigGaugeCircular::SetDeltaAngulo(double novoDelta)
{
    deltaAng = novoDelta;
    AtualizaTextura();
}

void CPigGaugeCircular::IncrementaValor(int delta)
{
    valor = PIGLimitaValor(valor+delta, valorMin,valorMax);
    porcentagemConcluida = 1.*(valor-valorMin)/(valorMax-valorMin);
    AtualizaTextura();
}

void CPigGaugeCircular::SetValorMax(int novoValor)
{
    if (novoValor<=valorMin)return;
    valorMax = novoValor;
    if (valor>valorMax) valor = valorMax;
    porcentagemConcluida = 1.*(valor-valorMin)/(valorMax-valorMin);
    AtualizaTextura();
}

void CPigGaugeCircular::SetValorMin(int novoValor)
{
    if (novoValor>=valorMax) return;
    valorMin = novoValor;
    if (valor<valorMin) valor=valorMin;
    porcentagemConcluida = 1.*(valor-valorMin)/(valorMax-valorMin);
    AtualizaTextura();
}

void CPigGaugeCircular::SetCorInicial(PIG_Cor cor)
{
    corInicial = cor;
    AtualizaTextura();
}

void CPigGaugeCircular::SetCorFinal(PIG_Cor cor)
{
    corFinal = cor;
    AtualizaTextura();
}

void CPigGaugeCircular::SetCorFundo(PIG_Cor cor)
{
    corFundo = cor;
    AtualizaTextura();
}

int CPigGaugeCircular::GetValor()
{
    return valor;
}

std::string CPigGaugeCircular::GetValorString()
{
    std::stringstream ss;
    ss <<valor;
    return ss.str();
}

int CPigGaugeCircular::GetValorMax()
{
    return valorMax;
}

int CPigGaugeCircular::GetValorMin()
{
    return valorMin;
}

void CPigGaugeCircular::AtualizaValor(int novoValor)
{
    if (valor==novoValor) return;
    valor = novoValor;
    AtualizaTextura();
}

void CPigGaugeCircular::AtualizaTextura()
{
    PIG_Cor corBarra = MixCor(corInicial,corFinal,porcentagemConcluida);//cor da barra mizada entre a cor inicial e a final
    PIG_Cor opcoes[4] = {VERDE,AZUL,ROXO,LARANJA}; //4 cores quaisquer
    PIG_Cor croma1, croma2; //cores usada como cromakey para transparencias (n�o podem ser nem a cor da barra, nem a cor do fundo)

    //escolha das cores
    int i=0;
    croma1=opcoes[i];
    while (PIGCoresIguais(croma1,corBarra)||PIGCoresIguais(croma1,corFundo)){//n�o pode ser a cor da barra nem do fundo
        croma1=opcoes[++i];
    }
    croma2=opcoes[i];
    while (PIGCoresIguais(croma2,corBarra)||PIGCoresIguais(croma2,corFundo)||PIGCoresIguais(croma2,croma1)){//n�o pode ser a cor da barra, nem do fundo, nem a cor croma1
        croma2=opcoes[++i];
    }

    //circulo interno para criar efeito de coroa circular
    off->DesenhaCirculoFinal(raioInterno,croma2,croma1,0,360.0,2);
    off->SetCorTransparente(2,true,croma2);
    //off->SalvarImagemPNG("interno.png",2);

    //circulo com a barra na cor desejada
    off->DesenhaCirculoFinal(larg/2-2,croma1,corBarra,angBase,porcentagemConcluida*(deltaAng)+angBase,0);
    off->SetCorTransparente(0,true,croma1);
    //off->SalvarImagemPNG("barra.png",0);

    //criculo com o fundo na cor de fundo
    off->DesenhaCirculoFinal(larg/2-2,croma1,corFundo,angBase,angBase+deltaAng,1);
    off->SetCorTransparente(1,true,croma1);
    //off->SalvarImagemPNG("fundo.png",1);

    //mistura o circulo interno com a barra
    off->MergeSurface(2,0,SDL_BLENDMODE_NONE);
    //off->SalvarImagemPNG("circ20.png",0);

    //mistura o circulo interno com o fundo
    off->MergeSurface(2,1,SDL_BLENDMODE_NONE);
    //off->SalvarImagemPNG("circ21.png",1);

    //sobre a barra em cima do fundo
    off->MergeSurface(0,1,SDL_BLENDMODE_NONE);
    //off->SalvarImagemPNG("circ01.png",1);

    if (textGauge) SDL_DestroyTexture(textGauge);
    textGauge = SDL_CreateTextureFromSurface(renderer,off->GetSurface(1));
    //bitmap = off->GetSurface(1);
    //CriaTextura(1);
}

int CPigGaugeCircular::Desenha()
{
    SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,&pivoRelativo,flip);
    SDL_RenderCopyEx(renderer,textGauge,NULL,&dest,-angulo,&pivoRelativo,flip);

    DesenhaLabel();
    EscreveHint();
}

void CPigGaugeCircular::DefineEstado(PIG_EstadoComponente estadoComponente)
{
}

int CPigGaugeCircular::OnMouseOn()
{
    return 0;
}

int CPigGaugeCircular::OnMouseOff()
{
    return 0;
}

int CPigGaugeCircular::TrataEvento(PIG_Evento evento)
{
    return 0;
}
