
#include "caudio.h"

#include "cassetloader.h"

#include "cpigerroarquivo.h"

CAudio::CAudio(std::string nomeArquivo, int nLoops, int tempoPlay)
{
    nomeArq = nomeArquivo;
    #ifdef SHARE_AUDIO
        chunk = CAssetLoader::LoadAudio(nomeArq);
    #else
        chunk = Mix_LoadWAV(nomeArq.c_str());
    #endif

    if (!chunk) {
        throw CPigErroArquivo(nomeArquivo);
    }

    volume = VOLUME_PADRAO;
    tempoExecucao = tempoPlay;
    status = AUDIO_PARADO;
    loops = nLoops;
    canal = -1;
}

CAudio::~CAudio()
{
    #ifdef SHARE_AUDIO
        CAssetLoader::FreeAudio(nomeArq);
    #else
        Mix_FreeChunk(chunk);
    #endif
}

Mix_Chunk *CAudio::GetChunk()
{
    return chunk;
}

void CAudio::SetVolume(int valor)
{
    volume = valor;
    if (canal!=-1)
        Mix_Volume(canal,volume);
}


int CAudio::GetCanal()
{
    return canal;
}

int CAudio::GetVolume()
{
    return volume;
}

int CAudio::GetTempoPlay()
{
    return tempoExecucao;
}

PIG_StatusAudio CAudio::GetStatus()
{
    return status;
}

int CAudio::GetLoops(){
    return loops;
}

void CAudio::Play()
{
    status = AUDIO_TOCANDO;
    canal = Mix_PlayChannelTimed(-1, chunk, loops, tempoExecucao);
    Mix_Volume(canal,volume);
}

void CAudio::Pause()
{
    status = AUDIO_PAUSADO;
    if (canal != -1) {
        Mix_Pause(canal);
    }
}

void CAudio::Resume()
{
    status = AUDIO_TOCANDO;
    if (canal != -1) {
        Mix_Resume(canal);
    }
}

void CAudio::Stop()
{
    status = AUDIO_PARADO;
    if (canal != -1) {
        Mix_HaltChannel(canal);
        canal = -1;
    }
}
