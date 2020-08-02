
#ifndef CPARTICULA_H
#define CPARTICULA_H

#include "canimacao.h"

#include <string>

class CObjeto;
class CTimer;

class CParticula : public CAnimacao
{
public:
    int viva;

    CParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, std::string nomeArq,int usaGerenciadorTimer=1,int idJanela=0);
    CParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, CAnimacao *animacaoBase,int usaGerenciadorTimer=1,int idJanela=0);
    CParticula(int x, int y, int deslocX,int deslocY,int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, CObjeto *objBase,int usaGerenciadorTimer=1,int idJanela=0);
    void DefineLimites(int xMenor,int xMaior,int yMenor,int yMaior, float tempoMax);
    ~CParticula();
    void Move();
    void SetDimensoes(int altura, int largura);
    void MudaDirecao(int deslocX,int deslocY);
    int Colisao(CObjeto *outro);
    int Colisao(CParticula *outra);

private:
    CTimer *timer;
    int idTimer;
    int inix,iniy;
    int dx,dy;
    int menorX,maiorX,menorY,maiorY;
    int hp;
    int fading;
    double escalaIniX,escalaIniY;//usados para ajustar o tamanho da particula em rela��o ao tamanho origninal. Se a particula aumentar ou diminuir com o tempo, ainda ser� aplicado outro fator no m�todo Move();
    float limTempo;
    float angRot;
    float escalaInicial,escalaFinal;
    int tenhoAnimacaoBase;

    void IniciaBase(int x, int y, int deslocX, int deslocY, int vida, float anguloRot, float escalaIni, float escalaFim, int fadeOut, int usaGerenciadorTimer);
};

#endif
