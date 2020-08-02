
#ifndef CPIGCAMPOTEXTOESENHA_H
#define CPIGCAMPOTEXTOESENHA_H

#include "cpigcaixatexto.h"
#include <string>

class CPigCampoTextoESenha: public CPigCaixaTexto
{
public:
    CPigCampoTextoESenha(int idComponente,int px, int py, int altura,int largura,std::string nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1,int janela=0,bool campoSenha = false);
    CPigCampoTextoESenha(std::string nomeArqParam);
    ~CPigCampoTextoESenha();
    
    static CPigCampoTextoESenha LeArquivoParametros(std::string nomeArqParam);
    int Desenha() override;
    void SetMargens(int horEsq,int horDir, int vertBaixo,int vertCima);
    int TrataMouseBotaoDireito(PIG_Evento evento,SDL_Point p);
    int TrataMouseRodinha(PIG_Evento evento);
    int SobeCursor();
    int DesceCursor();
    int PulaLinha();

private:
    char mascara;//s�mbolo usado quando o campo for de senha
    std::string (CPigCampoTextoESenha::*GetTextoVisivelPtr)() = nullptr;
    
    std::string GetTextoMask();
    std::string GetTextoVisivel();
    void AjustaAlinhamento();
};

#endif
