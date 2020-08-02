
#ifndef CASSETLOADER_H
#define CASSETLOADER_H

#include <map>
#include <string>

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_surface.h>

class CHashNodeImagem
{
public:
    int cont;
    SDL_Surface *imagem;
    CHashNodeImagem(std::string nomeArq);
    ~CHashNodeImagem();
};

class CHashNodeAudio
{
public:
    int cont;
    Mix_Chunk *chunk;
    CHashNodeAudio(std::string nomeArq);
    ~CHashNodeAudio();
};

class CAssetLoader
{
public:
    static void Inicia();
    static void Encerra();
    static SDL_Surface *LoadImage(std::string nomeArq);
    static void FreeImage(std::string nomeArq);
    static Mix_Chunk *LoadAudio(std::string nomeArq);
    static void FreeAudio(std::string nomeArq);

private:
    static int totalBitmaps;
    static int totalAudios;
    static std::map<std::string, CHashNodeImagem*> mapImagens;
    static std::map<std::string, CHashNodeAudio*> mapAudios;
};

#endif
