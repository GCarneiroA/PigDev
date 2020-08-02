
#ifndef CMOUSE_H
#define CMOUSE_H

#include "tipos_pig.h"

#include <string>

class CPIGCursor;

class CMouse
{
public:
    static void Inicia(bool cursorCustomizado);
    static void Encerra();
    static int GetEstadoBotaoDireito();
    static int GetEstadoBotaoCentral();
    static int GetEstadoBotaoEsquerdo();
    static void PegaXY(int &x, int &y);
    static void ProcessaEvento(PIG_Evento evento);
    static void MudaCursor(int indice);
    static void Desenha(int idJanela=0);
    static void Move(int x,int y, int idJanela=0);
    static void CarregaCursor(int indice,std::string nomeArquivo,int idJanela=0);
private:
    static int cursorAtual;
    static CPIGCursor *cursores[MAX_CURSORES];
    static bool cursorProprio;
    static int mx,my;
    static int estadoBotaoDireito,estadoBotaoEsquerdo,estadoBotaoCentral;
};

#endif // CMOUSE_H
