
#ifndef CGERENCIADORCONTROLES_H
#define CGERENCIADORCONTROLES_H

#include "tipos_pig.h"

class CControle;

class CGerenciadorControles
{
public:
    static void Inicia();
    static void Encerra();
    static int BotaoPressionado(int idControle, int botao);
    static int EixoAcionado(int idControle, int eixo);
    static float EixoAcionadoPercentual(int idControle, int eixo);
    static int GetQtdEixos(int idControle);
    static int GetQtdBotoes(int idControle);
    static void GetNome(int idControle, char *nomeControle);

private:
    static int qtdControles;
    static CControle *controles[MAX_CONTROLES];

};

#endif
