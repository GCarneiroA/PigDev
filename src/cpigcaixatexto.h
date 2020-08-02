
#ifndef CPIGCAIXATEXTO_H
#define CPIGCAIXATEXTO_H

#include "cpigcomponente.h"

class CTimer;

class CPigCaixaTexto : public CPigComponente
{
protected:
    //desenha o cursor
    void DesenhaCursor();

    //trata os eventos de mouse poss�veis
    int EventosMouse(PIG_Evento evento,SDL_Point p);

    //verifica se o evento ocorre dentro da �rea do componente
    int TrataEventoMouse(PIG_Evento evento);

    //trata teclas de movimenta��o do cursor
    virtual int TrataTeclasEspeciais(PIG_Evento evento);

    //trata os diversos tipos de eventos de teclado que podem ocorrer
    int TrataEventoTeclado(PIG_Evento evento);

    std::string texto;
    int fonteTexto;
    int posCursor;
    int xBase,xCursor,yCursor,yBase;
    int xBaseOriginal,yBaseOriginal;
    int margemHorEsq,margemHorDir,margemVertCima,margemVertBaixo;
    int altLetra;

    virtual void AjustaAlinhamento() =0;//pure virtual, porque cada classe derivada vai fazer ajustes diferentes

    virtual int SobeCursor() = 0;

    virtual int DesceCursor() = 0;

    virtual int PulaLinha() = 0;

    virtual std::string GetTextoVisivel() =0;//pure virtual, porque cada classe derivada vai retornar um texto de forma diferente

    //posiciona o cursor no eixo X (necess�rio, pois pode haver texto "escondido" � esquerda)
    void AjustaBaseTextoEixoX(int largParcial);
    //posiciona o cursor uma posi��o � frente
    int AvancaCursor();
    //posiciona o cursor uma posi��o atr�s
    int VoltaCursor();
    //reira um caracter com a tecla backspace
    int RetiraTextoBackSpace();
    //retira um caracter com a tecla delete
    int RetiraTextoDelete();
    //adiciona um texto (caracter ou string) na posi��o indicada pelo cursor (se poss�vel)
    int AdicionaTexto(std::string frase);
    //converte caracteres especiais, como acentos por exemplo
    std::string ConverteString(char *str);

    virtual int TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p) =0; //cada classe vai poder definir o que fazer com o bot�o direito

    //o botao esquerdo faz com que a edi��o do trexto comece ou que o cursor seja reposicionado
    virtual int TrataMouseBotaoEsquerdo(SDL_Point p,int inicioLinha = 0);

public:

    CPigCaixaTexto(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200,bool apenasNumeros=false,int retiraFundo=1,int janela=0);
    ~CPigCaixaTexto();
    //define o texto a ser mostrado no componente
    virtual int SetTexto(std::string frase);
    virtual void SetFonteTexto(int fonte);
    //recupera o texto armazenado no componente
    std::string GetTexto();
    //trata eventos relativos ao componente
    int TrataEvento(PIG_Evento evento);

    //define a cor do cursor
    void SetCorCursor(PIG_Cor cor);
    //define o estado do componente
    void DefineEstado(PIG_EstadoComponente estadoComponente);

    //reposiciona o componente
    void Move(int nx, int ny);

private:
    int OnMouseOn(){ return 0; }
    int OnMouseOff(){ return 0; }
    bool cursorExibido;
    int maxCaracteres;
    bool somenteNumeros;
    PIG_Cor corCursor;
    CTimer *timer;

};

#endif
