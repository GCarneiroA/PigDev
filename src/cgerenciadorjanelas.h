
#ifndef CGERENCIADORJANELAS_H
#define CGERENCIADORJANELAS_H

#include "tipos_pig.h"
#include "cjanela.h"

#include <string>

class CJanela;

class CGerenciadorJanelas
{
public:
    static void Inicia(std::string nome,int altura=ALT_TELA,int largura=LARG_TELA);
    static void Encerra();
    static int GetQtdJanelas();
    static int CriaJanela(std::string nome,int altura=ALT_TELA,int largura=LARG_TELA);
    static void FechaJanela(int idJanela);
    static void EscondeJanela(int idJanela);
    static void ExibeJanela(int idJanela);
    static void GanhaFocoJanela(int idJanela);
    static CJanela *GetJanela(int idJanela);
    static void IniciaDesenho(int idJanela=-1);
    static void EncerraDesenho(int idJanela=-1);
    static void DefineFundo(std::string nomeArquivo,int idJanela=0);
    static void SaveScreenshotBMP(std::string nomeArquivo,int idJanela=0);
    static void SaveScreenshotPNG(std::string nomeArquivo,int idJanela=0);
    static int GetAltura(int idJanela=0);
    static int GetLargura(int idJanela=0);
    static void SetTamanho(int altura,int largura,int idJanela=0);
    static std::string GetTitulo(int idJanela=0);
    static void SetTitulo(std::string novoTitulo,int idJanela=0);
    static PIG_Cor GetCorFundo(int idJanela=0);
    static void SetCorFundo(PIG_Cor cor,int idJanela=0);
    static float GetOpacidade(int idJanela=0);
    static void SetOpacidade(float valor,int idJanela=0);
    static void SetPosicao(int x,int y,int idJanela=0);
    static void GetPosicao(int *x,int *y,int idJanela=0);
    static void SetBorda(int valor,int idJanela=0);
    static void SetModo(int modo,int idJanela=0);
    static int GetModo(int idJanela=0);
    static void DesenhaRetangulo(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor, int idJanela=0);
    static void DesenhaRetanguloVazado(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor, int idJanela=0);
    static void DesenhaLinhaSimples(int x1,int y1,int x2,int y2,PIG_Cor cor,int idJanela=0);
    static void DesenhaLinhasDisjuntas(int *x,int *y,int qtd,PIG_Cor cor,int idJanela=0);
    static void DesenhaLinhasSequencia(int *x,int *y,int qtd,PIG_Cor cor,int idJanela=0);
    static PIG_Cor GetPixel(int x, int y, int idJanela=0);

private:
    static int qtdJanelas;
    static CJanela *janelas[MAX_JANELAS];
};

#endif
