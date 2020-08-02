
#ifndef CMODOANIMACAO_H
#define CMODOANIMACAO_H

#include <vector>

typedef struct {
    int frame;      //n�mero do frame
    double tempo;   //tempo de exibi��o do frame
    int audio;      //audio a ser tocado quando o frame for exibido
} EstagioAnimacao;

class CModoAnimacao
{
public:
    CModoAnimacao(bool emLoop=true);
    ~CModoAnimacao();
    int InsereEstagio(int idFrame, double tempo, int idAudio);
    void SetTempo(int idEstagio, double novoTempo);
    void SetAudio(int idEstagio, int idAudio);
    void SetLoop(bool emLoop);
    bool GetLoop();
    void SetIndiceFrameAtual(int indice);
    int GetIndiceFrameAtual();
    int GetFrameAtual();
    int GetAudioAtual();
    double GetTempoAtual();
    int GetAudioFrame(int indiceFrame);
    double GetTempoFrame(int indiceFrame);
    int TestaTempo(double tempoDecorrido);
    bool GetEncerrou();
private:
    int frameAtual;                         //n�mero do frame atual
    bool loop;                              //se o modo tem loop ou n�o
    bool encerrou;                          //indica se o modo terminou de eibir todos os frames
    std::vector<EstagioAnimacao> estagios;  //informa��es dos est�gios (frames) que comp�em o modo
};

#endif
