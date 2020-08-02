
#ifndef CJANELA_H
#define CJANELA_H

#include <SDL2/SDL.h>
#include <string>

#include "tipos_pig.h"

class CJanela
{
public:
    CJanela(std::string tituloJanela,int idJanela,int altTela,int largTela);
    ~CJanela();
    SDL_Window *GetWindow();
    SDL_Renderer *GetRenderer();
    void Fecha();
    int GetFechada();
    void Esconde();
    void Exibe();
    void GanhaFoco();
    void DefineFundo(std::string nomeArquivo);
    void SaveScreenshot(std::string nomeArquivo, bool BMP);
    void IniciaDesenho();
    void EncerraDesenho();
    int GetAltura();
    int GetLargura();
    std::string GetTitulo();
    void SetTitulo(std::string novoTitulo);
    PIG_Cor GetCorFundo();
    void SetCorFundo(PIG_Cor cor);
    float GetOpacidade();
    void SetOpacidade(float valor);
    void SetPosicao(int x,int y);
    void GetPosicao(int *x,int *y);
    void SetBorda(int valor);
    void SetModo(int valor);
    int GetModo();
    int SetTamanho(int alt, int larg);
    void DesenhaRetangulo(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor);
    void DesenhaRetanguloVazado(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor);
    void DesenhaLinhaSimples(int x1,int y1,int x2,int y2,PIG_Cor cor);
    void DesenhaLinhasDisjuntas(int *x,int *y,int qtd,PIG_Cor cor);
    void DesenhaLinhasSequencia(int *x,int *y,int qtd,PIG_Cor cor);
    PIG_Cor GetPixel(int x,int y);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textFundo;
    PIG_Cor corFundo;
    int altura,largura,px,py;
    int id;
    int fechada,modo;
    float opacidade;
    std::string titulo;
};

#endif
