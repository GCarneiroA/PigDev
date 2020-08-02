
#include "csockettcp.h"

#include <time.h>

CSocketTCP::CSocketTCP(int id,std::string host,int porta,int maxBytesPacote){
    IPaddress ipAux;

    SDLNet_ResolveHost(&ipAux,getenv("COMPUTERNAME"),porta);
    Uint8 *part = (Uint8*)&(ipAux.host);
    hostLocal = std::to_string((int)part[0])+"." + std::to_string((int)part[1])+"."+std::to_string((int)part[2])+"."+std::to_string((int)part[3]);
    //%d.%d.%d.%d",(int)part[0],(int)part[1],(int)part[2],(int)part[3]);

    InicializaValoresBasicos(id,maxBytesPacote);

    portaRemota = porta;
    hostRemoto = host;

    const char *strHost = host==""?NULL:host.c_str();
    if (SDLNet_ResolveHost(&ipAux,strHost,porta)==-1){
         printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
    }

    socket = SDLNet_TCP_Open(&ipAux);
    ativo = socket!=NULL;
    liberaSocketSet = true;
    if(!ativo){
        printf("Erro ao criar socket regular: %s\n", SDLNet_GetError());
    }
}

CSocketTCP::CSocketTCP(int id,TCPsocket serverSocket,int maxBytesPacote,SDLNet_SocketSet socketSetClientes){//TCPsocket server,int maxBytesPacote,){
    IPaddress ipAux;

    InicializaValoresBasicos(id,maxBytesPacote);

    socket = SDLNet_TCP_Accept(serverSocket);
    ativo = socket!=NULL;
    if(ativo){
        ipAux = *(SDLNet_TCP_GetPeerAddress(socket));
        hostRemoto.assign(SDLNet_ResolveIP(&ipAux));
        portaRemota = ipAux.port;
        socketSet = socketSetClientes;
        SDLNet_TCP_AddSocket(socketSet,socket);
        liberaSocketSet = false;
    }else{
        printf("Erro ao criar socket de aceitacao: %s\n", SDLNet_GetError());
    }
}

CSocketTCP::~CSocketTCP(){
    if (socketSet){
        SDLNet_TCP_DelSocket(socketSet,socket);
        if (liberaSocketSet)
            SDLNet_FreeSocketSet(socketSet);
    }

    if (socket)
        SDLNet_TCP_Close(socket);
}

int CSocketTCP::GetId(){
    return id;
}

bool CSocketTCP::GetAtivo(){
    return ativo;
}

std::string CSocketTCP::GetHostRemoto(){
    return hostRemoto;
}

std::string CSocketTCP::GetHostLocal(){
    return hostLocal;
}

int CSocketTCP::GetPortaRemota(){
    return portaRemota;
}

int CSocketTCP::GetTamanhoPacote(){
    return tamPacote;
}

int CSocketTCP::MudaSet(SDLNet_SocketSet socketSetNovo){
    if (!ativo) return -1;
    if (socketSet){
        int status = SDLNet_TCP_DelSocket(socketSet,socket);
        if (status==-1) return -1;
    }
    socketSet = socketSetNovo;
    return SDLNet_TCP_AddSocket(socketSet,socket);
}

long CSocketTCP::GetBytesEnviados(){
    return qtdBytesEnviados;
}

long CSocketTCP::GetBytesRecebidos(){
    return qtdBytesRecebidos;
}

long CSocketTCP::GetPacotesEnviados(){
    return qtdPacotesEnviados;
}

long CSocketTCP::GetPacotesRecebidos(){
    return qtdPacotesRecebidos;
}

long CSocketTCP::GetTempoUltimoRecebido(){
    return tempoPacoteRecebido;
}

long CSocketTCP::GetTempoUltimoEnviado(){
    return tempoPacoteEnviado;
}

int CSocketTCP::RecebeDados(void *buffer){
    //printf("passoA\n");
    if (!ativo) return -1;
    //printf("passoB\n");
    if (!SDLNet_SocketReady(socket)) return -1;
    //printf("passoC\n");
    int bytes = SDLNet_TCP_Recv(socket,buffer,tamPacote);
    //printf("passoD\n");
    if (bytes<0){
        printf("Erro de recebimento de pacote ou desconexao: %s\n", SDLNet_GetError());
        return -2;
    }
    RegistraBytesRecebidos(bytes);
    return bytes;
}

int CSocketTCP::EnviaDados(const void *buffer, int tamanhoBuffer){
    if (!ativo) return -1;
    //int tamTotal = tamanhoBuffer; // soma-se 1 por causa do caracter terminal NULL (\0) da string
    int bytes = SDLNet_TCP_Send(socket,buffer,tamanhoBuffer);
    if (bytes < tamanhoBuffer) {
        printf("Erro de envio de pacote: %s\n", SDLNet_GetError());
        return -1;
    }
    RegistraBytesEnviados(bytes);
    return bytes;
}

void CSocketTCP::RegistraBytesRecebidos(int qtdBytes){
    if (!ativo) return;
    tempoPacoteRecebido = clock();
    qtdPacotesRecebidos++;
    qtdBytesRecebidos += qtdBytes;
}

void CSocketTCP::RegistraBytesEnviados(int qtdBytes){
    if (!ativo) return;
    tempoPacoteEnviado = clock();
    qtdPacotesEnviados++;
    qtdBytesEnviados += qtdBytes;
}

void CSocketTCP::InicializaValoresBasicos(int valorId,int maxBytesPacote){
    qtdPacotesRecebidos = 0;
    qtdBytesRecebidos = 0;
    qtdPacotesEnviados = 0;
    qtdBytesEnviados = 0;
    tempoPacoteRecebido = -1;
    tempoPacoteEnviado = -1;
    tamPacote = maxBytesPacote;
    socketSet = NULL;
    id = valorId;
}
