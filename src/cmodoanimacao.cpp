
#include "cmodoanimacao.h"

    //construtor do modo
CModoAnimacao::CModoAnimacao(bool emLoop){
        frameAtual = 0;
        loop = emLoop;
        encerrou = false;
    }

    //destrutor
CModoAnimacao::~CModoAnimacao(){
        estagios.clear();
    }

    //cria um novo est�gio (frame)
    int CModoAnimacao::InsereEstagio(int idFrame, double tempo, int idAudio){
        EstagioAnimacao estagio={idFrame,tempo,idAudio};
        estagios.push_back(estagio);
        return estagios.size()-1;
    }

    //define o tempo de um est�gio (frame) j� criado
    void CModoAnimacao::SetTempo(int idEstagio, double novoTempo){
        estagios[idEstagio].tempo = novoTempo;
    }

    //define o audio de um est�gio (frame) j� criado
    void CModoAnimacao::SetAudio(int idEstagio, int idAudio){
        estagios[idEstagio].audio = idAudio;
    }

    //define se o modo estra�em loop ou n�o
    void CModoAnimacao::SetLoop(bool emLoop){
        loop = emLoop;
    }

    //retorna se o modo est� em loop ou n�o
    bool CModoAnimacao::GetLoop(){
        return loop;
    }

    //muda arbitrariamente o �ndice (posi��o da sequ�ncia de frames) do frame a ser exibido
    void CModoAnimacao::SetIndiceFrameAtual(int indice){
        if (indice<frameAtual)
            encerrou = false;
        frameAtual = indice;
    }

    //retorna o �ndice (posi��od o vetor) do frame atual
    int CModoAnimacao::GetIndiceFrameAtual(){
        return frameAtual;
    }

    //retorna o n�mero do frame atual
    int CModoAnimacao::GetFrameAtual(){
        return estagios[frameAtual].frame;
    }

    //retorna o audio do frame atual
    int CModoAnimacao::GetAudioAtual(){
        return estagios[frameAtual].audio;
    }

    //retorna o tempo de exibi��o do frame atual
    double CModoAnimacao::GetTempoAtual(){
        return estagios[frameAtual].tempo;
    }

    //retorna o audio de um frame j� criado (pelo seu �ndice no vetor)
    int CModoAnimacao::GetAudioFrame(int indiceFrame){
        return estagios[indiceFrame].audio;
    }

    //retorna o tempo de um frame j� criado (pelo seu �ndice no vetor)
    double CModoAnimacao::GetTempoFrame(int indiceFrame){
        return estagios[indiceFrame].tempo;
    }

    //teste se j� passou o tempo necess�rio para mudar de frame
    int CModoAnimacao::TestaTempo(double tempoDecorrido){
        encerrou = false;
        if (estagios.size()==0) return 0;//nao foi criado nenhum estagio nesse modo
        int frameAntigo = frameAtual;//armazena o valor do frameAtual
        if (tempoDecorrido>=estagios[frameAtual].tempo){
            if (frameAtual < estagios.size()-1){//se ainda nao chegou no �ltimo est�gio
                frameAtual++;
            }else{//chegou no �ltimo est�gio
                if (loop)
                    frameAtual = 0;//se est� em loop, volta ao primeiro frame
                else encerrou=true;
            }
        }
        return frameAtual!=frameAntigo;//retorna se alterou o frameAtual
    }

    //retorna se o modo j� exibiu todos os frames (apenas se n�o estiver em loop)
    bool CModoAnimacao::GetEncerrou(){
        return encerrou;
    }
