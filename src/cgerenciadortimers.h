
#ifndef CGERENCIADORTIMERS_H
#define CGERENCIADORTIMERS_H

#include "tipos_pig.h"

class CPoolNumeros;
class CTimer;

class CGerenciadorTimers
{
public:
    static void Inicia();
    static void Encerra();
    static int CriaTimer(bool congelado=false);
    static void DestroiTimer(int id_timer);
    static void PausaTodos();
    static void DespausaTodos();
    static float GetTempoDecorrido(int idTimer);
    static void ReiniciaTimer(int idTimer,bool congelado=false);
    static void PausaTimer(int idTimer);
    static void DespausaTimer(int idTimer);
private:
    static int totalTimers;
    static CPoolNumeros *numTimers;
    static CTimer *timers[MAX_TIMERS];
};

#endif
