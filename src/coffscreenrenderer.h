
#ifndef COFFSCREENRENDERER_H
#define COFFSCREENRENDERER_H

#include "cpilhacoordenada.h"

#include <SDL2/SDL.h>

#include "tipos_pig.h"

#define PIG_MAX_CAMADAS_OFFSCREEN 50

typedef struct{
    SDL_Surface *surf;
    SDL_Renderer *render;
} Layer;

class COffscreenRenderer
{
private:
    Layer layers[PIG_MAX_CAMADAS_OFFSCREEN];
    int qtdLayers,maxLayers;

    int alt,larg,depth;
    double px,py;
    double ang;
    PIG_Cor corAtual;
    PIG_Cor (*userFunctionPintarArea)(int, int, int, int, PIG_Cor,PIG_Cor);

public:
    SDL_Renderer *GetRenderer(int layer=0);
    SDL_Surface *GetSurface(int layer=0);
    int GetAltura();
    int GetLargura();
    int GetDepth();
    void SetCorTransparente(int layer, bool transparencia, PIG_Cor cor);
    void MergeSurface(int layerSuperior, int layerInferior, SDL_BlendMode modo);
    Layer CriaLayer();
    void LimpaLayer(int layer, PIG_Cor cor);
    COffscreenRenderer(int altura,int largura,int qtdMaxCamadas=1);
    void DesenhaCirculoFinal(int raio, PIG_Cor corFundo, PIG_Cor corCirculo, double angInicial,double angFinal,int layer=0);
    void DesenhaCirculoFatia(int centroX,int centroY,int raio, PIG_Cor cor, double angInicial, double angFinal,SDL_Point &iniP,SDL_Point &fimP,int layer=0);
    /*
    SDL_Point DesenhaCirculo2(int centroX,int centroY,int raio, PIG_Cor cor, double angFinal,int layer=0);
    void DesenhaCirculo(int raioInterno, int raioExterno, PIG_Cor cor, double angFinal,bool horario,int layer=0);
    */
    void PintarFundo(SDL_Color cor,int layer=0);
    void PintarArea(int px,int py,PIG_Cor cor,void *ponteiro=nullptr,int layer=0);
    void DesenharLinha(int x1,int y1,int x2,int y2,PIG_Cor cor,int layer=0);
    void DesenharRetangulo(int x,int y,int altura,int largura,PIG_Cor cor,int layer=0);
    void DesenharRetanguloVazado(int x,int y,int altura,int largura,PIG_Cor cor,int layer=0);
    void CarregaPixelsSurface(int layer=0);
    void SalvarImagemBMP(char *nomearq,int layer=0);
    void SalvarImagemPNG(char *nomearq,int layer=0);
    void DefineFuncaoPintarArea(PIG_Cor (*funcao)(int, int, int, int, PIG_Cor,PIG_Cor));
    void MoveCanetaPara(double nx,double ny);
    void GiraCanetaHorario(double angulo);
    void GiraCanetaAntiHorario(double angulo);
    void GiraAnguloFixo(double angulo);
    double GetAngAtual();
    void AvancaCaneta(double distancia,int layer=0);
    void MudaCorAtualCaneta(PIG_Cor novaCor);
    double GetXCaneta();
    double GetYCaneta();
    ~COffscreenRenderer();

};

#endif
