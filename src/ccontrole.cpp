
#include "ccontrole.h"

CControle::CControle(int idControle)
{
    if (SDL_IsGameController(idControle)) {
        printf("Index \'%i\' is a compatible controller, named \'%s\'\n", idControle, SDL_GameControllerNameForIndex(idControle));
        ctrl = SDL_GameControllerOpen(idControle);
        joy = SDL_GameControllerGetJoystick(ctrl);
        id = idControle;
        qtdEixos = SDL_JoystickNumAxes(joy);
        qtdBotoes = SDL_JoystickNumButtons(joy);
        strcpy(nome,SDL_JoystickName(joy));
        printf("Axes: %d\n",qtdEixos);
        printf("Botoes: %d\n",qtdBotoes);
        printf("Nome: %s\n",nome);
    } else {
        printf("Index \'%i\' is not a compatible controller.\n", idControle);
    }
}

CControle::~CControle()
{
    SDL_GameControllerClose(ctrl);
}

int CControle::BotaoPressionado(int botao)
{
    return SDL_GameControllerGetButton(ctrl, (SDL_GameControllerButton)botao);
}

int CControle::EixoAcionado(int eixo)
{
    return SDL_GameControllerGetAxis(ctrl, (SDL_GameControllerAxis)eixo);
}

float CControle::EixoAcionadoPercentual(int eixo)
{
    return SDL_GameControllerGetAxis(ctrl, (SDL_GameControllerAxis)eixo) / 32768.0f;
}

int CControle::GetQtdEixos()
{
    return qtdEixos;
}

int CControle::GetQtdBotoes()
{
    return qtdBotoes;
}

void CControle::GetNome(char *nomeControle)
{
    strcpy(nomeControle, nome);
}
