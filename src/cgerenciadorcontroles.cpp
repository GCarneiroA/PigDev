
#include "cgerenciadorcontroles.h"

#include <SDL2/SDL_gamecontroller.h>

#include "ccontrole.h"

int CGerenciadorControles::qtdControles;
CControle *CGerenciadorControles::controles[MAX_CONTROLES];

void CGerenciadorControles::Inicia()
{
    qtdControles = SDL_NumJoysticks();
    for (int i = 0; i < qtdControles; ++i) {
        controles[i] = new CControle(i);
    }
}

void CGerenciadorControles::Encerra()
{
    for (int i = 0; i < qtdControles; ++i) {
        delete controles[i];
    }
}

int CGerenciadorControles::BotaoPressionado(int idControle, int botao)
{
    return controles[idControle]->BotaoPressionado((SDL_GameControllerButton)botao);
}

int CGerenciadorControles::EixoAcionado(int idControle, int eixo)
{
    return controles[idControle]->EixoAcionado((SDL_GameControllerAxis)eixo);
}

float CGerenciadorControles::EixoAcionadoPercentual(int idControle, int eixo)
{
    return controles[idControle]->EixoAcionadoPercentual((SDL_GameControllerAxis)eixo);
}

int CGerenciadorControles::GetQtdEixos(int idControle)
{
    return controles[idControle]->GetQtdEixos();
}

int CGerenciadorControles::GetQtdBotoes(int idControle)
{
    return controles[idControle]->GetQtdBotoes();
}

void CGerenciadorControles::GetNome(int idControle, char *nomeControle)
{
    controles[idControle]->GetNome(nomeControle);
}
