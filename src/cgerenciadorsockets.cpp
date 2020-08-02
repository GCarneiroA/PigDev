
#include "cgerenciadorsockets.h"
#include "cclientetcp.h"
#include "cpoolnumeros.h"
#include "cservidortcp.h"
#include "csocketudp.h"

int CGerenciadorSockets::totalClientes;
CPoolNumeros *CGerenciadorSockets::numClientes;
CClienteTCP *CGerenciadorSockets::clientes[MAX_SOCKETS_CLIENTES_TCP];
int CGerenciadorSockets::totalServidores;
CPoolNumeros *CGerenciadorSockets::numServidores;
CServidorTCP *CGerenciadorSockets::servidores[MAX_SOCKETS_SERVIDORES_TCP];
int CGerenciadorSockets::totalSocketsUDP;
CPoolNumeros *CGerenciadorSockets::numSocketsUDP;
CSocketUDP *CGerenciadorSockets::socketsUDP[MAX_SOCKETS_UDP];


 void CGerenciadorSockets::Inicia(){
    totalClientes = 0;
    for (int i=0;i<MAX_SOCKETS_CLIENTES_TCP;i++)
        clientes[i] = NULL;
    numClientes = new CPoolNumeros(MAX_SOCKETS_CLIENTES_TCP);

    totalServidores = 0;
    for (int i=0;i<MAX_SOCKETS_SERVIDORES_TCP;i++)
        servidores[i] = NULL;
    numServidores = new CPoolNumeros(MAX_SOCKETS_SERVIDORES_TCP);

    totalSocketsUDP = 0;
    for (int i=0;i<MAX_SOCKETS_UDP;i++)
        socketsUDP[i] = NULL;
    numSocketsUDP = new CPoolNumeros(MAX_SOCKETS_UDP);
}

 void CGerenciadorSockets::Encerra(){
    for (int i=0;i<MAX_SOCKETS_CLIENTES_TCP;i++){
        if (clientes[i]) delete clientes[i];
    }
    delete numClientes;

    for (int i=0;i<MAX_SOCKETS_SERVIDORES_TCP;i++){
        if (servidores[i]) delete servidores[i];
    }
    delete numServidores;

    for (int i=0;i<MAX_SOCKETS_UDP;i++){
        if (socketsUDP[i]) delete socketsUDP[i];
    }
    delete numSocketsUDP;
}

 int CGerenciadorSockets::CriaCliente(std::string hostname, int porta, int maxBytesPacote){
    int resp = numClientes->RetiraLivre();
    clientes[resp] = new CClienteTCP(resp,hostname,porta,maxBytesPacote);
    totalClientes++;
    return resp;
}

 int CGerenciadorSockets::CriaServidor(int maxClientes, int porta, int maxBytesPacote){
    int resp = numServidores->RetiraLivre();
    servidores[resp] = new CServidorTCP(resp,maxClientes,porta,maxBytesPacote);
    totalServidores++;
    return resp;
}

 int CGerenciadorSockets::CriaSocketUDP(int porta){
    int resp = numSocketsUDP->RetiraLivre();
    socketsUDP[resp] = new CSocketUDP(resp,porta);
    totalSocketsUDP++;
    return resp;
}

 void CGerenciadorSockets::DestroiCliente(int idSocket){
    numClientes->DevolveUsado(idSocket);
    delete clientes[idSocket];
    totalClientes--;
    clientes[idSocket] = NULL;
}

 void CGerenciadorSockets::DestroiServidor(int idSocket){
    numServidores->DevolveUsado(idSocket);
    delete servidores[idSocket];
    totalServidores--;
    servidores[idSocket] = NULL;
}

 void CGerenciadorSockets::DestroiSocketUDP(int idSocket){
    numSocketsUDP->DevolveUsado(idSocket);
    delete socketsUDP[idSocket];
    totalSocketsUDP--;
    socketsUDP[idSocket] = NULL;
}

 bool CGerenciadorSockets::GetAtivoCliente(int idSocket){
    return clientes[idSocket]->GetAtivo();
}

 bool CGerenciadorSockets::GetAtivoServidor(int idSocket){
    return servidores[idSocket]->GetAtivo();
}

 bool CGerenciadorSockets::GetAtivoSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetAtivo();
}

 long CGerenciadorSockets::GetBytesEnviadosCliente(int idSocket){
    return clientes[idSocket]->GetBytesEnviados();
}

 long CGerenciadorSockets::GetBytesRecebidosCliente(int idSocket){
    return clientes[idSocket]->GetBytesRecebidos();
}

 long CGerenciadorSockets::GetPacotesEnviadosCliente(int idSocket){
    return clientes[idSocket]->GetPacotesEnviados();
}

 long CGerenciadorSockets::GetPacotesRecebidosCliente(int idSocket){
    return clientes[idSocket]->GetPacotesRecebidos();
}

 long CGerenciadorSockets::GetTempoUltimoRecebidoCliente(int idSocket){
    return clientes[idSocket]->GetTempoUltimoRecebido();
}

 long CGerenciadorSockets::GetTempoUltimoEnviadoCliente(int idSocket){
    return clientes[idSocket]->GetTempoUltimoEnviado();
}

 long CGerenciadorSockets::GetBytesEnviadosServidor(int idSocket){
    return servidores[idSocket]->GetBytesEnviados();
}

 long CGerenciadorSockets::GetBytesRecebidosServidor(int idSocket){
    return servidores[idSocket]->GetBytesRecebidos();
}

 long CGerenciadorSockets::GetPacotesEnviadosServidor(int idSocket){
    return servidores[idSocket]->GetPacotesEnviados();
}

 long CGerenciadorSockets::GetPacotesRecebidosServidor(int idSocket){
    return servidores[idSocket]->GetPacotesRecebidos();
}

 long CGerenciadorSockets::GetTempoUltimoRecebidoServidor(int idSocket){
    return servidores[idSocket]->GetTempoUltimoRecebido();
}

 long CGerenciadorSockets::GetTempoUltimoEnviadoServidor(int idSocket){
    return servidores[idSocket]->GetTempoUltimoEnviado();
}

 long CGerenciadorSockets::GetBytesEnviadosSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetBytesEnviados();
}

 long CGerenciadorSockets::GetBytesRecebidosSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetBytesRecebidos();
}

 long CGerenciadorSockets::GetPacotesEnviadosSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetPacotesEnviados();
}

 long CGerenciadorSockets::GetPacotesRecebidosSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetPacotesRecebidos();
}

 long CGerenciadorSockets::GetTempoUltimoRecebidoSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetTempoUltimoRecebido();
}

 long CGerenciadorSockets::GetTempoUltimoEnviadoSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetTempoUltimoEnviado();
}

 int CGerenciadorSockets::GetPortaRemotaCliente(int idSocket){
    return clientes[idSocket]->GetPortaRemota();
}

 int CGerenciadorSockets::GetPortaLocalServidor(int idSocket){
    return servidores[idSocket]->GetPortaLocal();
}

 int CGerenciadorSockets::GetPortaLocalSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetPortaLocal();
}

 std::string CGerenciadorSockets::GetHostRemotoCliente(int idSocket){
    return clientes[idSocket]->GetHostRemoto();
}

 std::string CGerenciadorSockets::GetHostLocalCliente(int idSocket){
    return clientes[idSocket]->GetHostLocal();
}

 std::string CGerenciadorSockets::GetHostLocalServidor(int idSocket){
    return servidores[idSocket]->GetHostLocal();
}

 std::string CGerenciadorSockets::GetHostLocalSocketUDP(int idSocket){
    return socketsUDP[idSocket]->GetHostLocal();
}

 int CGerenciadorSockets::GetTamanhoPacoteCliente(int idSocket){
    return clientes[idSocket]->GetTamanhoPacote();
}

 int CGerenciadorSockets::GetTamanhoPacoteServidor(int idSocket){
    return servidores[idSocket]->GetTamanhoPacote();
}

 int CGerenciadorSockets::GetMaximoConexoesServidor(int idSocket){
    return servidores[idSocket]->GetMaximoConexoes();
}

 int CGerenciadorSockets::GetQuantidadeConexoes(int idSocket){
    return servidores[idSocket]->GetQuantidadeConexoes();
}

 int CGerenciadorSockets::EnviaDadosCliente(int idSocket,void *buffer, int tamanhoBuffer){
    return clientes[idSocket]->EnviaDados(buffer,tamanhoBuffer);
}

 int CGerenciadorSockets::EnviaDadosServidor(int idSocket,int socketSecundario,void *buffer, int tamanhoBuffer){
    return servidores[idSocket]->EnviaDados(buffer,tamanhoBuffer,socketSecundario);
}

 int CGerenciadorSockets::EnviaDadosSocketUDP(int idSocket,void *buffer,int tamanhoBuffer, std::string hostRemoto, int porta){
    return socketsUDP[idSocket]->EnviaDados(buffer,tamanhoBuffer,hostRemoto,porta);
}
