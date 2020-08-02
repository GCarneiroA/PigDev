
#include "cassetloader.h"
#include <SDL2/SDL_image.h>

int CAssetLoader::totalBitmaps;
std::map<std::string, CHashNodeImagem*> CAssetLoader::mapImagens;
int CAssetLoader::totalAudios;
std::map<std::string, CHashNodeAudio*> CAssetLoader::mapAudios;

CHashNodeImagem::CHashNodeImagem(std::string nomeArq)
{
    cont = 1;
    imagem = IMG_Load(nomeArq.c_str());
}

CHashNodeImagem::~CHashNodeImagem()
{
    SDL_FreeSurface(imagem);
}

CHashNodeAudio::CHashNodeAudio(std::string nomeArq)
{
    cont = 1;
    chunk = Mix_LoadWAV(nomeArq.c_str());
}

CHashNodeAudio::~CHashNodeAudio()
{
    Mix_FreeChunk(chunk);
}

void CAssetLoader::Inicia()
{
    totalBitmaps=0;
    totalAudios=0;
}

void CAssetLoader::Encerra()
{
    for(std::map<std::string,CHashNodeImagem*>::iterator it = mapImagens.begin(); it != mapImagens.end(); ++it) {
        delete it->second;
    }
    for(std::map<std::string,CHashNodeAudio*>::iterator it = mapAudios.begin(); it != mapAudios.end(); ++it) {
        delete it->second;
    }
}

SDL_Surface *CAssetLoader::LoadImage(std::string nomeArq)
{
    std::map<std::string, CHashNodeImagem*>::iterator it = mapImagens.find(nomeArq);
    if (it == mapImagens.end()) {//n�o achou
        CHashNodeImagem *imagem = new CHashNodeImagem(nomeArq);
        mapImagens[nomeArq]=imagem;
        totalBitmaps++;
        return imagem->imagem;
    }else{
        it->second->cont++;
        return it->second->imagem;
    }
}

void CAssetLoader::FreeImage(std::string nomeArq)
{
    std::map<std::string, CHashNodeImagem*>::iterator it = mapImagens.find(nomeArq);
    if (it == mapImagens.end()) {//n�o achou
        printf("Nao existe asset carregado: %s\n",nomeArq.c_str());
    }else{
        it->second->cont--;
        if (it->second->cont==0){
            delete it->second;
            mapImagens.erase(it);
        }
    }
}

Mix_Chunk *CAssetLoader::LoadAudio(std::string nomeArq)
{
    std::map<std::string, CHashNodeAudio*>::iterator it = mapAudios.find(nomeArq);
    if (it == mapAudios.end()) {//n�o achou
        CHashNodeAudio *audio = new CHashNodeAudio(nomeArq);
        mapAudios[nomeArq] = audio;
        totalAudios++;
        return audio->chunk;
    }else{
        it->second->cont++;
        return it->second->chunk;
    }
}

void CAssetLoader::FreeAudio(std::string nomeArq)
{
    std::map<std::string, CHashNodeAudio*>::iterator it = mapAudios.find(nomeArq);
    if (it == mapAudios.end()) {//n�o achou
        printf("Nao existe asset carregado: %s\n",nomeArq.c_str());
    }else{
        it->second->cont--;
        if (it->second->cont==0){
            delete it->second;
            mapAudios.erase(it);
        }
    }
}
