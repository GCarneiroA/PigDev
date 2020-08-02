
#ifndef COBJETO_H
#define COBJETO_H

#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

#include "cvisual.h"

class COffscreenRenderer;

class CObjeto : public CVisual
{
protected:
    std::map<int, int> valoresIntInt;
    std::map<std::string, int> valoresStringInt;
    std::map<int, float> valoresIntFloat;
    std::map<std::string, float> valoresStringFloat;
    std::map<int, std::string> valoresIntString;
    std::map<std::string, std::string> valoresStringString;
    SDL_Point bb[4];
    PIG_Cor **pixels;

    std::vector<SDL_Point> vertices;
    std::vector<SDL_Point> verticesOriginais;
    bool bbAlterado = true;

    void DesenhaBB();
    void DesenhaAreaDeColisao(PIG_Cor cor);
    void AtualizaBB();
    void AtualizaVertices();
    void ExtraiPixels();

public:
    CObjeto(std::string nomeArquivo, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int janela = 0);
    CObjeto(COffscreenRenderer *offRender, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int janela = 0);
    CObjeto(CObjeto *objBase, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int janela = 0);
    ~CObjeto();
    /*int GetIdJanela();*/
    void SetValoresInt(int chave, int valor);
    void SetValoresInt(std::string chave, int valor);
    void SetValoresFloat(int chave, float valor);
    void SetValoresFloat(std::string chave, float valor);
    void SetValoresString(int chave, std::string valor);
    void SetValoresString(std::string chave, std::string valor);
    void SetVertices(std::vector<SDL_Point> vertices);
    void SetAngulo(float a) override;
    bool GetValoresInt(int chave, int &valor);
    bool GetValoresInt(std::string chave, int &valor);
    bool GetValoresFloat(int chave, float &valor);
    bool GetValoresFloat(std::string chave, float &valor);
    bool GetValoresString(int chave, std::string &valor);
    bool GetValoresString(std::string chave, std::string &valor);
    SDL_Point GetBB(int i);
    std::vector<SDL_Point> GetVertices();
    void Move(int nx, int ny) override;
    int Desenha(COffscreenRenderer *offRender = nullptr);
    void Atualiza();
    bool Colisao(CObjeto *outro);
    int ColisaoBB(CObjeto *outro);
    bool PontoDentro(SDL_Point p);
    bool ColisaoPoligono(CObjeto *outro);
    PIG_Cor **GetPixels();
    void AtualizaPixels(int retiraFundo = 1, int opacidadeObj = 255);

private:

    int arredonda(float valor);
    double projecaoY(double coefAngular, SDL_Point p);
    double projecaoX(double coefAngular, SDL_Point p);
    double  min(double  vetor[4]);
    double  max(double  vetor[4]);
    bool Entre(int x, int a, int b);
    bool Intersecao(int i, int f, SDL_Point p);

};

#endif
