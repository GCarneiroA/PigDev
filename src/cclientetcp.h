
#ifndef CCLIENTTCP_H
#define CCLIENTTCP_H

#include <string>
#include <SDL2/SDL_thread.h>

#include "tipos_pig.h"
#include "csockettcp.h"

class CClienteTCP : public CSocketTCP
{
public:
    CClienteTCP(int idSocket,std::string host, int porta, int maxBytesPacote);
    ~CClienteTCP();
    static int thread_code(void *data);

private:
    SDL_Thread *thread;
    void CriaEventoMensagem(PIG_TipoMensagemRede tipoMensagem, const void *buffer, int tamanhoDados);
};

#endif
