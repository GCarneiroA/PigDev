
#ifndef CGERENCIADORSOCKETS_H
#define CGERENCIADORSOCKETS_H

#include "csockettcp.h"

#include "cservidortcp.h"
#include "csocketudp.h"

#include <string>

class CClienteTCP;
class CPoolNumeros;
class CServidorTCP;
class CSocketUDP;

class CGerenciadorSockets
{
public:
    static void Inicia();
    static void Encerra();
    static int CriaCliente(std::string hostname, int porta, int maxBytesPacote=MAX_MENSAGEM_REDE_TCP);
    static int CriaServidor(int maxClientes, int porta, int maxBytesPacote=MAX_MENSAGEM_REDE_TCP);
    static int CriaSocketUDP(int porta);
    static void DestroiCliente(int idSocket);
    static void DestroiServidor(int idSocket);
    static void DestroiSocketUDP(int idSocket);
    static bool GetAtivoCliente(int idSocket);
    static bool GetAtivoServidor(int idSocket);
    static bool GetAtivoSocketUDP(int idSocket);
    static long GetBytesEnviadosCliente(int idSocket);
    static long GetBytesRecebidosCliente(int idSocket);
    static long GetPacotesEnviadosCliente(int idSocket);
    static long GetPacotesRecebidosCliente(int idSocket);
    static long GetTempoUltimoRecebidoCliente(int idSocket);
    static long GetTempoUltimoEnviadoCliente(int idSocket);
    static long GetBytesEnviadosServidor(int idSocket);
    static long GetBytesRecebidosServidor(int idSocket);
    static long GetPacotesEnviadosServidor(int idSocket);
    static long GetPacotesRecebidosServidor(int idSocket);
    static long GetTempoUltimoRecebidoServidor(int idSocket);
    static long GetTempoUltimoEnviadoServidor(int idSocket);
    static long GetBytesEnviadosSocketUDP(int idSocket);
    static long GetBytesRecebidosSocketUDP(int idSocket);
    static long GetPacotesEnviadosSocketUDP(int idSocket);
    static long GetPacotesRecebidosSocketUDP(int idSocket);
    static long GetTempoUltimoRecebidoSocketUDP(int idSocket);
    static long GetTempoUltimoEnviadoSocketUDP(int idSocket);
    static int GetPortaRemotaCliente(int idSocket);
    static int GetPortaLocalServidor(int idSocket);
    static int GetPortaLocalSocketUDP(int idSocket);
    static std::string GetHostRemotoCliente(int idSocket);
    static std::string GetHostLocalCliente(int idSocket);
    static std::string GetHostLocalServidor(int idSocket);
    static std::string GetHostLocalSocketUDP(int idSocket);
    static int GetTamanhoPacoteCliente(int idSocket);
    static int GetTamanhoPacoteServidor(int idSocket);
    static int GetMaximoConexoesServidor(int idSocket);
    static int GetQuantidadeConexoes(int idSocket);
    static int EnviaDadosCliente(int idSocket,void *buffer, int tamanhoBuffer);
    static int EnviaDadosServidor(int idSocket,int socketSecundario,void *buffer, int tamanhoBuffer);
    static int EnviaDadosSocketUDP(int idSocket,void *buffer,int tamanhoBuffer, std::string hostRemoto, int porta);
private:
    static int totalClientes;
    static CPoolNumeros *numClientes;
    static CClienteTCP *clientes[MAX_SOCKETS_CLIENTES_TCP];
    static int totalServidores;
    static CPoolNumeros *numServidores;
    static CServidorTCP *servidores[MAX_SOCKETS_SERVIDORES_TCP];
    static int totalSocketsUDP;
    static CPoolNumeros *numSocketsUDP;
    static CSocketUDP *socketsUDP[MAX_SOCKETS_UDP];
};

#endif
