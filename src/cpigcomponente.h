
#ifndef CPIGCOMPONENTE_H
#define CPIGCOMPONENTE_H

#include "cvisual.h"

typedef enum
{
    COMPONENTE_NORMAL,
    COMPONENTE_MOUSEOVER,
    COMPONENTE_ACIONADO,
    COMPONENTE_DESABILITADO,
    COMPONENTE_EDITANDO,
    COMPONENTE_INVISIVEL
} PIG_EstadoComponente;

typedef enum
{
    PIG_COMPONENTE_CIMA_CENTRO,
    PIG_COMPONENTE_CIMA_ESQ,
    PIG_COMPONENTE_CIMA_DIR,
    PIG_COMPONENTE_BAIXO_CENTRO,
    PIG_COMPONENTE_BAIXO_DIR,
    PIG_COMPONENTE_BAIXO_ESQ,
    PIG_COMPONENTE_DIR_CIMA,
    PIG_COMPONENTE_DIR_BAIXO,
    PIG_COMPONENTE_DIR_CENTRO,
    PIG_COMPONENTE_ESQ_BAIXO,
    PIG_COMPONENTE_ESQ_CENTRO,
    PIG_COMPONENTE_ESQ_CIMA,
    PIG_COMPONENTE_CENTRO_CENTRO,
    PIG_COMPONENTE_PERSONALIZADA
} PIG_PosicaoComponente;

typedef enum
{
    NORTE,
    SUL,
    LESTE,
    OESTE,
    NORDESTE,
    NOROESTE,
    SUDESTE,
    SUDOESTE,
    CENTRO
} PIG_Ancora;

class CPigComponente : public CVisual
{
public:
    CPigComponente(int idComponente,int px,int py, int altura, int largura, int janela=0);
    CPigComponente(int idComponente,int px,int py, int altura, int largura, std::string nomeArq,int retiraFundo=1,int janela=0);
    ~CPigComponente();

    int GetId();
    virtual int Desenha()=0;
    virtual int TrataEvento(PIG_Evento evento)=0;

    void SetHint(std::string novoHint);
    void SetLabel(std::string novoLabel);
    virtual void SetAudio(int idAudio);
    virtual void SetFonteHint(int fonte);
    virtual void SetFonteLabel(int fonte);
    std::string GetLabel();
    virtual int SetPosicaoPadraoLabel(PIG_PosicaoComponente pos);
    virtual int SetPosicaoPersonalizadaLabel(int rx, int ry);
    virtual void DefineEstado(PIG_EstadoComponente estadoComponente)=0;
    PIG_EstadoComponente GetEstado();

    PIG_PosicaoComponente GetPosComponente();
    void SetPosPadraoExternaComponente(PIG_PosicaoComponente pos,CPigComponente *componenteAssociado);
    void SetPosPadraoComponente(PIG_Ancora ancora);

protected:
    PIG_EstadoComponente estado;
    std::string hint,label;
    int fonteHint,fonteLabel;
    int audioComponente;
    int antesOn,agoraOn;
    int id;
    int labelX,labelY;
    int altLetraLabel;
    PIG_PosicaoComponente posLabel,posComponente;

    virtual int OnMouseOn()=0;
    virtual int OnMouseOff()=0;

    void IniciaBase(int idComponente, int px, int py);
    void EscreveHint();
    int MouseSobre(int mx, int my);
    void DesenhaLabel();

};

#endif
