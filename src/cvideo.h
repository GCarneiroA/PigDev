
#ifndef CVIDEO_H
#define CVIDEO_H

#define __STDC_CONSTANT_MACROS

#ifdef _MSC_VER
    #define ALIGN_16(T, F) __declspec(align(16)) T F;
#else
    #define ALIGN_16(T, F) T F __attribute__((aligned(16)));
#endif
/*
#ifdef __cplusplus
    extern "C"{
#endif
*/
extern "C" {
    #include <libavfilter/avfilter.h>
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavdevice/avdevice.h>
    #include <libavutil/imgutils.h>
    #include <libavutil/avstring.h>
    #include <libavutil/time.h>

    #include <libswresample/swresample.h>
    #include <libswscale/swscale.h>
}

#include <SDL2/SDL_image.h>
#include "cjanela.h"

#define SDL_MAIN_HANDLED
/*
#ifdef __cplusplus
}
#endif
*/
#define MAX_QUEUE_SIZE                  (15 * 1024 * 1024)
#define VIDEO_PICTURE_QUEUE_SIZE        (1)
#define SDL_AUDIO_BUFFER_SIZE           1024
#define AVCODEC_MAX_AUDIO_FRAME_SIZE    192000
#define AV_SYNC_THRESHOLD               0.01
#define AV_NOSYNC_THRESHOLD             10.0

typedef struct _VideoPicture{
    SDL_Texture *texture;
    int width, height;
    int allocated;
    double pts;
} VideoPicture;

typedef struct _VideoState{
    ALIGN_16(uint8_t, audioBuf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2])
    ALIGN_16(uint8_t, audioConvertedData[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2])
    ALIGN_16(AVPacket, audioPkt)
    ALIGN_16(AVPacket, videoPkt)
    AVFormatContext *pFormatCtx;
    AVCodecContext *audioCtx;
    AVCodecContext *videoCtx;
    struct SwrContext *pSwrCtx;
    struct SwsContext *pSwsCtx;
    int videoStream, audioStream;
    AVStream *audioSt;

    unsigned int audioBufSize, audioBufIndex;
    int hasAudioFrames;
    AVFrame *pAudioFrame;
    AVFrame *pFrameRGB;
    uint8_t *pFrameBuffer;

    int seek_req;
    int seek_flags;
    int64_t seek_pos;

    AVStream *videoSt;

    VideoPicture pictq[VIDEO_PICTURE_QUEUE_SIZE];
    int pictqSize, pictqRindex, pictqWindex;
    SDL_mutex *pictqCs;
    SDL_cond *pictqCv;

    double video_current_pts;
    int64_t video_current_pts_time;

    double videoClock, audioClock, lastFramePts, lastFrameDelay, frameTimer;
} VideoState;

#include "cvisual.h"

class CFilaPacotes;
class CJanela;
class CTimer;

class CVideo : public CVisual
{
    int audioDeviceId;
    double volume;
    VideoState *is;
    SDL_Thread *hParseThread;
    SDL_Thread *hVideoThread;
    int quit;
    bool janelaToda;
    PIG_StatusVideo estado;
    int64_t pausa;
    bool decodeEncerrado;
    double tempoFrame;
    CJanela *janelaAtual;
    CTimer *timerProx;
    CFilaPacotes *filaAudio, *filaVideo;
    SDL_mutex *mutexTex;

    double get_video_clock();
    static int DecodeThread(void* pUserData);
    double GetAudioClock();
    int QueuePicture(AVFrame *frame, double pts);
    double SyncVideo(AVFrame *frame, double pts);
    static int VideoThread(void *pUserData);
    void VideoRefreshTimer();
    void DisplayVideo();
    void AllocPicture();
    int DecodeAudioFrame(double *ptsPtr);
    static void AudioCallback(void *userdata, uint8_t *stream, int len);
    static int DecodeInterruptCallback(void *userData);
    int StreamVideoComponentOpen();
    int StreamAudioComponentOpen();
    int CriaVideoState();
    void DestroiStream(AVStream *stream);
    void DestroiVideoState();

public:
    CVideo(std::string nomeArq,int idJanela=0);
    ~CVideo();
    void SetSeek(double incremento);
    void Play();
    void Stop();
    void Pause();
    void Resume();
    int Desenha();
    void SetVolume(double valor);
    double GetVolume();
    double GetTempoAtual();
    std::string GetTempoAtualString();
    double GetTempoTotal();
    std::string GetTempoTotalString();
    double GetTempoFrame();
    double GetFPS();

    /*
    void SetAngulo(float a);
    double GetAngulo();
    void SetFlip(PIG_Flip valor);
    PIG_Flip GetFlip();
    void SetPivo(int px,int py);
    void SetPivo(float px,float py);
    void GetPivo(int &px,int &py);
    */

    void Move(int nx,int ny);
    void SetDimensoes(int altura,int largura);
    void OcupaJanelaInteira();
    void UsaResolucaoOriginal();

};

#endif
