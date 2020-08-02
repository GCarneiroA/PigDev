
#include "cgerenciadorparticulas.h"
#include "canimacao.h"
#include "cgeradorparticulas.h"
#include "cobjeto.h"
#include "cpoolnumeros.h"

CPoolNumeros *CGerenciadorParticulas::numGeradores;
int CGerenciadorParticulas::totalGeradores;
CGeradorParticulas *CGerenciadorParticulas::geradores[MAX_GERADORPARTICULAS];

     void CGerenciadorParticulas::Inicia(SDL_Renderer *renderer)
    {
        //render = renderer;
        totalGeradores = 0;
        for (int i=0;i<MAX_GERADORPARTICULAS;i++)
            geradores[i] = NULL;
        numGeradores = new CPoolNumeros(MAX_GERADORPARTICULAS);
    }

     void CGerenciadorParticulas::Encerra(){
        for (int i=0;i<MAX_GERADORPARTICULAS;i++){
            if (geradores[i]) delete geradores[i];
        }
        delete numGeradores;
    }

     int CGerenciadorParticulas::CriaGeradorParticulas(int maxParticulas,std::string nomeArquivoBMP,int audioCriacao, int audioEncerramento, int idJanela,int usaGerenciadorTimer)
    {
        int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CGeradorParticulas(maxParticulas,nomeArquivoBMP,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;
    }

     int CGerenciadorParticulas::CriaGeradorParticulas(int maxParticulas, CAnimacao *animacaoBase,int audioCriacao, int audioEncerramento, int idJanela,int usaGerenciadorTimer)
    {
        int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CGeradorParticulas(maxParticulas,animacaoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;
    }

     int CGerenciadorParticulas::CriaGeradorParticulas(int maxParticulas,CObjeto *objetoBase,int audioCriacao, int audioEncerramento, int idJanela,int usaGerenciadorTimer)
    {
        int resp = numGeradores->RetiraLivre();
        geradores[resp] = new CGeradorParticulas(maxParticulas,objetoBase,audioCriacao,audioEncerramento,usaGerenciadorTimer,idJanela);
        totalGeradores++;
        return resp;
    }

     void CGerenciadorParticulas::DestroiGeradorParticulas(int idGerador)
    {
        numGeradores->DevolveUsado(idGerador);
        delete geradores[idGerador];
        totalGeradores--;
        geradores[idGerador] = NULL;
    }

      void CGerenciadorParticulas::Move(int idGerador,int px,int py){
        geradores[idGerador]->Move(px,py);
    }

      void CGerenciadorParticulas::Desloca(int idGerador,int dx,int dy){
        geradores[idGerador]->Desloca(dx,dy);
    }

      void CGerenciadorParticulas::MudaDirecaoParticulas(int idGerador,int dx,int dy){
        geradores[idGerador]->MudaDirecao(dx,dy);
    }

      void CGerenciadorParticulas::MudaRotacaoParticulas(int idGerador,float angPerSec){
        geradores[idGerador]->MudaRotacao(angPerSec);
    }

      void CGerenciadorParticulas::MudaCorParticulas(int idGerador,PIG_Cor cor){
        geradores[idGerador]->MudaCor(cor);
    }

      void CGerenciadorParticulas::MudaEscalaParticulas(int idGerador,float escalaInicial,float escalaFinal){
        geradores[idGerador]->MudaEscala(escalaInicial,escalaFinal);
    }

      void CGerenciadorParticulas::SetPivoParticulas(int idGerador,int pivoX,int pivoY){
        geradores[idGerador]->SetPivo(pivoX,pivoY);
    }

      void CGerenciadorParticulas::SetPivoParticulas(int idGerador,float pivoX,float pivoY){
        geradores[idGerador]->SetPivo(pivoX,pivoY);
    }

      int CGerenciadorParticulas::CriaParticula(int idGerador,int fadingOut,int minX,int minY,int maxX,int maxY,float maxTempo)
    {
        return geradores[idGerador]->CriaParticula(fadingOut,minX,minY,maxX,maxY,maxTempo);
    }

      void CGerenciadorParticulas::MoveParticulas(int idGerador){
        geradores[idGerador]->MoveParticulas();
    }

      int CGerenciadorParticulas::GetQtdAtivas(int idGerador){
        return geradores[idGerador]->GetQtdAtivas();
    }

      void CGerenciadorParticulas::Desenha(int idGerador){
        geradores[idGerador]->Desenha();
    }

      int CGerenciadorParticulas::Colisao(int idGerador,CObjeto *obj){
        return geradores[idGerador]->Colisao(obj);
    }
