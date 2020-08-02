
#ifndef CPIGSCROLLBAR_H
#define CPIGSCROLLBAR_H

#include "cpigcomponente.h"

#include "cpigbotao.h"

typedef enum
{
    HORIZONTAL,
    VERTICAL
} Pig_Orientacao;

//tipo de fun��o a ser usada em altera��es na posi��o do handle da barra
//o par�metro int devolver� � fun��o o identificador do bot�o
//o par�metro double devolver� � fun��o a porcentagem atual da barra
//o par�metro void* devolver� � fun��o um par�etro personalizado passado ao m�todo DefineAcao();
typedef int (*AcaoScroll)(int,double,void*);

class CPigScrollBar : public CPigComponente
{
private:
    int vMin,vAtual,vMax;
    double porcentagemConcluida;
    Pig_Orientacao orientacao;
    int xOriginal,yOriginal;
    CPigBotao *botao1,*botao2,*handle;
    int altBotoes,largHandle,largUtil;
    int deltaBotao,deltaRodinha,deltaTeclado;
    int comprimento,largura;
    bool orientacaoCrescimento,setasAtivadas;
    int largReal,altReal;
    void *param;
    AcaoScroll acao;

    static int AcaoSetas(int idBotao, void* pontObjeto);
    void AjustaOrientacao();
    void AjustaHandle();
    int AvancaHandle(int novoValor,int delta = 0);
    void TrataClickTrilha(int px,int py);
    int TrataBotoes(PIG_Evento evento);
    int TrataRodinha(PIG_Evento evento);
    int TrataMouse(PIG_Evento evento);
    int TrataTeclado(PIG_Evento evento);
    void DefineEstadoComponentes(PIG_EstadoComponente estado);
    int OnMouseOn();
    int OnMouseOff();

public:

    CPigScrollBar(int idComponente,int px, int py,int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1,int janela=0);
    CPigScrollBar(std::string nomeArqParam);

    ~CPigScrollBar();
    static CPigScrollBar LeArquivoParametros(std::string nomeArqParam);
    void SetBotoes(int alturaBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1);
    void SetOrientacao(Pig_Orientacao novaOrientacao);
    int TrataEvento(PIG_Evento evento);
    void DefineEstado(PIG_EstadoComponente estadoComponente);
    void GetDimensoes(int &altura,int &largura)override;
    void GetDimensoesTrilha(int &altura,int &largura);
    void SetSetasAtivadas(bool estado);
    void MudaOrientacaoCrescimento();
    void SetDimensoes(int largura,int comprimento);
    void Move(int px,int py);
    void SetDeltas(int dBotao = 1,int dRodinha = 10,int dTeclado = 10);
    int Desenha();
    int GetValorAtual();
    void SetValorMinMax(int minimo,int maximo);
    void SetValorAtual(int valor);
};

#endif
