
#include "tipos_pig.h"
#include "cgerenciadoraudios.h"
#include "cpigerroindice.h"
#include "cpoolnumeros.h"

CAudio *CGerenciadorAudios::audios[MAX_AUDIOS];
int CGerenciadorAudios::totalAudios;
CPoolNumeros *CGerenciadorAudios::numAudios;
int CGerenciadorAudios::audioIds[QTD_CANAIS_PADRAO];
Mix_Music *CGerenciadorAudios::background;
int CGerenciadorAudios::volumeBackground;
PIG_StatusAudio CGerenciadorAudios::statusBackground;

void CGerenciadorAudios::Inicia()
{
    Mix_OpenAudio(FREQ_AUDIO_PADRAO,MIX_DEFAULT_FORMAT,2,TAMANHO_CHUNK);

    Mix_AllocateChannels(QTD_CANAIS_PADRAO);

    totalAudios = 0;
    for (int i=0;i<MAX_AUDIOS;i++){
        audios[i] = NULL;
    }
    for (int i=0;i<QTD_CANAIS_PADRAO;i++){
        audioIds[i] = -1;
    }
    numAudios = new CPoolNumeros(MAX_AUDIOS);

    Mix_ChannelFinished(TrataParadaAudio);
    background = NULL;
    volumeBackground = VOLUME_PADRAO;
    statusBackground = AUDIO_PARADO;
    Mix_HookMusicFinished(TrataParadaBackground);
}

 void CGerenciadorAudios::Encerra(){
    StopTudo();
    for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i]) delete audios[i];
    }
    delete numAudios;
    if (background)
        Mix_FreeMusic(background);
    Mix_CloseAudio();
}

  CAudio *CGerenciadorAudios::GetAudio(int idAudio){
    if (idAudio<0||idAudio>=MAX_AUDIOS||audios[idAudio]==NULL) throw CPigErroIndice(idAudio,"audios");
    return audios[idAudio];
}

 void CGerenciadorAudios::CarregaBackground(std::string nomeArquivo){
    if (background)
        Mix_FreeMusic(background);
    background = Mix_LoadMUS(nomeArquivo.c_str());
}

 void CGerenciadorAudios::PlayBackground(int nVezes){
    if (background){
        Mix_PlayMusic(background, nVezes);
        statusBackground = AUDIO_TOCANDO;
    }
}

 void CGerenciadorAudios::StopBackground(){
    if (background){
        Mix_HaltMusic();
        statusBackground = AUDIO_PARADO;
    }
}

 void CGerenciadorAudios::PauseBackground(){
    if (background){
        Mix_PauseMusic();
        statusBackground = AUDIO_PAUSADO;
    }
}

 void CGerenciadorAudios::ResumeBackground(){
    if (background){
        Mix_ResumeMusic();
        statusBackground = AUDIO_TOCANDO;
    }
}

 PIG_StatusAudio CGerenciadorAudios::GetStatusBackground(){
    return statusBackground;
}

 void CGerenciadorAudios::SetVolumeBackground(int valor){
    volumeBackground = valor;
    Mix_VolumeMusic(volumeBackground);
}

 int CGerenciadorAudios::GetVolumeBackground(){
    return volumeBackground;
}

 int CGerenciadorAudios::CriaAudio(std::string nomeArquivo,int nLoops,int tempoExecucao){
    int resp = numAudios->RetiraLivre();
    audios[resp] = new CAudio(nomeArquivo,nLoops,tempoExecucao);
    totalAudios++;
    return resp;
}

 void CGerenciadorAudios::DestroiAudio(int idAudio){
    if (idAudio<0||idAudio>=totalAudios||audios[idAudio]==NULL) throw CPigErroIndice(idAudio,"audios");
    numAudios->DevolveUsado(idAudio);
    delete audios[idAudio];
    totalAudios--;
    audios[idAudio] = NULL;
}

  void CGerenciadorAudios::SetVolume(int idAudio,int volume){
    GetAudio(idAudio)->SetVolume(volume);
}

  int CGerenciadorAudios::GetVolume(int idAudio){
    return GetAudio(idAudio)->GetVolume();
}

  void CGerenciadorAudios::SetVolumeTudo(int volume){
    Mix_Volume(-1,volume);
    for (int i=0;i<MAX_AUDIOS;i++)
        if (audios[i])
            audios[i]->SetVolume(volume);
}

  void CGerenciadorAudios::Play(int idAudio){
    CAudio *audio = GetAudio(idAudio);
    audio->Play();
    audioIds[audio->GetCanal()] = idAudio;
}

  void CGerenciadorAudios::Pause(int idAudio){
    GetAudio(idAudio)->Pause();
}

  void CGerenciadorAudios::Resume(int idAudio){
    GetAudio(idAudio)->Resume();
}

  void CGerenciadorAudios::Stop(int idAudio){
    GetAudio(idAudio)->Stop();
}

  PIG_StatusAudio CGerenciadorAudios::GetStatus(int idAudio){
    return GetAudio(idAudio)->GetStatus();
}

  void CGerenciadorAudios::StopTudo(){
    Mix_HaltChannel(-1);
    for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i]){
            audios[i]->Stop();
        }
    }
}

  void CGerenciadorAudios::PauseTudo(){
    Mix_Pause(-1);
    for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i])
            audios[i]->Pause();
    }
}

  void CGerenciadorAudios::ResumeTudo(){
    Mix_Resume(-1);
    for (int i=0;i<MAX_AUDIOS;i++){
        if (audios[i])
            audios[i]->Resume();
    }
}
