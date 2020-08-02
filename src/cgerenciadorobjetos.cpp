
#include "cgerenciadorobjetos.h"

#include "cpigerroindice.h"

#include "cobjeto.h"

#include "cpoolnumeros.h"

CPoolNumeros *CGerenciadorObjetos::numObjetos;
int CGerenciadorObjetos::totalObjetos;
CObjeto *CGerenciadorObjetos::objetos[MAX_OBJETOS];


      CObjeto *CGerenciadorObjetos::GetObjeto(int idObjeto){
        if (idObjeto<0||idObjeto>=MAX_OBJETOS||objetos[idObjeto]==NULL) throw CPigErroIndice(idObjeto,"objetos");
        return objetos[idObjeto];
    }

     void CGerenciadorObjetos::Inicia(){
        totalObjetos = 0;
        for (int i=0;i<MAX_OBJETOS;i++)
            objetos[i] = NULL;
        numObjetos = new CPoolNumeros(MAX_OBJETOS);
    }

     void CGerenciadorObjetos::Encerra(){
        for (int i=0;i<MAX_OBJETOS;i++){
            if (objetos[i]) delete objetos[i];
        }
        delete numObjetos;
    }

     int CGerenciadorObjetos::CriaObjeto(std::string nomeArquivoBMP,PIG_Cor *corFundo,int retiraFundo,int idJanela){
        int resp = numObjetos->RetiraLivre();
        objetos[resp] = new CObjeto(nomeArquivoBMP,corFundo,retiraFundo,idJanela);
        totalObjetos++;
        return resp;
    }

     int CGerenciadorObjetos::CriaObjetoOffScreen(COffscreenRenderer *offRenderer,PIG_Cor *corFundo,int retiraFundo,int idJanela){
        int resp = numObjetos->RetiraLivre();
        objetos[resp] = new CObjeto(offRenderer,corFundo,retiraFundo,idJanela);
        totalObjetos++;
        return resp;
    }

     void CGerenciadorObjetos::DestroiObjeto(int idObjeto){
        if (idObjeto<0||idObjeto>=MAX_OBJETOS||objetos[idObjeto]==NULL) throw CPigErroIndice(idObjeto,"objetos");
        numObjetos->DevolveUsado(idObjeto);
        delete objetos[idObjeto];
        totalObjetos--;
        objetos[idObjeto] = NULL;
    }

      void CGerenciadorObjetos::SetValorIntObjeto(int idObjeto, int chave, int valor){
        GetObjeto(idObjeto)->SetValoresInt(chave,valor);
    }

      void CGerenciadorObjetos::SetValorIntObjeto(int idObjeto, std::string chave, int valor){
        GetObjeto(idObjeto)->SetValoresInt(chave,valor);
    }

      void CGerenciadorObjetos::SetValorFloatObjeto(int idObjeto, int chave, float valor){
        GetObjeto(idObjeto)->SetValoresFloat(chave,valor);
    }

      void CGerenciadorObjetos::SetValorFloatObjeto(int idObjeto, std::string chave, float valor){
        GetObjeto(idObjeto)->SetValoresFloat(chave,valor);
    }

      void CGerenciadorObjetos::SetValorStringObjeto(int idObjeto, int chave, std::string valor){
        GetObjeto(idObjeto)->SetValoresString(chave,valor);
    }

      void CGerenciadorObjetos::SetValorStringObjeto(int idObjeto, std::string chave, std::string valor){
        GetObjeto(idObjeto)->SetValoresString(chave,valor);
    }

      bool CGerenciadorObjetos::GetValorIntObjeto(int idObjeto, int indice, int *valor){
        return GetObjeto(idObjeto)->GetValoresInt(indice,*valor);
    }

      bool CGerenciadorObjetos::GetValorFloatObjeto(int idObjeto, int indice, float *valor){
        return GetObjeto(idObjeto)->GetValoresFloat(indice,*valor);
    }

      bool CGerenciadorObjetos::GetValorStringObjeto(int idObjeto, int indice, char *valor){
        std::string str;
        bool resp = GetObjeto(idObjeto)->GetValoresString(indice,str);
        strcpy(valor,str.c_str());
        return resp;
    }

      bool CGerenciadorObjetos::GetValorIntObjeto(int idObjeto, std::string indice, int *valor){
        return GetObjeto(idObjeto)->GetValoresInt(indice,*valor);
    }

      bool CGerenciadorObjetos::GetValorFloatObjeto(int idObjeto, std::string indice, float *valor){
        return GetObjeto(idObjeto)->GetValoresFloat(indice,*valor);
    }

      bool CGerenciadorObjetos::GetValorStringObjeto(int idObjeto, std::string indice, char *valor){
        std::string str;
        bool resp = GetObjeto(idObjeto)->GetValoresString(indice,str);
        strcpy(valor,str.c_str());
        return resp;
    }

      void CGerenciadorObjetos::GetPosicaoXY(int idObjeto, int *x, int *y){
        GetObjeto(idObjeto)->GetXY(*x,*y);
    }

      void CGerenciadorObjetos::Move(int idObjeto, int x, int y){
        GetObjeto(idObjeto)->Move(x,y);
    }

      void CGerenciadorObjetos::Desloca(int idObjeto, int dx, int dy){
        GetObjeto(idObjeto)->Desloca(dx,dy);
    }

      void CGerenciadorObjetos::SetAngulo(int idObjeto, float angulo){
        GetObjeto(idObjeto)->SetAngulo(angulo);
    }

      float CGerenciadorObjetos::GetAngulo(int idObjeto){
        return GetObjeto(idObjeto)->GetAngulo();
    }

      void CGerenciadorObjetos::SetPivo(int idObjeto, int x, int y){
        GetObjeto(idObjeto)->SetPivo(x,y);
    }

      void CGerenciadorObjetos::SetPivo(int idObjeto, float relX, float relY){
        GetObjeto(idObjeto)->SetPivo(relX,relY);
    }

      void CGerenciadorObjetos::GetPivo(int idObjeto, int *x,int *y){
        GetObjeto(idObjeto)->GetPivo(*x,*y);
    }

      void CGerenciadorObjetos::SetFlip(int idObjeto, PIG_Flip valor){
        GetObjeto(idObjeto)->SetFlip(valor);
    }

      PIG_Flip CGerenciadorObjetos::GetFlip(int idObjeto){
        return GetObjeto(idObjeto)->GetFlip();
    }

      void CGerenciadorObjetos::SetDimensoes(int idObjeto, int altura, int largura){
        GetObjeto(idObjeto)->SetDimensoes(altura,largura);
    }

      void CGerenciadorObjetos::GetDimensoes(int idObjeto, int *altura, int *largura){
        GetObjeto(idObjeto)->GetDimensoes(*altura,*largura);
    }

      void CGerenciadorObjetos::GetDimensoesOriginais(int idObjeto, int *altura, int *largura){
        GetObjeto(idObjeto)->GetDimensoesOriginais(*altura,*largura);
    }

      void CGerenciadorObjetos::CriaFrame(int idObjeto, int xBitmap, int yBitmap,int altura,int largura){
        SDL_Rect r;
        r.x = xBitmap;
        r.y = yBitmap;
        r.h = altura;
        r.w = largura;
        GetObjeto(idObjeto)->DefineFrame(r);
    }

      void CGerenciadorObjetos::SetColoracao(int idObjeto, PIG_Cor cor){
        GetObjeto(idObjeto)->SetColoracao(cor);
    }

      void CGerenciadorObjetos::SetOpacidade(int idObjeto, int valor){
        GetObjeto(idObjeto)->SetOpacidade(valor);
    }

      int CGerenciadorObjetos::GetOpacidade(int idObjeto){
        return GetObjeto(idObjeto)->GetOpacidade();
    }

      void CGerenciadorObjetos::Desenha(int idObjeto,COffscreenRenderer *offRender){
        GetObjeto(idObjeto)->Desenha(offRender);
    }

      int CGerenciadorObjetos::TestaColisaoPoligono(int idObjeto1, int idObjeto2) {
        return GetObjeto(idObjeto1)->ColisaoPoligono(GetObjeto(idObjeto2)) || GetObjeto(idObjeto2)->ColisaoPoligono(GetObjeto(idObjeto1));
    }

      int CGerenciadorObjetos::TestaColisao(int idObjeto1, int idObjeto2) {
        return GetObjeto(idObjeto1)->Colisao(GetObjeto(idObjeto2)) && GetObjeto(idObjeto2)->Colisao(GetObjeto(idObjeto1));
    }

      void CGerenciadorObjetos::DefineAreaColisao(int idObjeto, int *x, int *y, int quantidadePontos) {
        std::vector<SDL_Point> vertices;

        for (int i = 0; i < quantidadePontos; i++) {
            SDL_Point aux = {x[i], y[i]};
            vertices.push_back(aux);
        }

        GetObjeto(idObjeto)->SetVertices(vertices);
    }

      PIG_Cor **CGerenciadorObjetos::GetPixels(int idObjeto){
        return GetObjeto(idObjeto)->GetPixels();
    }

      void CGerenciadorObjetos::AtualizaPixels(int idObjeto,int retiraFundo){
        GetObjeto(idObjeto)->AtualizaPixels(retiraFundo);
    }
    