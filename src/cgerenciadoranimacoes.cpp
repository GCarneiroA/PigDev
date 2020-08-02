
#include "cgerenciadoranimacoes.h"
#include "canimacao.h"
#include "cpoolnumeros.h"

CPoolNumeros *CGerenciadorAnimacoes::numAnimacoes;
int CGerenciadorAnimacoes::totalAnimacoes;
CAnimacao *CGerenciadorAnimacoes::animacoes[MAX_ANIMACOES];

    CAnimacao *CGerenciadorAnimacoes::GetAnimacao(int idAnimacao){
        return animacoes[idAnimacao];
    }

    void CGerenciadorAnimacoes::Inicia(SDL_Renderer *renderer){
        totalAnimacoes = 0;
        for (int i=0;i<MAX_ANIMACOES;i++)
            animacoes[i] = NULL;
        numAnimacoes = new CPoolNumeros(MAX_ANIMACOES);
    }

    void CGerenciadorAnimacoes::Encerra(){
        for (int i=0;i<MAX_ANIMACOES;i++){
            if (animacoes[i]) delete animacoes[i];
        }
        delete numAnimacoes;
    }

    int CGerenciadorAnimacoes::CriaAnimacao(std::string nomeArquivoBMP,PIG_Cor *corFundo,int retiraFundo,int idJanela){
        int resp = numAnimacoes->RetiraLivre();
        animacoes[resp] = new CAnimacao(nomeArquivoBMP,0,corFundo,retiraFundo,idJanela);
        totalAnimacoes++;
        return resp;
    }

    int CGerenciadorAnimacoes::CriaAnimacao(int idAnimacaoBase,PIG_Cor *corFundo,int retiraFundo,int idJanela){
        int resp = numAnimacoes->RetiraLivre();
        animacoes[resp] = new CAnimacao(animacoes[idAnimacaoBase],0,corFundo,retiraFundo,idJanela);
        totalAnimacoes++;
        return resp;
    }

    void CGerenciadorAnimacoes::DestroiAnimacao(int idAnimacao){
        numAnimacoes->DevolveUsado(idAnimacao);
        delete animacoes[idAnimacao];
        totalAnimacoes--;
        animacoes[idAnimacao] = NULL;
    }

    void CGerenciadorAnimacoes::Move(int idAnimacao,int px,int py){
        animacoes[idAnimacao]->Move(px,py);
    }

    void CGerenciadorAnimacoes::Desloca(int idAnimacao,int dx,int dy){
        animacoes[idAnimacao]->Desloca(dx,dy);
    }

    void CGerenciadorAnimacoes::GetPosicaoXY(int idAnimacao, int *x,int *y){
        animacoes[idAnimacao]->GetXY(*x,*y);
    }

     int CGerenciadorAnimacoes::Desenha(int idAnimacao){
        return animacoes[idAnimacao]->Desenha();
    }

     void CGerenciadorAnimacoes::CriaFrame(int idAnimacao,int codFrame,int x,int y,int altura,int largura){
        animacoes[idAnimacao]->CriaFrame(codFrame,x,y,altura,largura);
    }

     void CGerenciadorAnimacoes::CriaModo(int idAnimacao,int idModo, int loop){
        animacoes[idAnimacao]->CriaModo(idModo,loop);
    }

     void CGerenciadorAnimacoes::InsereFrame(int idAnimacao, int idModo,int idFrame, float delayFrame,int idAudio){
        animacoes[idAnimacao]->InsereFrame(idModo,idFrame,delayFrame,idAudio);
    }

     int CGerenciadorAnimacoes::GetModo(int idAnimacao){
        return animacoes[idAnimacao]->GetModoAtual();
    }

     void CGerenciadorAnimacoes::MudaModo(int idAnimacao,int idModo,int indiceFrame,int forcado){
        animacoes[idAnimacao]->MudaModo(idModo,indiceFrame,forcado);
    }

     void CGerenciadorAnimacoes::SetOpacidade(int idAnimacao,int valor){
        animacoes[idAnimacao]->SetOpacidade(valor);
    }

     int CGerenciadorAnimacoes::GetOpacidade(int idAnimacao){
        return animacoes[idAnimacao]->GetOpacidade();
    }

     void CGerenciadorAnimacoes::SetColoracao(int idAnimacao,PIG_Cor cor){
        animacoes[idAnimacao]->SetColoracao(cor);
    }

     void CGerenciadorAnimacoes::SetPivo(int idAnimacao,int x,int y){
        animacoes[idAnimacao]->SetPivo(x,y);
    }

     void CGerenciadorAnimacoes::GetPivo(int idAnimacao,int *x,int *y){
        animacoes[idAnimacao]->GetPivo(*x,*y);
    }

     void CGerenciadorAnimacoes::SetFlip(int idAnimacao, PIG_Flip valor){
        animacoes[idAnimacao]->SetFlip(valor);
    }

     PIG_Flip CGerenciadorAnimacoes::GetFlip(int idAnimacao){
        return animacoes[idAnimacao]->GetFlip();
    }

     void CGerenciadorAnimacoes::SetAngulo(int idAnimacao,float valor){
        animacoes[idAnimacao]->SetAngulo(valor);
    }

     float CGerenciadorAnimacoes::GetAngulo(int idAnimacao){
        return animacoes[idAnimacao]->GetAngulo();
    }

     int CGerenciadorAnimacoes::ColisaoAnimacoes(int idAnimacao1,int idAnimacao2){
        return animacoes[idAnimacao1]->Colisao(animacoes[idAnimacao2]);
    }

     int CGerenciadorAnimacoes::ColisaoObjeto(int idAnimacao,CObjeto *obj){
        return animacoes[idAnimacao]->Colisao(obj);
    }

     void CGerenciadorAnimacoes::CGerenciadorAnimacoes::SetDimensoes(int idAnimacao,int altura,int largura){
        animacoes[idAnimacao]->SetDimensoes(altura,largura);
    }

     void CGerenciadorAnimacoes::GetDimensoes(int idAnimacao,int *altura,int *largura){
        animacoes[idAnimacao]->GetDimensoes(*altura,*largura);
    }

     void CGerenciadorAnimacoes::SetValorIntAnimacao(int idAnimacao, int chave, int valor){
        animacoes[idAnimacao]->SetValoresInt(chave,valor);
    }

     void CGerenciadorAnimacoes::SetValorIntAnimacao(int idAnimacao, std::string chave, int valor){
        animacoes[idAnimacao]->SetValoresInt(chave,valor);
    }

     void CGerenciadorAnimacoes::SetValorFloatAnimacao(int idAnimacao, int chave, float valor){
        animacoes[idAnimacao]->SetValoresFloat(chave,valor);
    }

     void CGerenciadorAnimacoes::SetValorFloatAnimacao(int idAnimacao, std::string chave, float valor){
        animacoes[idAnimacao]->SetValoresFloat(chave,valor);
    }

     void CGerenciadorAnimacoes::SetValorStringAnimacao(int idAnimacao, int chave, std::string valor){
        animacoes[idAnimacao]->SetValoresString(chave,valor);
    }

     void CGerenciadorAnimacoes::SetValorStringAnimacao(int idAnimacao, std::string chave, std::string valor){
        animacoes[idAnimacao]->SetValoresString(chave,valor);
    }

     bool CGerenciadorAnimacoes::GetValorIntAnimacao(int idAnimacao, int indice, int *valor){
        return animacoes[idAnimacao]->GetValoresInt(indice,*valor);
    }

     bool CGerenciadorAnimacoes::GetValorFloatAnimacao(int idAnimacao, int indice, float *valor){
        return animacoes[idAnimacao]->GetValoresFloat(indice,*valor);
    }

     bool CGerenciadorAnimacoes::GetValorStringAnimacao(int idAnimacao, int indice, std::string &valor){
        return animacoes[idAnimacao]->GetValoresString(indice,valor);
    }

     bool CGerenciadorAnimacoes::GetValorIntAnimacao(int idAnimacao, std::string indice, int *valor){
        return animacoes[idAnimacao]->GetValoresInt(indice,*valor);
    }

     bool CGerenciadorAnimacoes::GetValorFloatAnimacao(int idAnimacao, std::string indice, float *valor){
        return animacoes[idAnimacao]->GetValoresFloat(indice,*valor);
    }

     bool CGerenciadorAnimacoes::GetValorStringAnimacao(int idAnimacao, std::string indice, std::string &valor){
        return animacoes[idAnimacao]->GetValoresString(indice,valor);
    }

     void CGerenciadorAnimacoes::PausaAnimacao(int idAnimacao){
        animacoes[idAnimacao]->Pausa();
    }

     void CGerenciadorAnimacoes::DespausaAnimacao(int idAnimacao){
        animacoes[idAnimacao]->Despausa();
    }

     void CGerenciadorAnimacoes::SetTempoFrameAnimacao(int idAnimacao, int idModo, int indiceFrame, double tempo){
        animacoes[idAnimacao]->SetTempoFrame(idModo,indiceFrame,tempo);
    }

     void CGerenciadorAnimacoes::SetAudioFrameAnimacao(int idAnimacao, int idModo, int indiceFrame, int idAudio){
        animacoes[idAnimacao]->SetAudioFrame(idModo,indiceFrame,idAudio);
    }

     void CGerenciadorAnimacoes::SetLoopModoAnimacao(int idAnimacao, int idModo, bool loop){
        animacoes[idAnimacao]->SetLoopModo(idModo,loop);
    }

     double CGerenciadorAnimacoes::GetTempoFrameAnimacao(int idAnimacao, int idModo, int indiceFrame){
        return animacoes[idAnimacao]->GetTempoFrame(idModo,indiceFrame);
    }

     bool CGerenciadorAnimacoes::GetLoopModoAnimacao(int idAnimacao, int idModo){
        return animacoes[idAnimacao]->GetLoopModo(idModo);
    }

     int CGerenciadorAnimacoes::GetAudioFrameAnimacao(int idAnimacao, int idModo, int indiceFrame){
        return animacoes[idAnimacao]->GetAudioFrame(idModo,indiceFrame);
    }
