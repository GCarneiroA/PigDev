
#ifndef CGERENCIADOROBJETOS_H
#define CGERENCIADOROBJETOS_H

#include "coffscreenrenderer.h"

#include <string>

class CObjeto;
class COffscreenRenderer;
class CPoolNumeros;

class CGerenciadorObjetos
{
public:
    static CObjeto *GetObjeto(int idObjeto);
    static void Inicia();
    static void Encerra();
    static int CriaObjeto(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0);
    static int CriaObjetoOffScreen(COffscreenRenderer *offRenderer,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0);
    static void DestroiObjeto(int idObjeto);
    static void SetValorIntObjeto(int idObjeto, int chave, int valor);
    static void SetValorIntObjeto(int idObjeto, std::string chave, int valor);
    static void SetValorFloatObjeto(int idObjeto, int chave, float valor);
    static void SetValorFloatObjeto(int idObjeto, std::string chave, float valor);
    static void SetValorStringObjeto(int idObjeto, int chave, std::string valor);
    static void SetValorStringObjeto(int idObjeto, std::string chave, std::string valor);
    static bool GetValorIntObjeto(int idObjeto, int indice, int *valor);
    static bool GetValorFloatObjeto(int idObjeto, int indice, float *valor);
    static bool GetValorStringObjeto(int idObjeto, int indice, char *valor);
    static bool GetValorIntObjeto(int idObjeto, std::string indice, int *valor);
    static bool GetValorFloatObjeto(int idObjeto, std::string indice, float *valor);
    static bool GetValorStringObjeto(int idObjeto, std::string indice, char *valor);
    static void GetPosicaoXY(int idObjeto, int *x, int *y);
    static void Move(int idObjeto, int x, int y);
    static void Desloca(int idObjeto, int dx, int dy);
    static void SetAngulo(int idObjeto, float angulo);
    static float GetAngulo(int idObjeto);
    static void SetPivo(int idObjeto, int x, int y);
    static void SetPivo(int idObjeto, float relX, float relY);
    static void GetPivo(int idObjeto, int *x,int *y);
    static void SetFlip(int idObjeto, PIG_Flip valor);
    static PIG_Flip GetFlip(int idObjeto);
    static void SetDimensoes(int idObjeto, int altura, int largura);
    static void GetDimensoes(int idObjeto, int *altura, int *largura);
    static void GetDimensoesOriginais(int idObjeto, int *altura, int *largura);
    static void CriaFrame(int idObjeto, int xBitmap, int yBitmap,int altura,int largura);
    static void SetColoracao(int idObjeto, PIG_Cor cor);
    static void SetOpacidade(int idObjeto, int valor);
    static int GetOpacidade(int idObjeto);
    static void Desenha(int idObjeto,COffscreenRenderer *offRender=nullptr);
    static int TestaColisaoPoligono(int idObjeto1, int idObjeto2);
    static int TestaColisao(int idObjeto1, int idObjeto2);
    static void DefineAreaColisao(int idObjeto, int *x, int *y, int quantidadePontos);
    static PIG_Cor **GetPixels(int idObjeto);
    static void AtualizaPixels(int idObjeto,int retiraFundo=1);

private:
    static int totalObjetos;
    static CPoolNumeros *numObjetos;
    static CObjeto *objetos[MAX_OBJETOS];   
};

#endif // CGERENCIADOROBJETOS_H
