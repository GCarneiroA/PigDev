
#ifndef CCONTROLE_H
#define CCONTROLE_H

#include <SDL2/SDL_gamecontroller.h>

class CControle
{
public:
    CControle(int idControle);
    ~CControle();
    int BotaoPressionado(int botao);
    int EixoAcionado(int eixo);
    float EixoAcionadoPercentual(int eixo);
    int GetQtdEixos();
    int GetQtdBotoes();
    void GetNome(char *nomeControle);

private:
    int id;
    SDL_GameController *ctrl;
    SDL_Joystick *joy;
    int qtdEixos,qtdBotoes;
    char nome[50];
};

#endif
