
#ifndef CSOCKETTCP_H
#define CSOCKETTCP_H

#include <string>
#include <SDL2/SDL_net.h>

class CSocketTCP
{
protected:
    int id;
    TCPsocket socket;
    SDLNet_SocketSet socketSet;
    std::string hostRemoto;
    std::string hostLocal;
    int portaRemota;
    int tamPacote;
    long tempoPacoteRecebido;
    long qtdPacotesRecebidos;
    long qtdBytesRecebidos;
    long tempoPacoteEnviado;
    long qtdPacotesEnviados;
    long qtdBytesEnviados;
    bool ativo;
    bool liberaSocketSet;//usado para saber se o socketSet deve ser liberado

    void RegistraBytesRecebidos(int qtdBytes);
    void RegistraBytesEnviados(int qtdBytes);
    void InicializaValoresBasicos(int valorId,int maxBytesPacote);

public:
    CSocketTCP(int id,std::string host,int porta,int maxBytesPacote);
    CSocketTCP(int id,TCPsocket serverSocket,int maxBytesPacote,SDLNet_SocketSet socketSetClientes);
    ~CSocketTCP();
    int GetId();
    bool GetAtivo();
    std::string GetHostRemoto();
    std::string GetHostLocal();
    int GetPortaRemota();
    int GetTamanhoPacote();
    int MudaSet(SDLNet_SocketSet socketSetNovo);
    long GetBytesEnviados();
    long GetBytesRecebidos();
    long GetPacotesEnviados();
    long GetPacotesRecebidos();
    long GetTempoUltimoRecebido();
    long GetTempoUltimoEnviado();
    int RecebeDados(void *buffer);
    int EnviaDados(const void *buffer, int tamanhoBuffer);

};

#endif
