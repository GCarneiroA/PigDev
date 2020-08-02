
#ifndef CFILAPACOTES_H
#define CFILAPACOTES_H

#include <cstdint>
#include <SDL2/SDL.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

class CFilaPacotes
{
public:
    int GetQtdPacotes();
    int GetSize();
    void SetQtdPacotes(int valor);
    void SetSize(int valor);
    int Put(AVPacket *srcPkt);
    int Get(AVPacket *pkt, int block, int &encerrar);
    int PutFlush();
    void Flush();
    CFilaPacotes();
    ~CFilaPacotes();
    bool IgualFlushData(uint8_t *data);
    void LiberaBlock();

private:
    AVPacketList *first, *last;
    int nb_packets, size;
    AVPacket flushPkt;
    SDL_mutex *cs;
    SDL_cond *cv;
};

#endif
