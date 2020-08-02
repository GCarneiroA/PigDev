
#ifndef CTIMER_H
#define CTIMER_H

#include <chrono>

class CTimer
{
private:
    std::chrono::system_clock::time_point inicio;
    std::chrono::system_clock::time_point pausa;
    double totalPausa;
    bool pausado;

public:
    CTimer(bool congelado);
    ~CTimer();
    double GetTempoDecorrido();
    void Pausa();
    void Despausa();
    void Reinicia(bool congelado);
    CTimer* Copia();
};

#endif
