
#ifndef CGERENCIADORAUDIOS_H
#define CGERENCIADORAUDIOS_H

#include "caudio.h"
#include "cpoolnumeros.h"

#include <SDL2/SDL_mixer.h>

class CAudio;
class CPoolNumeros;

class CGerenciadorAudios
{
public:
    static void Inicia();
    static void Encerra();
    static CAudio *GetAudio(int idAudio);
    static void CarregaBackground(std::string nomeArquivo);
    static void PlayBackground(int nVezes);
    static void StopBackground();
    static void PauseBackground();
    static void ResumeBackground();
    static PIG_StatusAudio GetStatusBackground();
    static void SetVolumeBackground(int valor);
    static int GetVolumeBackground();
    static int CriaAudio(std::string nomeArquivo,int nLoops,int tempoExecucao=-1);
    static void DestroiAudio(int idAudio);
    static void SetVolume(int idAudio,int volume);
    static int GetVolume(int idAudio);
    static void SetVolumeTudo(int volume);
    static void Play(int idAudio);
    static void Pause(int idAudio);
    static void Resume(int idAudio);
    static void Stop(int idAudio);
    static PIG_StatusAudio GetStatus(int idAudio);
    static void StopTudo();
    static void PauseTudo();
    static void ResumeTudo();

private:
    static void TrataParadaAudio(int canal);
    static void TrataParadaBackground();

    static int totalAudios;
    static CPoolNumeros *numAudios;
    static CAudio *audios[MAX_AUDIOS];
    static int audioIds[QTD_CANAIS_PADRAO];
    static Mix_Music *background;
    static int volumeBackground;
    static PIG_StatusAudio statusBackground;
};

#endif // CGERENCIADORAUDIOS_H
