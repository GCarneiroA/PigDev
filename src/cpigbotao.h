
#ifndef CPIGBOTAO_H
#define CPIGBOTAO_H

#include "cpigcomponente.h"

#include "tipos_pig.h"

#include <string>

typedef int (*AcaoBotao)(int,void*);
class CTimer;

class CPigBotao : public CPigComponente
{
public:
    CPigBotao(int idComponente,int px, int py, int alt,int larg,std::string nomeArq, int retiraFundo=1,int janela=0);

    CPigBotao(std::string nomeArqParam);

    ~CPigBotao();
    void DefineAcao(AcaoBotao funcao,void *parametro);
    void DefineAtalho(int teclaAtalho);
    void DefineCursor(PIG_EstadoComponente estado, int indiceMouse);
    void DefineTempoRepeticao(double segundos);
    void DefineBotaoRepeticao(bool repeticao);
    void DefineEstado(PIG_EstadoComponente estadoComponente);
    int TrataEvento(PIG_Evento evento);
    int Desenha();
private:
    int tecla;
    int largFrame;
    AcaoBotao acao;
    void *param;
    CTimer *timer;
    bool botaoRepeticao;
    double tempoRepeticao;

    int TrataMouse(PIG_Evento evento);
    int TrataTeclado(PIG_Evento evento);
    void TrataTimer();
    int OnMouseClick();
    int OnMouseOn();
    int OnMouseOff();
    CPigBotao LeArquivoParametros(std::string nomeArqParam);
};

#endif
