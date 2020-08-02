
#ifndef CPIGAREADETEXTO_H
#define CPIGAREADETEXTO_H

#include "tipos_pig.h"
#include "cpigcaixatexto.h"
#include "cpigscrollbar.h"

#include <vector>
#include <string>

struct SDL_Point;

class CPigAreaDeTexto: public CPigCaixaTexto
{
public:
    CPigAreaDeTexto(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200,int retiraFundo=1,int janela=0);
    CPigAreaDeTexto(std::string nomeArqParam);
    ~CPigAreaDeTexto();
    static CPigAreaDeTexto LeArquivoParametros(std::string nomeArqParam);
    void SetScrollBarVertical(int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1);
    int SetBotoesScrollBarVertical(int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1);
    void SetScrollBarHorizontal(int larguraTotal,int comprimentoTotal,int larguraHandle,std::string imgHandle,std::string imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1);
    int SetBotoesScrollBarHorizontal(int larguraBotoes,std::string imgBotao1,std::string imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1);
    void SetPosPadraoScrollHorizontal(PIG_PosicaoComponente pos);
    void SetPosPadraoScrollVertical(PIG_PosicaoComponente pos);
    void Move(int px,int py);
    void MoveScrollBarHorizontal(int px,int py);
    void MoveScrollBarVertical(int px,int py);
    void SetDimensoes(int altura,int largura);

    int Desenha() override;
    void SetFonteTexto(int fonte) override;
    void SetLinhasAbaixoTexto(bool visivel,PIG_Cor cor = PRETO);
    void SetLargMaxTexto(int largMaxTexto);
    int TrataEvento(PIG_Evento evento)override;
    void SetEspacoEntreAsLinhas(int espaco);
    int SetTexto(std::string frase)override;
    void SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima);
    std::vector<std::string> GetLinhasTexto();

private:
    int largMax;
    int espacoEntreLinhas;
    bool linhasPauta;
    CPigScrollBar *scrollVertical,*scrollHorizontal;
    bool scrollVerticalAtivado,scrollHorizontalAtivado;
    int xOriginal,yOriginal;
    int largReal,altReal;

    std::vector<std::string> linhas;

    PIG_Cor corLinhasTexto;

    std::string GetTextoVisivel();
    void TrataScrollBarVertical(PIG_Evento evento);
    void TrataScrollBarHorizontal(PIG_Evento evento);
    void AcionaScrollBarVertical();
    void AcionaScrollBarHorizontal();
    int GetLarguraLinhaMaior();
    void DesenhaMarcacaoMargem();
    void ResetaValoresBase();
    void AjustaBaseTextoEixoY();
    void AjustaAlinhamento() override;
    int TrataMouseBotaoEsquerdo(SDL_Point p,int inicioLinha = 0)override;
    int TrataMouseBotaoEsquerdoESobeDesceCursor(SDL_Point p,int inicioLinha = 0,int linha = 0);
    int TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p);
    int GetLinhaComMouseEmCima();
    int GetPosInicialDeUmaLinha(int linha);
    int GetLinhaDeUmaPos(int pos);
    void DesenhaLinhasHorizontais();
    int SobeCursor();
    int DesceCursor();
    int PulaLinha();
};

#endif
