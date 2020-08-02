
#ifndef CSOCKETUDP_H
#define CSOCKETUDP_H

#include <string>

#include "tipos_pig.h"

#include <SDL2/SDL_net.h>

class CSocketUDP
{
private:
    int portaLocal;
    char hostLocal[TAMANHO_MAXIMO_HOSTNAME];
    int id;
    int ativo;
    long tempoPacoteRecebido;
    long qtdPacotesRecebidos;
    long qtdBytesRecebidos;
    long tempoPacoteEnviado;
    long qtdPacotesEnviados;
    long qtdBytesEnviados;
    UDPsocket socket;
    UDPpacket *pacoteEnvio, *pacoteRecebimento;
    SDL_Thread *thread;

    void CriaEventoMensagem(PIG_TipoMensagemRede tipoMensagem, UDPpacket *pacoteRecebido);

public:
    CSocketUDP(int idSocket,int porta);
    ~CSocketUDP();
    bool EnviaDados(const void *buffer, int tamanhoBuffer, std::string host, int porta);
    int GetId();
    bool GetAtivo();
    int GetPortaLocal();
    std::string GetHostLocal();
    long GetBytesEnviados();
    long GetBytesRecebidos();
    long GetPacotesEnviados();
    long GetPacotesRecebidos();
    long GetTempoUltimoRecebido();
    long GetTempoUltimoEnviado();
    static int thread_code(void *data);
};

#endif
