
#include "cmapacaracteres.h"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "cgerenciadorjanelas.h"
#include "cassetloader.h"

#include "cpigerroindice.h"
#include "cpigerroarquivo.h"

#include "pigfuncoesbasicas.h"

#include <vector>

typedef CMapaCaracteres* MapaCaracteres;
std::string CMapaCaracteres::PigDelimitadores = " \n";


CMapaCaracteres::CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, char *nomeFundo,int outline,PIG_Cor corOutline, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        SDL_Surface *fundo = IMG_Load(nomeFundo);//carrega a imagem de fundo
        SDL_SetSurfaceBlendMode(fundo,SDL_BLENDMODE_MOD);
        CriaLetrasSurface(estilo, outline, corOutline, fundo);
        SDL_FreeSurface(fundo);
    }

CMapaCaracteres::CMapaCaracteres(char *nomeFonte,int tamanhoFonte,int estilo, PIG_Cor corFonte,int outline,PIG_Cor corOutline, int idJanela){
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, estilo);

        CriaLetrasSurface(estilo, outline, corOutline, NULL, corFonte);

        SDL_SetRenderTarget(render, NULL);
    }

CMapaCaracteres::~CMapaCaracteres(){
        TTF_CloseFont(font);
        for (int i=0;i<PIG_TOTALESTILOS;i++){
            if (glyphsT[i]){
                free(alturaExtra[i]);
                free(larguraLetra[i]);
                for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
                    SDL_DestroyTexture(glyphsT[i][j-PRIMEIRO_CAR]);
                }
                free(glyphsT[i]);
            }
        }
        free(glyphsT);
        free(larguraLetra);
        free(alturaExtra);
    }


//cria o conjunto de glifos das letras com as caracter�sticas fornecidas
    void CMapaCaracteres::CriaLetrasSurface(PIG_Estilo estilo, int nivelOutline, PIG_Cor corOutline, SDL_Surface *fundo,  PIG_Cor corFonte){
        TTF_SetFontStyle(font,estilo);

        glyphsT[estilo] = (SDL_Texture**) malloc(sizeof(SDL_Texture*)*(ULTIMO_CAR-PRIMEIRO_CAR));
        larguraLetra[estilo] = (int*)malloc(sizeof(int*)*(ULTIMO_CAR-PRIMEIRO_CAR));
        alturaExtra[estilo] = (int*)malloc(sizeof(int*)*(ULTIMO_CAR-PRIMEIRO_CAR));

        for (Uint16 letra=PRIMEIRO_CAR;letra<ULTIMO_CAR;letra++){
            SDL_Surface *surf = TTF_RenderGlyph_Blended(font,letra,corFonte);//superficie gerada com a forna da letra simples

            if (fundo){
                SDL_BlitScaled(fundo,NULL,surf,NULL);
            }

            larguraLetra[estilo][letra-PRIMEIRO_CAR] = surf->w;//largura da letra com o estilo espec�fico
            alturaExtra[estilo][letra-PRIMEIRO_CAR] = surf->h-tamFonte;//qtd de pixels a mais na altura, para letras mai�sculas acentudadas como �, �, �...

            if (nivelOutline>0){//faz o outline da letra, se houver
                TTF_SetFontOutline(font,nivelOutline);
                SDL_Surface *out = TTF_RenderGlyph_Blended(font,letra,corOutline);
                SDL_BlitSurface(out,NULL,surf,NULL);
                SDL_FreeSurface(out);
                TTF_SetFontOutline(font,0);
            }

            glyphsT[estilo][letra-PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(render,surf);

            SDL_FreeSurface(surf);
        }

    }

    //inicia os atributos da classe
    void CMapaCaracteres::IniciaBase(char *nomeFonte,int tamanhoFonte,int idJanela,PIG_Estilo estilo){
        nome.assign(nomeFonte);
        tamFonte = tamanhoFonte;
        janela = idJanela;
        estiloFixo = estilo;

        render = CGerenciadorJanelas::GetJanela(idJanela)->GetRenderer();
        font = TTF_OpenFont( nome.c_str(), tamanhoFonte );
        fontDescent = TTF_FontDescent(font);
        if (font==NULL)
            printf("Erro: arquivo de fonte (%s) nao localizado\n",nomeFonte);

        alturaExtra = (int**)malloc(sizeof(int)*(PIG_TOTALESTILOS));
        larguraLetra = (int**)malloc(sizeof(int)*(PIG_TOTALESTILOS));
        glyphsT = (SDL_Texture***) malloc(sizeof(SDL_Texture**)*(PIG_TOTALESTILOS));
        for (int i=0;i<PIG_TOTALESTILOS;i++){
            alturaExtra[i] = NULL;
            larguraLetra[i] = NULL;
            glyphsT[i] = NULL;
        }
    }

    CMapaCaracteres::CMapaCaracteres(){}


void CMapaCaracteres::SubstituiGlyph(std::string nomeArq,uint16_t glyph, int largNova, int x, int y, int alt, int larg){
        glyph = glyph%256;
        if (glyph<PRIMEIRO_CAR||glyph>=ULTIMO_CAR) throw CPigErroIndice(glyph,"caracter");//se o indice do glyph antigo n�o existe

        int h;
        SDL_Surface *surfExtra;

        #ifdef SHARE_BITMAP
        surfExtra = CAssetLoader::LoadImage(nomeArq);
        #else
        surfExtra = IMG_Load(nomeArq.c_str()); //tenta ler o arquivo de imagem indicado
        #endif // SHARE_BITMAP

        if (surfExtra==NULL) throw CPigErroArquivo(nomeArq); //se n�o for poss�vel lan�a um erro

        SDL_Rect r = {x,y,larg,alt};//pega somente a �rea do novo glyph

        for (int estilo=0;estilo<PIG_TOTALESTILOS;estilo++){
            if (estiloFixo>=0&&estilo!=estiloFixo) continue;

            SDL_QueryTexture(glyphsT[estilo][glyph-PRIMEIRO_CAR],NULL,NULL,NULL,&h); //pega a altura do caracter que ser� substitu�do
            SDL_Surface *surfAux = SDL_CreateRGBSurfaceWithFormat(0,largNova,h,32,SDL_PIXELFORMAT_RGBA32);//cria uma superf�cie com o tamanho adequado

            SDL_BlitScaled(surfExtra,&r,surfAux,NULL);//copia somente a �rea desejada para uma superf�cie auxiliar
            SDL_DestroyTexture(glyphsT[estilo][glyph-PRIMEIRO_CAR]);//libera a mem�ria do glyph antigo
            larguraLetra[estilo][glyph-PRIMEIRO_CAR] = largNova;//atualiza a largura do glyph novo (valor do par�metro)


            glyphsT[estilo][glyph-PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(render,surfAux); //cria o gylph novo
            SDL_FreeSurface(surfAux);
        }
    }

    int CMapaCaracteres::GetFonteDescent(){
        return -fontDescent;//o valor armazenada fica negativo; a resposta � dada com valor positivo
    }

    int CMapaCaracteres::GetFonteAscent(){
        return TTF_FontAscent(font); //quantidade base de pixels acima da linha base da letra (n�o inclui acento de vogais mai�sculas)
    }

    PIG_Metricas_Fonte CMapaCaracteres::GetMetricasLetra(Uint16 letra, int estilo){
        PIG_Metricas_Fonte metrica;
        int xMin,xMax,yMin,yMax,adv;
        if(estiloFixo>=0)
            estilo = estiloFixo;

        TTF_SetFontStyle(font,estilo);
        letra = letra%256;
        TTF_GlyphMetrics(font,letra,&xMin,&xMax,&yMin,&yMax,&adv);

        metrica.descent = -yMin;
        metrica.ascent = yMax;
        metrica.altura = yMax-yMin;
        metrica.recuo = xMin;
        metrica.avanco = xMax;
        metrica.largura = xMax-xMin;
        return metrica;
    }

    int CMapaCaracteres::GetTamanhoBaseFonte(){
        return tamFonte;
    }

    int CMapaCaracteres::GetLineSkip(){
        return TTF_FontLineSkip(font);
    }

    int CMapaCaracteres::GetLarguraLetra(Uint16 letra, int estilo){
        Uint16 aux = letra;
        aux = aux % 256;
        if(estiloFixo>=0)
            estilo = estiloFixo;
        return larguraLetra[estilo][aux-PRIMEIRO_CAR];
    }

    std::vector<std::string> CMapaCaracteres::ExtraiLinhas(std::string texto, int largMax, std::string delim){
        std::vector<std::string> resp;
        if (texto=="") return resp;

        std::vector<std::string> palavras = PIGSeparaPalavras(texto,delim);
        std::string linhaAtual = "";   //linha atual (que est� sendo montada) cont�m pelo menos a primeira palavra
        int tamanhoAtual = 0;

        for (std::string palavra : palavras){
            int largPalavra = GetLarguraPixelsString(palavra);

            if (palavra[0]=='\n'){//se existe uma quebra de linha for�ada
                resp.push_back(linhaAtual);
                linhaAtual = "";
                tamanhoAtual = 0;
            }

            if (tamanhoAtual + largPalavra > largMax && linhaAtual!=""){//a palavra estouraria a largura m�xima se fosse agregada                if (ttttt==0){
                resp.push_back(linhaAtual); //coloca a linha que est� montada no vetor de linhas
                linhaAtual = palavra; //a palavra que estouraria o limite come�a a pr�xima linha
                tamanhoAtual = largPalavra;
            }else{//n�o estourou o limite
                linhaAtual += palavra;
                tamanhoAtual += largPalavra;
            }
        }

        if (linhaAtual != ""){
            resp.push_back(linhaAtual); //pega a linha que sobrou do processamento (�ltima linha que n�o foi quebrada)
        }

        palavras.clear();
        return resp;
    }

    int CMapaCaracteres::GetLarguraPixelsString(std::string texto){
        int resp=0;
        Uint16 aux;

        for (int i=0;i<texto.size();i++){
            aux = texto[i];
            aux = aux % 256;
            if(texto[i] != '\n')
                resp += larguraLetra[estiloFixo][aux-PRIMEIRO_CAR];
        }

        return resp;
    }

    void CMapaCaracteres::Escreve(std::string texto,int x,int y,PIG_PosTexto pos,float ang){
        if (texto=="") return;
        int larguraPixels = GetLarguraPixelsString(texto);
        int delta=0;
        switch(pos){
        case CPIG_TEXTO_ESQUERDA:
            break;
        case CPIG_TEXTO_DIREITA:
            x -= larguraPixels; delta = larguraPixels;break;
        case CPIG_TEXTO_CENTRO:
            x -= larguraPixels/2; delta = larguraPixels/2;break;
        }

        SDL_Rect rectDestino;
        rectDestino.x = x;

        int altJanela = CGerenciadorJanelas::GetJanela(janela)->GetAltura();
        SDL_Point ponto = {delta,tamFonte};
        Uint16 aux;

        for (int i=0;i<texto.size();i++){
            aux = texto[i];
            aux = aux % 256;//UTF16 string, retirando s� o byte que interessa
            if (aux-PRIMEIRO_CAR<0) continue;
            //printf("aux: %d  %d",aux,aux-PRIMEIRO_CAR);

            rectDestino.w = larguraLetra[estiloFixo][aux-PRIMEIRO_CAR];
            rectDestino.h = tamFonte+alturaExtra[estiloFixo][aux-PRIMEIRO_CAR];
            rectDestino.y = altJanela-y-rectDestino.h;

            SDL_RenderCopyEx(render,glyphsT[estiloFixo][aux-PRIMEIRO_CAR],NULL,&rectDestino,-ang,&ponto,FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }

    }

    void CMapaCaracteres::EscreveLonga(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,PIG_PosTexto pos,float angulo){
        if (texto=="") return;
        std::vector<std::string> linhas = ExtraiLinhas(texto,largMax);
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            Escreve(linhas[k],x,yTotal,pos,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    SDL_Surface *CMapaCaracteres::GetGlyph(Uint16 *emoji, PIG_Cor cor){
        return TTF_RenderUNICODE_Blended(font,emoji,cor);
    }
