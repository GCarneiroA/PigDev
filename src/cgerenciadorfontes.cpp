
#include "cgerenciadorfontes.h"

#include <iomanip>
#include <sstream>

#include "cmapacaracteres.h"
#include "cmapacaracteresdinamicos.h"
#include "cpoolnumeros.h"

CPoolNumeros *CGerenciadorFontes::numFontes;
int CGerenciadorFontes::totalFontes;
CMapaCaracteres *CGerenciadorFontes::fontes[MAX_FONTES];

     CMapaCaracteres *CGerenciadorFontes::GetFonte(int idFonte){
        return fontes[idFonte];
    }

     void CGerenciadorFontes::Inicia(){
        TTF_Init();

        fontes[0] = new CMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0,BRANCO,0);
        //fontes[0] = new CMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,"desenho.bmp",0,BRANCO,0);
        //fontes[0] = new CMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0);
        totalFontes = 1;

        for (int i=1;i<MAX_FONTES;i++)
            fontes[i] = NULL;

        numFontes = new CPoolNumeros(MAX_FONTES);
    }

     void CGerenciadorFontes::Encerra(){
        for (int i=0;i<MAX_FONTES;i++){
            if (fontes[i]) delete fontes[i];
        }
        delete numFontes;

        TTF_Quit();
    }

     int CGerenciadorFontes::CriaFonteFundo(char *nome,int tamanho,int estilo,char *arquivoFundo,int contorno,PIG_Cor corContorno,int idJanela){
        int resp = numFontes->RetiraLivre();
        fontes[resp] = new CMapaCaracteres(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela);
        totalFontes++;
        return resp;
    }

     int CGerenciadorFontes::CriaFonteNormal(char *nome,int tamanho,int estilo,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,int idJanela){
        int resp = numFontes->RetiraLivre();
        fontes[resp] = new CMapaCaracteres(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela);
        totalFontes++;
        return resp;
    }

     int CGerenciadorFontes::CriaFonteDinamica(char *nome,int tamanho,int idJanela){
        int resp = numFontes->RetiraLivre();
        fontes[resp] = new CMapaCaracteresDinamicos(nome,tamanho,idJanela);
        totalFontes++;
        return resp;
    }

      int CGerenciadorFontes::GetLarguraPixels(std::string texto,int numFonte){
        return fontes[numFonte]->GetLarguraPixelsString(texto);
    }

      int CGerenciadorFontes::GetFonteDescent(int numFonte){
        return fontes[numFonte]->GetFonteDescent();
    }

      int CGerenciadorFontes::GetFonteAscent(int numFonte){
        return fontes[numFonte]->GetFonteAscent();
    }

      void CGerenciadorFontes::EscreverString(std::string str,int x,int y,int numFonte,PIG_PosTexto pos,float angulo){
        fontes[numFonte]->Escreve(str,x,y,pos,angulo);
    }

      void CGerenciadorFontes::EscreverInteiro(int valor,int x,int y,int numFonte,PIG_PosTexto pos,float angulo){
        std::stringstream str;
        str<<valor;
        fontes[numFonte]->Escreve(str.str(),x,y,pos,angulo);
    }

      void CGerenciadorFontes::EscreverReal(double valor,int x,int y,int numFonte,int casas,PIG_PosTexto pos,float angulo){
        std::stringstream str;
        str.setf(std::ios_base::fixed, std::ios_base::floatfield);
        str<<std::setprecision(casas)<<valor;
        fontes[numFonte]->Escreve(str.str(),x,y,pos,angulo);
    }

      void CGerenciadorFontes::EscreverLonga(std::string str,int x,int y,int largMax,int espacoEntreLinhas,int numFonte,PIG_PosTexto pos,float angulo){
        fontes[numFonte]->EscreveLonga(str,x,y,largMax,espacoEntreLinhas,pos,angulo);
    }

      std::vector<std::string> CGerenciadorFontes::ExtraiLinhasString(std::string texto,int largMax,int numFonte){
        return fontes[numFonte]->ExtraiLinhas(texto,largMax);
    }

      PIG_Metricas_Fonte CGerenciadorFontes::GetMetricas(Uint16 letra, int numFonte,PIG_Estilo estilo){
        return fontes[numFonte]->GetMetricasLetra(letra,estilo);
    }

      int CGerenciadorFontes::GetLarguraLetra(char letra,int numFonte, PIG_Estilo estilo){
        return fontes[numFonte]->GetLarguraLetra(letra,estilo);
    }

      int CGerenciadorFontes::GetTamanhoBaseFonte(int numFonte){
        return fontes[numFonte]->GetTamanhoBaseFonte();
    }

      int CGerenciadorFontes::GetLineSkip(int numFonte){
        return fontes[numFonte]->GetLineSkip();
    }

      SDL_Surface *CGerenciadorFontes::GetGlyph(Uint16 *ch,int numFonte,PIG_Cor cor){
        return fontes[numFonte]->GetGlyph(ch,cor);
    }

     void CGerenciadorFontes::DestroiFonte(int idFonte){
        if (idFonte==0) return;             //a fonte padrao s� � destruida quando o gerenciador for encerrado
        numFontes->DevolveUsado(idFonte);
        delete fontes[idFonte];
        totalFontes--;
        fontes[idFonte] = NULL;
    }

     void CGerenciadorFontes::SubstituiCaracter(uint16_t caracter,std::string nomeArquivo,int largNova,int x,int y,int altura,int largura,int numFonte){
        fontes[numFonte]->SubstituiGlyph(nomeArquivo,caracter,largNova,x,y,altura,largura);
    }
