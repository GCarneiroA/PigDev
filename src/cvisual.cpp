
#include "cvisual.h"
#include "cpigerroarquivo.h"
#include "cassetloader.h"
#include "cgerenciadorjanelas.h"
#include "coffscreenrenderer.h"

    void CVisual::CriaTextura(int retiraFundo, PIG_Cor *corFundo){
        if (retiraFundo){
            Uint8 red, green, blue, alpha;
            //printf("vou retirar cor de fundo\n");
            if (corFundo!=NULL){
                red = corFundo->r;
                green = corFundo->g;
                blue = corFundo->b;
                alpha = corFundo->a;
            }else{
                Uint32 *pixel = (Uint32*)bitmap->pixels;
                SDL_GetRGBA(*pixel,bitmap->format,&red,&green,&blue,&alpha);
            }

            SDL_SetColorKey( bitmap, SDL_TRUE, SDL_MapRGBA(bitmap->format, red, green, blue,alpha) );
        }else SDL_SetColorKey( bitmap, SDL_FALSE, 0);

        if (text) SDL_DestroyTexture(text);
        text = SDL_CreateTextureFromSurface(renderer, bitmap);
    }

    void CVisual::CarregaImagem(std::string nomeArq){
        nomeArquivo = nomeArq;

        #ifdef SHARE_BITMAP
        bitmap = CAssetLoader::LoadImage(nomeArquivo);
        #else
        bitmap = IMG_Load(nomeArquivo.c_str());
        #endif
        if (!bitmap) throw CPigErroArquivo(nomeArquivo);
    }

    void CVisual::IniciaBase(int altura,int largura,int janela){
        IniciaCor();
        IniciaJanela(janela);
        IniciaDimensoes(altura,largura);
        IniciaOrientacao();
    }

    CVisual::CVisual(int altura,int largura,std::string nomeArq,int janela){
        nomeArquivo = nomeArq;
        IniciaBase(altura,largura,janela);
    }

    CVisual::CVisual(std::string nomeArq,int retiraFundo,PIG_Cor *corFundo,int janela){
        nomeArquivo = nomeArq;

        CarregaImagem(nomeArq);

        IniciaBase(bitmap->h,bitmap->w,janela);

        CriaTextura(retiraFundo,corFundo);
    }

    CVisual::CVisual(COffscreenRenderer *offRender, int retiraFundo,PIG_Cor *corFundo,int janela){
        nomeArquivo = "";

        SDL_Surface *surface = offRender->GetSurface();

        bitmap = SDL_CreateRGBSurfaceWithFormatFrom(surface->pixels,surface->w,surface->h,offRender->GetDepth(),surface->pitch,surface->format->format);

        IniciaBase(bitmap->h,bitmap->w,janela);
        CriaTextura(retiraFundo,corFundo);
    }

    CVisual::CVisual(CVisual *visualBase,int retiraFundo,PIG_Cor *corFundo,int janela){
        nomeArquivo = visualBase->nomeArquivo;

        #ifdef SHARE_BITMAP
        bitmap = CAssetLoader::LoadImage(visualBase->nomeArquivo);
        #else
        bitmap = IMG_Load(visualBase->nomeImagem);
        #endif

        IniciaBase(bitmap->h,bitmap->w,janela);
        CriaTextura(retiraFundo,corFundo);
    }

    CVisual::~CVisual(){
        if (text) SDL_DestroyTexture(text);

        if (nomeArquivo == ""){
            if (bitmap) SDL_FreeSurface(bitmap);
        }else{
            #ifdef SHARE_BITMAP
            CAssetLoader::FreeImage(nomeArquivo);
            #else
            if (bitmap) SDL_FreeSurface(bitmap);
            #endif
        }
    }

    void CVisual::IniciaCor(){
        coloracao = BRANCO;
        opacidade = 255; //totalmente opaco
        text = NULL;
    }

    void CVisual::IniciaJanela(int janela){
        idJanela = janela;
        altJanela = CGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
        renderer = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
    }

    void CVisual::IniciaDimensoes(int altura,int largura){
        altOriginal = alt = altura;
        largOriginal = larg = largura;
    }

    void CVisual::IniciaOrientacao(){
        x = y = 0;
        angulo = 0;
        pivoRelativo.x = 0;
        pivoRelativo.y = alt;

        dest.x = x;
        dest.y = altJanela-y-alt;
        dest.h = alt;
        dest.w = larg;

        frame.x = frame.y = 0;
        frame.h = alt;
        frame.w = larg;

        flip = SDL_FLIP_NONE;
    }

    int CVisual::GetIdJanela(){
        return idJanela;
    }

    void CVisual::DefineFrame(SDL_Rect r){
        frame = r;
    }

    void CVisual::GetXY(int &x,int &y){
        x = this->x;
        y = this->y;
    }

    void CVisual::SetColoracao(PIG_Cor cor){
        coloracao = cor;
        SDL_SetTextureColorMod(text,cor.r,cor.g,cor.b);
    }

    void CVisual::SetAngulo(float a){
        angulo = a;
    }

    float CVisual::GetAngulo(){
        return angulo;
    }

    void CVisual::SetFlip(PIG_Flip valor){
        flip = valor;
    }

    PIG_Flip CVisual::GetFlip(){
        return flip;
    }

    void CVisual::SetPivo(int px,int py){
        pivoRelativo.x = px;
        pivoRelativo.y = dest.h-py;
    }

    void CVisual::SetPivo(float px,float py){
        pivoRelativo.x = px*dest.w;
        pivoRelativo.y = dest.h-py*dest.h;
    }

    void CVisual::GetPivo(int &px,int &py){
        px = pivoRelativo.x;
        py = pivoRelativo.y;
    }

    void CVisual::Move(int nx,int ny){
        x = nx;
        y = ny;
        dest.x = x;
        dest.y = altJanela-alt-y;
    }

    void CVisual::Desloca(int dx, int dy){
        x += dx;
        y += dy;
        dest.x = x;
        dest.y = altJanela-alt-y;
    }

    void CVisual::SetDimensoes(int altura,int largura){
        dest.h = alt = altura;
        dest.w = larg = largura;
        dest.x = x;
        dest.y = altJanela-y-alt;

        pivoRelativo.y = alt;//necess�rio porque o poiv� relativo � usado com eixo Y invertido (para baixo)
    }

    void CVisual::GetDimensoes(int &altura, int &largura){
        altura = alt;
        largura = larg;
    }

    void CVisual::GetDimensoesOriginais(int &altura,int &largura){
        altura = altOriginal;
        largura = largOriginal;
    }

    void CVisual::SetOpacidade(int valor){
        opacidade = valor;
        SDL_SetTextureAlphaMod(text,valor);
    }

    int CVisual::GetOpacidade(){
        return opacidade;
    }

    std::string CVisual::GetNomeArquivo(){
        return nomeArquivo;
    }
