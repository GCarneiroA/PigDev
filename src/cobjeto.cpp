
#include "cobjeto.h"

#include "coffscreenrenderer.h"


    CObjeto::CObjeto(std::string nomeArquivo, PIG_Cor *corFundo, int retiraFundo, int janela)
        : CVisual(nomeArquivo, retiraFundo, corFundo, janela)
    {
        ExtraiPixels();
    }

    CObjeto::CObjeto(COffscreenRenderer *offRender, PIG_Cor *corFundo, int retiraFundo, int janela)
        : CVisual(offRender, retiraFundo, corFundo, janela)
    {
        ExtraiPixels();
    }

    CObjeto::CObjeto(CObjeto *objBase, PIG_Cor *corFundo, int retiraFundo, int janela)
        : CVisual(objBase, retiraFundo, corFundo, janela)
    {
        ExtraiPixels();
        SetDimensoes(objBase->alt, objBase->larg);
    }

    CObjeto::~CObjeto()
    {
        for (int i = 0; i < bitmap->h; i++)
            free(pixels[i]);
        free(pixels);
    }

    /*
    int CObjeto::GetIdJanela()
    {
        return idJanela;
    }
    */

    void CObjeto::SetValoresInt(int chave, int valor)
    {
        valoresIntInt[chave] = valor;
    }

    void CObjeto::SetValoresInt(std::string chave, int valor)
    {
        valoresStringInt[chave] = valor;
    }

    void CObjeto::SetValoresFloat(int chave, float valor)
    {
        valoresIntFloat[chave] = valor;
    }

    void CObjeto::SetValoresFloat(std::string chave, float valor)
    {
        valoresStringFloat[chave] = valor;
    }

    void CObjeto::SetValoresString(int chave, std::string valor)
    {
        valoresIntString[chave] = valor;
    }

    void CObjeto::SetValoresString(std::string chave, std::string valor)
    {
        valoresStringString[chave] = valor;
    }

    void CObjeto::SetVertices(std::vector<SDL_Point> vertices)
    {
        this->vertices = vertices;
        this->verticesOriginais = vertices;
    }

    void CObjeto::SetAngulo(float a)
    {
        angulo = a;
        bbAlterado = true;
    }

    bool CObjeto::GetValoresInt(int chave, int &valor)
    {
        std::map<int, int>::iterator it;
        it = valoresIntInt.find(chave);
        if (it == valoresIntInt.end())
            return false;
        valor = it->second;
        return true;
    }

    bool CObjeto::GetValoresInt(std::string chave, int &valor)
    {
        std::map<std::string, int>::iterator it;
        it = valoresStringInt.find(chave);
        if (it == valoresStringInt.end())
            return false;
        valor = it->second;
        return true;
    }

    bool CObjeto::GetValoresFloat(int chave, float &valor)
    {
        std::map<int, float>::iterator it;
        it = valoresIntFloat.find(chave);
        if (it == valoresIntFloat.end())
            return false;
        valor = it->second;
        return true;
    }

    bool CObjeto::GetValoresFloat(std::string chave, float &valor)
    {
        std::map<std::string, float>::iterator it;
        it = valoresStringFloat.find(chave);
        if (it == valoresStringFloat.end())
            return false;
        valor = it->second;
        return true;
    }

    bool CObjeto::GetValoresString(int chave, std::string &valor)
    {
        std::map<int, std::string>::iterator it;
        it = valoresIntString.find(chave);
        if (it == valoresIntString.end())
            return false;
        valor = it->second;
        return true;
    }

    bool CObjeto::GetValoresString(std::string chave, std::string &valor)
    {
        std::map<std::string, std::string>::iterator it;
        it = valoresStringString.find(chave);
        if (it == valoresStringString.end())
            return false;
        valor = it->second;
        return true;
    }

    SDL_Point CObjeto::GetBB(int i)
    {
        return bb[i];
    }

    std::vector<SDL_Point> CObjeto::GetVertices()
    {
        return vertices;
    }

    void CObjeto::Move(int nx, int ny)
    {
        SDL_Point pivo = {x, y};

        x = nx;
        y = ny;
        dest.x = x;
        dest.y = altJanela - alt - y;

        bbAlterado = true;
    }

    int CObjeto::Desenha(COffscreenRenderer *offRender)
    {
        if (offRender == NULL){
            SDL_RenderCopyEx(renderer, text, &frame, &dest, -angulo, &pivoRelativo, flip);
            //DesenhaBB();
            //DesenhaAreaDeColisao({0, 0, 255, 255});
        }else{
            SDL_Texture *textAux = SDL_CreateTextureFromSurface(offRender->GetRenderer(), bitmap);
            SDL_Rect rectAux = dest;
            rectAux.y = offRender->GetAltura() - alt - y;
            SDL_RenderCopyEx(offRender->GetRenderer(), textAux, &frame, &rectAux, -angulo, &pivoRelativo, flip);
            SDL_DestroyTexture(textAux);
        }
        return 0;
    }

    void CObjeto::Atualiza()
    {
        if(bbAlterado) {
            AtualizaBB();
            AtualizaVertices();
            bbAlterado = false;
        }
    }

    bool CObjeto::Colisao(CObjeto *outro)
    {
        Atualiza();
        outro->Atualiza();

        if(ColisaoBB(outro) && outro->ColisaoBB(this)) {
            return true;//ColisaoPoligono(outro) || outro->ColisaoPoligono(this);
        }
        return false;
    }

    int CObjeto::ColisaoBB(CObjeto *outro)
    {

        // caso em q o angulo é 0
        // caso em que o vetor que vai de bb[0] para bb[1] é paralelo ao eixo X, ou seja, nao ira existir uma "projecao" no eixo X
        // os pontos sao trocados para que seja usado o antigo bb[3] para bb[0]
        if (bb[1].y == bb[0].y) {
            for (int i = 1; i < 4; i++) {
                std::swap(bb[i].x, bb[0].x);
                std::swap(bb[i].y, bb[0].y);
            }
        }

        // projecao dos vetores no eixo X deste objeto
        double projecaoAB = projecaoX((double)(bb[1].y - bb[0].y) / (double)(bb[1].x - bb[0].x), bb[0]);
        double projecaoCD = projecaoX((double)(bb[3].y - bb[2].y) / (double)(bb[3].x - bb[2].x), bb[2]);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawLine(renderer,(int)projecaoAB,300,(int)projecaoCD,300);

        // projecao dos pontos(com o angulo dos anteriores) no eixo X do outro objeto
        double projecao[4];
        for (int i = 0; i < 4; i++)
            projecao[i] = projecaoX((double)(bb[1].y - bb[0].y) / (double)(bb[1].x - bb[0].x), outro->GetBB(i));

        double menorA = (projecaoAB < projecaoCD) ? projecaoAB : projecaoCD;
        double maiorA = (projecaoAB > projecaoCD) ? projecaoAB : projecaoCD;
        double menorB = min(projecao);
        double maiorB = max(projecao);

        if (!(menorA < maiorB && maiorA > menorB))
            return false;

        // projecao dos vetores no eixo Y deste objeto
        projecaoAB = projecaoY((double )(bb[2].y - bb[1].y) / (double )(bb[2].x - bb[1].x), bb[1]);
        projecaoCD = projecaoY((double )(bb[0].y - bb[3].y) / (double )(bb[0].x - bb[3].x), bb[3]);

        // projecao dos pontos(com o angulo dos anteriores) no eixo Y do outro objeto
        for (int i = 0; i < 4; i++)
            projecao[i] = projecaoY((double )(bb[2].y - bb[1].y) / (double )(bb[2].x - bb[1].x), outro->GetBB(i));

        menorA = (projecaoAB < projecaoCD) ? projecaoAB : projecaoCD;
        maiorA = (projecaoAB > projecaoCD) ? projecaoAB : projecaoCD;
        menorB = min(projecao);
        maiorB = max(projecao);

        return (menorA < maiorB && maiorA > menorB);
    }

    bool CObjeto::PontoDentro(SDL_Point p)
    {
        int i = 0;
        int quant_intersecoes = 0;

        do {
            if (Intersecao(i, (i + 1) % vertices.size(), p))
                quant_intersecoes++;

            i = (i + 1) % vertices.size();
        } while (i != 0);

        return !(quant_intersecoes % 2 == 0);
    }

    bool CObjeto::ColisaoPoligono(CObjeto *outro)
    {
        for (auto vertice : outro->GetVertices()) {
            if (PontoDentro(vertice)) return true;
        }
        return false;
    }

    PIG_Cor **CObjeto::GetPixels()
    {
        return pixels;
    }

    void CObjeto::AtualizaPixels(int retiraFundo, int opacidadeObj)
    {
        Uint8 *pix8;
        Uint32 *pix32;
        if (bitmap->format->BytesPerPixel == 3) {
            for (int h = 0; h < bitmap->h; h++) {
                pix8 = (Uint8 *)bitmap->pixels + (h * bitmap->pitch);
                for (int w = 0; w < bitmap->w; w++) {
                    if (bitmap->format->format == SDL_PIXELFORMAT_RGB24) {
                        *pix8 = pixels[h][w].r;
                        pix8++;
                        *pix8 = pixels[h][w].g;
                        pix8++;
                        *pix8 = pixels[h][w].b;
                        pix8++;
                    } else {
                        *pix8 = pixels[h][w].b;
                        pix8++;
                        *pix8 = pixels[h][w].g;
                        pix8++;
                        *pix8 = pixels[h][w].r;
                        pix8++;
                    }
                }
            }
        } else if (bitmap->format->BytesPerPixel == 4) {
            pix32 = (Uint32 *)bitmap->pixels;
            for (int h = 0; h < bitmap->h; h++) {
                for (int w = 0; w < bitmap->w; w++) {
                    SDL_GetRGBA((Uint32)*pix32, bitmap->format, &(pixels[h][w].r), &(pixels[h][w].g), &(pixels[h][w].b), &(pixels[h][w].a));
                    pix32++;
                }
            }
        }

        SetOpacidade(opacidadeObj);
        CriaTextura(retiraFundo);
    }


    void CObjeto::DesenhaBB()
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//retângulo verde para o OOBB (com ângulo)
        SDL_RenderDrawLine(renderer, bb[0].x, altJanela - bb[0].y, bb[1].x, altJanela - bb[1].y);
        SDL_RenderDrawLine(renderer, bb[1].x, altJanela - bb[1].y, bb[2].x, altJanela - bb[2].y);
        SDL_RenderDrawLine(renderer, bb[2].x, altJanela - bb[2].y, bb[3].x, altJanela - bb[3].y);
        SDL_RenderDrawLine(renderer, bb[3].x, altJanela - bb[3].y, bb[0].x, altJanela - bb[0].y);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &dest);//retângulo vermelhor para o AABB (sem ângulo)
        //printf("%d,%d,%d,%d\n",dest.x,dest.y,dest.w,dest.h);
    }

    void CObjeto::DesenhaAreaDeColisao(PIG_Cor cor)
    {
        int i = 0;

        if (vertices.empty()) return;

        do {
            SDL_Rect rect;
            rect.x = vertices[i].x;
            rect.y = altJanela - (vertices[i].y + 10);
            rect.h = 10;
            rect.w = 10;

            SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);
            SDL_RenderDrawLine(
                renderer, vertices[i].x, altJanela - vertices[i].y,
                vertices[(i + 1) % vertices.size()].x,
                altJanela - vertices[(i + 1) % vertices.size()].y);
            SDL_RenderFillRect(renderer, &rect);

            i = (i + 1) % vertices.size();
        } while (i != 0);
    }

    void CObjeto::AtualizaBB()
    {
        SDL_Point pivoAbs;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        pivoAbs.x = pivoRelativo.x + x;
        pivoAbs.y = -pivoRelativo.y + y + alt; //inverte o eixo Y, pois o pivoRel considera o eixo Y aumentando para baixo
        //printf("PivoRel: %d %d\n",pivoRelativo.x,pivoRelativo.y);
        //printf("PivoRAbs: %d %d\n",pivoAbs.x,pivoAbs.y);
        float angRad = -angulo * M_PI / 180.0;
        float seno = sin(angRad);
        float cosseno = cos(angRad);
        //printf("Pivo %d %d  %f\n",pivoObj.x,pivoObj.y,angRad);

        //matriz de rota��o
        // ( cos(ang) sin(ang))   (Vx)   (Rx)
        // (-sin(ang) cos(ang)) * (Vy) = (Ry)

        //vetor (Rx,Ry) � a resposta do vetor (Vx,Vy) rotacionado em ang

        bb[0].x = (x - pivoAbs.x) * cosseno + (y - pivoAbs.y) * seno + pivoAbs.x;
        bb[0].y = (y - pivoAbs.y) * cosseno - (x - pivoAbs.x) * seno + pivoAbs.y;
        //printf("bb0: %d %d\n",bb[0].x,bb[0].y);

        bb[1].x = (x + larg - pivoAbs.x) * cosseno + (y - pivoAbs.y) * seno + pivoAbs.x;
        bb[1].y = (y - pivoAbs.y) * cosseno - (x + larg - pivoAbs.x) * seno + pivoAbs.y;
        //printf("bb1: %d %d\n",bb[1].x,bb[1].y);

        bb[2].x = (x + larg - pivoAbs.x) * cosseno + (y + alt - pivoAbs.y) * seno + pivoAbs.x;
        bb[2].y = (y + alt - pivoAbs.y) * cosseno - (x + larg - pivoAbs.x) * seno + pivoAbs.y;
        //printf("bb2: %d %d\n",bb[2].x,bb[2].y);

        bb[3].x = (x - pivoAbs.x) * cosseno + (y + alt - pivoAbs.y) * seno + pivoAbs.x;
        bb[3].y = (y + alt - pivoAbs.y) * cosseno - (x - pivoAbs.x) * seno + pivoAbs.y;
        //printf("bb3: %d %d\n",bb[3].x,bb[3].y);
    }

    void CObjeto::AtualizaVertices()
    {
        double _angulo = M_PI * angulo / 180.0;

        SDL_Point pivo = {pivoRelativo.x + x, -pivoRelativo.y + y + alt};

        for (int i = 0; i < vertices.size(); i++) {
            vertices[i] = {verticesOriginais[i].x + x, verticesOriginais[i].y + y};

            int deltaX = vertices[i].x - pivo.x;
            int deltaY = vertices[i].y - pivo.y;

            vertices[i].x =
                (cos(_angulo) * deltaX) - (sin(_angulo) * deltaY) + pivo.x;
            vertices[i].y =
                (sin(_angulo) * deltaX) + (cos(_angulo) * deltaY) + pivo.y;
        }
    }

    void CObjeto::ExtraiPixels()
    {
        Uint8 *pix8;
        Uint32 *pix32;

        pixels = (PIG_Cor **)malloc(sizeof(PIG_Cor *) * bitmap->h);
        for (int i = 0; i < bitmap->h; i++) {
            pixels[i] = (PIG_Cor *)calloc(sizeof(PIG_Cor), bitmap->w);
        }

        if (bitmap->format->BytesPerPixel == 3) {
            for (int h = 0; h < bitmap->h; h++) {
                pix8 = (Uint8 *)bitmap->pixels + (h * bitmap->pitch);
                for (int w = 0; w < bitmap->w; w++) {
                    if (bitmap->format->format == SDL_PIXELFORMAT_RGB24) {
                        pixels[h][w].r = *pix8;
                        pix8++;
                        pixels[h][w].g = *pix8;
                        pix8++;
                        pixels[h][w].b = *pix8;
                        pix8++;
                    } else {
                        pixels[h][w].b = *pix8;
                        pix8++;
                        pixels[h][w].g = *pix8;
                        pix8++;
                        pixels[h][w].r = *pix8;
                        pix8++;
                    }
                    pixels[h][w].a = 255;
                }
            }
        } else if (bitmap->format->BytesPerPixel == 4) {
            pix32 = (Uint32 *)bitmap->pixels;
            for (int h = 0; h < bitmap->h; h++) {
                for (int w = 0; w < bitmap->w; w++) {
                    SDL_GetRGBA((Uint32)*pix32, bitmap->format, &(pixels[h][w].r), &(pixels[h][w].g), &(pixels[h][w].b), &(pixels[h][w].a));
                    pix32++;
                }
            }
        }
    }

    int CObjeto::arredonda(float valor)
    {
        int resultado = (int)valor;
        if (valor - resultado >= 0.5)
            return valor + 1;
        return valor;
    }

    double CObjeto::projecaoY(double coefAngular, SDL_Point p)
    {
        if (std::isinf(coefAngular))
            return (double)p.y;
        return coefAngular * (-p.x) + p.y;
    }

    double CObjeto::projecaoX(double coefAngular, SDL_Point p)
    {
        if (std::isinf(coefAngular))
            return (double)p.x;

        return (-p.y + (coefAngular * p.x)) / coefAngular;
    }

    double CObjeto::min(double  vetor[4])
    {
        double  menor = vetor[0];
        for (int i = 1; i < 4; i++)
            if (vetor[i] < menor)
                menor = vetor[i];
        return menor;
    }

    double CObjeto::max(double  vetor[4])
    {
        double  maior = vetor[0];
        for (int i = 1; i < 4; i++)
            if (vetor[i] > maior)
                maior = vetor[i];
        return maior;
    }

    bool CObjeto::Entre(int x, int a, int b)
    {
        return ((x > a) && (x < b) || (x < a) && (x > b));
    }

    bool CObjeto::Intersecao(int i, int f, SDL_Point p)
    {
        float m = ((float)vertices[f].y - vertices[i].y) /
                  ((float)vertices[f].x - vertices[i].x);
        int x;

        if (m == 0)
            return p.y == vertices[i].y &&
                   Entre(p.x, vertices[i].x, vertices[f].x);

        if (p.y == vertices[i].y && p.x <= vertices[i].x) {
            int anterior = i == 0 ? vertices.size() - 1 : i - 1;
            return Entre(p.y, vertices[anterior].y, vertices[f].y);
        }

        if (std::isinf(m))
            x = vertices[i].x;
        else
            x = (((float)p.y - vertices[i].y) / (float)m) +
                ((float)vertices[i].x);

        return (x >= p.x) && Entre(p.y, vertices[i].y, vertices[f].y);
    }
