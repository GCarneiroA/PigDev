
#ifndef CGERADORPARTICULA_H
#define CGERADORPARTICULA_H

#include "cparticula.h"
#include <string>

class CObjeto;
class CAnimacao;
class CParticula;

class CGeradorParticulas
{
public:
    CGeradorParticulas(int maximoParticulas, CObjeto *objBase, int audioCriacao,int audioEncerramento, int usaGerenciadorTimer, int idJanela);
    CGeradorParticulas(int maximoParticulas, CAnimacao *animaBase, int audioCriacao,int audioEncerramento, int usaGerenciadorTimer,int idJanela);
    CGeradorParticulas(int maximoParticulas, std::string nomeArq,int audioCriacao,int audioEncerramento, int usaGerenciadorTimer, int idJanela);
    ~CGeradorParticulas();
    void MoveParticulas();
    void Move(int nx,int ny);
    void Desloca(int dx,int dy);
    void MudaDirecao(int novaDx,int novaDy);
    void MudaRotacao(float angPerSec);
    void MudaEscala(float escalaIni,float escalaFim);
    void MudaHP(int novoValor);
    void MudaCor(PIG_Cor cor);
    void Desenha();
    void SetPivo(int pivoX,int pivoY);
    void SetPivo(float pivoX,float pivoY);
    int CriaParticula(int fadingOut = 0, int minX = -50, int minY = - 50, int maxX = LARG_TELA + 50, int maxY = ALT_TELA + 50, float maxTempo = 9999999.9);
    int Colisao(CObjeto *outro);
    int Colisao();
    int GetQtdAtivas();

private:
    CParticula *parts[MAX_PARTICULAS];
    int inix,iniy,dx,dy;            //posicao e direcao atual das particulas
    int pivoAbsX,pivoAbsY;          //pivo das particulas
    float pivoRelX,pivoRelY;
    bool modoPivoRelativo;
    int idJanela;
    int hp;
    float anguloRot;
    float escalaInicial,escalaFinal;
    int maxParticulas;
    std::string nomeArqImagem;
    int ativas;
    int usaGerTimer,tipoGerador;
    int audioInicio,audioFim;
    PIG_Cor corAtual;
    CAnimacao *animacaoBase;
    CObjeto *objetoBase;

    void IniciaBase(int maximoParticulas, std::string nomeArq, int usaGerenciadorTimer, int audioCriacao, int audioEncerramento, int janela, CObjeto *objBase, CAnimacao *animaBase);
};

#endif
