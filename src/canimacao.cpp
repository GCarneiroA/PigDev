
#include "canimacao.h"
#include "cgerenciadortimers.h"
#include "cgerenciadoraudios.h"
#include "cmodoanimacao.h"
#include "ctimer.h"

//cria uma anima��o a partir de um arquivo de spritesheet
CAnimacao::CAnimacao(std::string nomeArq, int usaGerenciadorTimer, PIG_Cor *corFundo, int retiraFundo, int idJanela)
    : CObjeto(nomeArq, corFundo, retiraFundo, idJanela)
{
    souCopia = 0;
    offx = offy = 0;
    modoAtual = 0;

    for (int i=0;i<MAX_FRAMES;i++)
        frames[i] = NULL;

    qtdTotalFrames = 0;
    for (int i=0;i<MAX_MODOS;i++){
        modos[i] = NULL;
    }

    if (usaGerenciadorTimer){
        tempoFrame = NULL;
        idTimer = CGerenciadorTimers::CriaTimer();
    }else{
        tempoFrame = new CTimer(false);
        idTimer = -1;
    }
}

//cria uma anima��oa partir deoutra anima��o j� existente
CAnimacao::CAnimacao(CAnimacao* base, int usaGerenciadorTimer, PIG_Cor *corFundo, int retiraFundo, int idJanela)
    : CObjeto(base->nomeArquivo, corFundo, retiraFundo, idJanela)
{
    souCopia= 1;

    qtdTotalFrames = base->qtdTotalFrames;
    for (int i=0;i<MAX_FRAMES;i++){
        frames[i] = base->frames[i];
    }

    for (int i=0;i<MAX_MODOS;i++){
        modos[i] = base->modos[i];
    }
    CObjeto::SetDimensoes(base->alt,base->larg);

    offx = base->offx;
    offy = base->offy;
    modoAtual = base->modoAtual;

    if (usaGerenciadorTimer){
        tempoFrame = NULL;
        idTimer = CGerenciadorTimers::CriaTimer();
    }else{
        tempoFrame = new CTimer(false);
        idTimer = -1;
    }
}

//cria uma anima��o a aprtir de um objeto
CAnimacao::CAnimacao(CObjeto *base, int usaGerenciadorTimer, PIG_Cor *corFundo, int retiraFundo, int idJanela)
    : CObjeto(base, corFundo, retiraFundo, idJanela)
{
    offx = offy = 0;
    modoAtual = 0;

    for (int i=0;i<MAX_FRAMES;i++){
        frames[i] = NULL;
    }

    for (int i=0;i<MAX_MODOS;i++){
        modos[i] = NULL;
    }

    idTimer = -1;
    tempoFrame = NULL;
}

//destroi uma anima��o
CAnimacao::~CAnimacao()
{
    if (!souCopia){
        for (int i=0;i<MAX_MODOS;i++){
            if (modos[i])
                delete modos[i];
        }
        for (int i=0;i<MAX_FRAMES;i++)
            if (frames[i])
                free(frames[i]);
    }

    if (tempoFrame)
        delete tempoFrame;
    else if (idTimer!=-1)
        CGerenciadorTimers::DestroiTimer(idTimer);
}

//define o retangulo da imagem que corresponde ao frame
void CAnimacao::CriaFrame(int codFrame, int x, int y, int altura, int largura)
{
    if (frames[codFrame])
        free(frames[codFrame]);
    
    frames[codFrame] = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    frames[codFrame]->x = x;
    frames[codFrame]->y = y;
    frames[codFrame]->h = altura;
    frames[codFrame]->w = largura;
}

//cria um modo vazio, sem frames associados
void CAnimacao::CriaModo(int idModo, int loop)
{
    if (modos[idModo])
        delete modos[idModo];
    
    modos[idModo] = new CModoAnimacao(loop);
}

//insere um frame em um dos modos
void CAnimacao::InsereFrame(int idModo, int idFrame, float delayFrame, int audio)
{
    modos[idModo]->InsereEstagio(idFrame, delayFrame, audio);
}

//muda o modo atual
void CAnimacao::MudaModo(int idModo, int indiceFrame, int forcado)
{
    if (forcado || (modos[modoAtual]&&modos[modoAtual]->GetEncerrou())) {
        modoAtual = idModo;

        modos[modoAtual]->SetIndiceFrameAtual(indiceFrame);

        AtualizaFrameAtual(modos[modoAtual]);
    }
}

//retorna o n�merodo modo atual
int CAnimacao::GetModoAtual()
{
    return modoAtual;
}

//desenha a anima��o
int CAnimacao::Desenha()
{
    int resp=0; //0 indica que que o modo de anima��o atual n�o encerrou

    if (modos[modoAtual]!=NULL) {
        float tempoDecorrido;

        if (tempoFrame)
            tempoDecorrido = tempoFrame->GetTempoDecorrido();
        else tempoDecorrido = CGerenciadorTimers::GetTempoDecorrido(idTimer);

        if (modos[modoAtual]->TestaTempo(tempoDecorrido)){
            AtualizaFrameAtual(modos[modoAtual]);
        }else resp = modos[modoAtual]->GetEncerrou();//pode ter encerrado de desenhar todos os est�gios do modo
    }

    int px = x+offx;
    int py = y+offy;

    CObjeto::Move(px,py);
    CObjeto::Desenha(NULL);

    px -=offx;
    py -=offy;

    CObjeto::Move(px,py);

    return resp;
}

//pausa a anima��o
void CAnimacao::Pausa()
{
    if (tempoFrame)
        tempoFrame->Pausa();
    else
        CGerenciadorTimers::PausaTimer(idTimer);
}

//despausa a anima��o
void CAnimacao::Despausa()
{
    if (tempoFrame)
        tempoFrame->Despausa();
    else
        CGerenciadorTimers::DespausaTimer(idTimer);
}

//define o tempo de um frame j� criado
void CAnimacao::SetTempoFrame(int modo, int indiceFrame, double tempo)
{
    modos[modo]->SetTempo(indiceFrame,tempo);
}

//define se um modo j� criado ter� ou n�o loop
void CAnimacao::SetLoopModo(int modo, int loop)
{
    modos[modo]->SetLoop(loop);
}

//define o audio de um frame j� criado
void CAnimacao::SetAudioFrame(int modo, int indiceFrame, int idAudio)
{
    modos[modo]->SetAudio(indiceFrame,idAudio);
}

//retorna o tempo de dura��o de um frame j� criado
double CAnimacao::GetTempoFrame(int modo, int indiceFrame)
{
    return modos[modo]->GetTempoFrame(indiceFrame);
}

//retorna se um modo tem ou n�o loop
bool CAnimacao::GetLoopModo(int modo)
{
    return modos[modo]->GetLoop();
}

//retorna o audio de um frame j� criado
int CAnimacao::GetAudioFrame(int modo, int indiceFrame)
{
    return modos[modo]->GetAudioFrame(indiceFrame);
}

//muda o frame a ser exibido do modo atual
void CAnimacao::AtualizaFrameAtual(CModoAnimacao *modo)
{
    frameAtual = modo->GetFrameAtual();
    CObjeto::DefineFrame(*(frames[frameAtual]));

    int audio = modo->GetAudioAtual();
    if (audio>=0) {
        CGerenciadorAudios::Play(audio);
    }

    if (tempoFrame)
        tempoFrame->Reinicia(false);
    else
        CGerenciadorTimers::ReiniciaTimer(idTimer);
}
