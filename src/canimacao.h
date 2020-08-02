
#ifndef CANIMACAO_H
#define CANIMACAO_H

#include "cobjeto.h"
#include "tipos_pig.h"
#include <string>

class CModoAnimacao;
class CTimer;

class CAnimacao : public CObjeto
{
public:

    //cria uma anima��o a partir de um arquivo de spritesheet
    CAnimacao(std::string nomeArq, int usaGerenciadorTimer = 0, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int idJanela = 0);

    //cria uma anima��oa partir deoutra anima��o j� existente
    CAnimacao(CAnimacao* base, int usaGerenciadorTimer = 0, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int idJanela = 0);

    //cria uma anima��o a aprtir de um objeto
    CAnimacao(CObjeto *base, int usaGerenciadorTimer = 0, PIG_Cor *corFundo = NULL, int retiraFundo = 1, int idJanela = 0);

    //destroi uma anima��o
    ~CAnimacao();

    //define o retangulo da imagem que corresponde ao frame
    void CriaFrame(int codFrame, int x, int y, int altura, int largura);

    //cria um modo vazio, sem frames associados
    void CriaModo(int idModo, int loop);

    //insere um frame em um dos modos
    void InsereFrame(int idModo, int idFrame, float delayFrame, int audio);

    //muda o modo atual
    void MudaModo(int idModo, int indiceFrame = 0, int forcado = 1);

    //retorna o n�merodo modo atual
    int GetModoAtual();

    //desenha a anima��o
    int Desenha();

    //pausa a anima��o
    void Pausa();

    //despausa a anima��o
    void Despausa();

    //define o tempo de um frame j� criado
    void SetTempoFrame(int modo, int indiceFrame, double tempo);

    //define se um modo j� criado ter� ou n�o loop
    void SetLoopModo(int modo, int loop);

    //define o audio de um frame j� criado
    void SetAudioFrame(int modo, int indiceFrame, int idAudio);

    //retorna o tempo de dura��o de um frame j� criado
    double GetTempoFrame(int modo, int indiceFrame);

    //retorna se um modo tem ou n�o loop
    bool GetLoopModo(int modo);

    //retorna o audio de um frame j� criado
    int GetAudioFrame(int modo, int indiceFrame);

private:
    //muda o frame a ser exibido do modo atual
    void AtualizaFrameAtual(CModoAnimacao *modo);

    int souCopia;                   //indica se esta anima��o � c�pia (foi criada a partir) de outra anima��o
    int qtdTotalFrames;             //indica o total de frames existentes nesta anima��o
    CModoAnimacao *modos[MAX_MODOS];  //modos da anima��oi
    SDL_Rect *frames[MAX_FRAMES];   //frames da anima��o
    CTimer *tempoFrame;             //timer da anima��o (se estiver sendo utilizado um timer espec�fico)
    int idTimer;                    //timer da anima��o (se estiver sendo utilizado o gerenciador de timers)
    int offx,offy;                  //offset (x,y) a ser utilizado junto com a posi��o (x,y) para desenhar oa anima��o
    int modoAtual;                  //n�mero que indica o modo atual
    int frameAtual;                 //n�mero que indica o frame atual
};

#endif
