
#ifndef CGERENCIADORANIMACOES_H
#define CGERENCIADORANIMACOES_H

#include "tipos_pig.h"
#include <string>

class CObjeto;
class CAnimacao;
class CPoolNumeros;

class CGerenciadorAnimacoes
{
public:
    static CAnimacao *GetAnimacao(int idAnimacao);
    static void Inicia(SDL_Renderer *renderer=NULL);
    static void Encerra();
    static int CriaAnimacao(std::string nomeArquivoBMP,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0);
    static int CriaAnimacao(int idAnimacaoBase,PIG_Cor *corFundo=NULL,int retiraFundo=1,int idJanela=0);
    static void DestroiAnimacao(int idAnimacao);
    
    static void Move(int idAnimacao,int px,int py);
    static void Desloca(int idAnimacao,int dx,int dy);
    static void GetPosicaoXY(int idAnimacao, int *x,int *y);
    static int Desenha(int idAnimacao);
    static void CriaFrame(int idAnimacao,int codFrame,int x,int y,int altura,int largura);
    static void CriaModo(int idAnimacao,int idModo, int loop);
    static void InsereFrame(int idAnimacao, int idModo,int idFrame, float delayFrame,int idAudio);
    static int GetModo(int idAnimacao);
    static void MudaModo(int idAnimacao,int idModo,int indiceFrame,int forcado);
    static void SetOpacidade(int idAnimacao,int valor);
    static int GetOpacidade(int idAnimacao);
    static void SetColoracao(int idAnimacao,PIG_Cor cor);
    static void SetPivo(int idAnimacao,int x,int y);
    static void GetPivo(int idAnimacao,int *x,int *y);
    static void SetFlip(int idAnimacao, PIG_Flip valor);
    static PIG_Flip GetFlip(int idAnimacao);
    static void SetAngulo(int idAnimacao,float valor);
    static float GetAngulo(int idAnimacao);
    static int ColisaoAnimacoes(int idAnimacao1,int idAnimacao2);
    static int ColisaoObjeto(int idAnimacao,CObjeto *obj);
    static void SetDimensoes(int idAnimacao,int altura,int largura);
    static void GetDimensoes(int idAnimacao,int *altura,int *largura);
    static void SetValorIntAnimacao(int idAnimacao, int chave, int valor);
    static void SetValorIntAnimacao(int idAnimacao, std::string chave, int valor);
    static void SetValorFloatAnimacao(int idAnimacao, int chave, float valor);
    static void SetValorFloatAnimacao(int idAnimacao, std::string chave, float valor);
    static void SetValorStringAnimacao(int idAnimacao, int chave, std::string valor);
    static void SetValorStringAnimacao(int idAnimacao, std::string chave, std::string valor);
    static bool GetValorIntAnimacao(int idAnimacao, int indice, int *valor);
    static bool GetValorFloatAnimacao(int idAnimacao, int indice, float *valor);
    static bool GetValorStringAnimacao(int idAnimacao, int indice, std::string &valor);
    static bool GetValorIntAnimacao(int idAnimacao, std::string indice, int *valor);
    static bool GetValorFloatAnimacao(int idAnimacao, std::string indice, float *valor);
    static bool GetValorStringAnimacao(int idAnimacao, std::string indice, std::string &valor);
    static void PausaAnimacao(int idAnimacao);
    static void DespausaAnimacao(int idAnimacao);
    static void SetTempoFrameAnimacao(int idAnimacao, int idModo, int indiceFrame, double tempo);
    static void SetAudioFrameAnimacao(int idAnimacao, int idModo, int indiceFrame, int idAudio);
    static void SetLoopModoAnimacao(int idAnimacao, int idModo, bool loop);
    static double GetTempoFrameAnimacao(int idAnimacao, int idModo, int indiceFrame);
    static bool GetLoopModoAnimacao(int idAnimacao, int idModo);
    static int GetAudioFrameAnimacao(int idAnimacao, int idModo, int indiceFrame);

private:
    static int totalAnimacoes;
    static CPoolNumeros *numAnimacoes;
    static CAnimacao *animacoes[MAX_ANIMACOES];
};

#endif
