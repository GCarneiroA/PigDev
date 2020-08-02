
#ifndef CGERENCIADORVIDEOS_H
#define CGERENCIADORVIDEOS_H

#include "cvideo.h"
#include "tipos_pig.h"
#include <string>

class CPoolNumeros;
class CVideo;

class CGerenciadorVideos
{
public:
    static void Inicia();
    static void Encerra();
    static int CriaVideo(std::string nomeArquivo, int idJanela = 0);
    static void DestroiVideo(int idVideo);
    static void SetSeek(int idVideo, double incremento);
    static void Play(int idVideo);
    static void Stop(int idVideo);
    static void Pause(int idVideo);
    static void Resume(int idVideo);
    static void Desenha(int idVideo);
    static void SetVolume(int idVideo, double valor);
    static double GetVolume(int idVideo);
    static std::string GetNomeArquivo(int idVideo);
    static double GetTempoAtual(int idVideo);
    static std::string GetTempoAtualString(int idVideo);
    static double GetTempoTotal(int idVideo);
    static std::string GetTempoTotalString(int idVideo);
    static double GetTempoFrame(int idVideo);
    static double GetFPS(int idVideo);
    static void SetAngulo(int idVideo, float a);
    static double GetAngulo(int idVideo);
    static void SetFlip(int idVideo, PIG_Flip valor);
    static PIG_Flip GetFlip(int idVideo);
    static void SetPivo(int idVideo, int px, int py);
    static void SetPivo(int idVideo, float px, float py);
    static void GetPivo(int idVideo, int &px, int &py);
    static void Move(int idVideo, int nx, int ny);
    static void SetDimensoes(int idVideo, int altura, int largura);
    static void GetDimensoes(int idVideo, int &altura, int &largura);
    static void GetDimensoesOriginais(int idVideo, int &altura, int &largura);
    static void OcupaJanelaInteira(int idVideo);
    static void UsaResolucaoOriginal(int idVideo);
    static void SetColoracao(int idVideo, PIG_Cor cor);
    static void SetOpacidade(int idVideo, int valor);
    static int GetOpacidade(int idVideo);

private:
    static int totalVideos;
    static CPoolNumeros *numVideos;
    static CVideo *videos[MAX_VIDEOS];
};

#endif
