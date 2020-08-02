
#include "cgerenciadorvideos.h"
#include "cpoolnumeros.h"
#include "cvideo.h"

int CGerenciadorVideos::totalVideos;
CPoolNumeros *CGerenciadorVideos::numVideos;
CVideo *CGerenciadorVideos::videos[MAX_VIDEOS];

void CGerenciadorVideos::Inicia(){
    av_register_all();
    avcodec_register_all();
    avdevice_register_all();
    avformat_network_init();

    totalVideos = 0;
    for (int i=0;i<MAX_VIDEOS;i++)
        videos[i] = NULL;
    numVideos = new CPoolNumeros(MAX_VIDEOS);
}

void CGerenciadorVideos::Encerra(){
    for (int i=0;i<MAX_VIDEOS;i++){
        if (videos[i]) delete videos[i];
    }
    delete numVideos;
    avformat_network_deinit();
}

int CGerenciadorVideos::CriaVideo(std::string nomeArquivo,int idJanela){
    int resp = numVideos->RetiraLivre();
    videos[resp] = new CVideo(nomeArquivo,idJanela);
    totalVideos++;
    return resp;
}

void CGerenciadorVideos::DestroiVideo(int idVideo){
    numVideos->DevolveUsado(idVideo);
    delete videos[idVideo];
    totalVideos--;
    videos[idVideo] = NULL;
}

void CGerenciadorVideos::SetSeek(int idVideo, double incremento){
    videos[idVideo]->SetSeek(incremento);
}

void CGerenciadorVideos::Play(int idVideo){
    videos[idVideo]->Play();
}

void CGerenciadorVideos::Stop(int idVideo){
    videos[idVideo]->Stop();
}

void CGerenciadorVideos::Pause(int idVideo){
    videos[idVideo]->Pause();
}

void CGerenciadorVideos::Resume(int idVideo){
    videos[idVideo]->Resume();
}

int CGerenciadorVideos::Desenha(int idVideo){
    videos[idVideo]->Desenha();
}

void CGerenciadorVideos::SetVolume(int idVideo, double valor){
    videos[idVideo]->SetVolume(valor);
}

double CGerenciadorVideos::GetVolume(int idVideo){
    return videos[idVideo]->GetVolume();
}

std::string CGerenciadorVideos::GetNomeArquivo(int idVideo){
    return videos[idVideo]->GetNomeArquivo();
}

double CGerenciadorVideos::GetTempoAtual(int idVideo){
    return videos[idVideo]->GetTempoAtual();
}

std::string CGerenciadorVideos::GetTempoAtualString(int idVideo){
    return videos[idVideo]->GetTempoAtualString();
}

double CGerenciadorVideos::GetTempoTotal(int idVideo){
    return videos[idVideo]->GetTempoTotal();
}

std::string CGerenciadorVideos::GetTempoTotalString(int idVideo){
    return videos[idVideo]->GetTempoTotalString();
}

double CGerenciadorVideos::GetTempoFrame(int idVideo){
    return videos[idVideo]->GetTempoFrame();
}

double CGerenciadorVideos::GetFPS(int idVideo){
    return videos[idVideo]->GetFPS();
}

void CGerenciadorVideos::SetAngulo(int idVideo, float a){
    videos[idVideo]->SetAngulo(a);
}

double CGerenciadorVideos::GetAngulo(int idVideo){
    return videos[idVideo]->GetAngulo();
}

void CGerenciadorVideos::SetFlip(int idVideo, PIG_Flip valor){
    videos[idVideo]->SetFlip(valor);
}

PIG_Flip CGerenciadorVideos::GetFlip(int idVideo){
    return videos[idVideo]->GetFlip();
}

void CGerenciadorVideos::SetPivo(int idVideo, int px,int py){
    videos[idVideo]->SetPivo(px,py);
}

void CGerenciadorVideos::SetPivo(int idVideo, float px,float py){
    videos[idVideo]->SetPivo(px,py);
}

void CGerenciadorVideos::GetPivo(int idVideo, int &px,int &py){
    videos[idVideo]->GetPivo(px,py);
}

void CGerenciadorVideos::Move(int idVideo, int nx,int ny){
    videos[idVideo]->Move(nx,ny);
}

void CGerenciadorVideos::SetDimensoes(int idVideo, int altura,int largura){
    videos[idVideo]->SetDimensoes(altura,largura);
}

void CGerenciadorVideos::GetDimensoes(int idVideo, int &altura, int &largura){
    videos[idVideo]->GetDimensoes(altura,largura);
}

void CGerenciadorVideos::GetDimensoesOriginais(int idVideo, int &altura,int &largura){
    videos[idVideo]->GetDimensoesOriginais(altura,largura);
}

void CGerenciadorVideos::OcupaJanelaInteira(int idVideo){
    videos[idVideo]->OcupaJanelaInteira();
}

void CGerenciadorVideos::UsaResolucaoOriginal(int idVideo){
    videos[idVideo]->UsaResolucaoOriginal();
}

void CGerenciadorVideos::SetColoracao(int idVideo, PIG_Cor cor){
    videos[idVideo]->SetColoracao(cor);
}

void CGerenciadorVideos::SetOpacidade(int idVideo, int valor){
    videos[idVideo]->SetOpacidade(valor);
}

int CGerenciadorVideos::GetOpacidade(int idVideo){
    return videos[idVideo]->GetOpacidade();
}
