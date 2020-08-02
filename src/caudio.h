
#ifndef CAUDIO_H
#define CAUDIO_H

#include <string>
#include <SDL2/SDL_mixer.h>
#include "tipos_pig.h"

class CAudio
{
public:
    CAudio(std::string nomeArquivo, int nLoops, int tempoPlay = -1);
    ~CAudio();
    Mix_Chunk *GetChunk();
    void SetVolume(int valor);
    int GetCanal();
    int GetVolume();
    int GetTempoPlay();
    PIG_StatusAudio GetStatus();
    int GetLoops();
    void Play();
    void Pause();
    void Resume();
    void Stop();

private:
    Mix_Chunk *chunk;
    int volume;
    int tempoExecucao;
    PIG_StatusAudio status;
    int loops;
    std::string nomeArq;
    int canal;

};

#endif // CAUDIO_H
