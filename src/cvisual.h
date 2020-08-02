
#ifndef CVISUAL_H
#define CVISUAL_H

#include "tipos_pig.h"

#include <string>

class COffscreenRenderer;

class CVisual
{
protected:
    int alt,larg,altOriginal,largOriginal;
    int idJanela,altJanela;
    float angulo;
    SDL_Rect dest,frame;
    SDL_Texture* text;
    SDL_Point pivoRelativo;
    SDL_Renderer* renderer;
    SDL_RendererFlip flip;
    SDL_Surface* bitmap;
    PIG_Cor coloracao;
    int opacidade;
    int x,y;
    std::string nomeArquivo;

    void CriaTextura(int retiraFundo, PIG_Cor *corFundo=NULL);
    void CarregaImagem(std::string nomeArq);
    void IniciaBase(int altura,int largura,int janela);
    CVisual(int altura,int largura,std::string nomeArq,int janela=0);
    CVisual(std::string nomeArq,int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0);
    CVisual(COffscreenRenderer *offRender, int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0);
    CVisual(CVisual *visualBase,int retiraFundo=1,PIG_Cor *corFundo=NULL,int janela=0);
    ~CVisual();

private:
    void IniciaCor();
    void IniciaJanela(int janela);
    void IniciaDimensoes(int altura,int largura);
    void IniciaOrientacao();

public:
    int GetIdJanela();
    void DefineFrame(SDL_Rect r);
    void GetXY(int &x,int &y);
    void SetColoracao(PIG_Cor cor);
    virtual void SetAngulo(float a);
    float GetAngulo();
    void SetFlip(PIG_Flip valor);
    PIG_Flip GetFlip();
    void SetPivo(int px,int py);
    void SetPivo(float px,float py);
    void GetPivo(int &px,int &py);
    virtual void Move(int nx,int ny);
    virtual void Desloca(int dx, int dy);
    void SetDimensoes(int altura,int largura);
    virtual void GetDimensoes(int &altura, int &largura);
    void GetDimensoesOriginais(int &altura,int &largura);
    void SetOpacidade(int valor);
    int GetOpacidade();
    std::string GetNomeArquivo();

};

#endif
