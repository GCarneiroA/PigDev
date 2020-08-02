
#ifndef CSERVIDORTCP_H
#define CSERVIDORTCP_H

#include "tipos_pig.h"
#include "csockettcp.h"

class CPoolNumeros;

class CServidorTCP : public CSocketTCP
{
public:
    CServidorTCP(int idSocket, int maximoConexoes, int porta, int maxBytesPacote);
    ~CServidorTCP();
    int GetPortaLocal();
    int GetMaximoConexoes();
    int GetQuantidadeConexoes();
    int EnviaDados(const void *buffer,int tamanhoBuffer,int indiceSlot);
    static int accept_code(void *data);
    static int receive_code(void *data);

private:
    SDLNet_SocketSet clienteSet;
    int maxConexoes;
    int qtdConexoes;
    CSocketTCP **clientesTCP;
    int portaLocal;
    SDL_Thread *threadAccept,*threadReceive;
    CPoolNumeros *pool;

    void CriaEventoMensagem(PIG_TipoMensagemRede tipoMensagem, const void *buffer, int tamanhoDados, int indiceSlot);
    void RegistraBytesRecebidos(int qtdBytes);
    void RegistraBytesEnviados(int qtdBytes);
    void InicializaValoresBasicos(int valorId,int maxBytesPacote);

};

#endif
