

#include "cgerenciadorjanelas.h"

#include "tipos_pig.h"

#include "cpigerroindice.h"

#include "cjanela.h"

int CGerenciadorJanelas::qtdJanelas;
CJanela *CGerenciadorJanelas::janelas[MAX_JANELAS];

 void CGerenciadorJanelas::Inicia(std::string nome,int altura,int largura){
    qtdJanelas = 0;
    for (int i=0;i<MAX_JANELAS;i++)
        janelas[i] = NULL;

    janelas[qtdJanelas++] = new CJanela(nome,qtdJanelas,altura,largura);
}

 void CGerenciadorJanelas::Encerra(){
    for (int i=0;i<qtdJanelas;i++)
        if (janelas[i]) delete janelas[i];
}

 int CGerenciadorJanelas::GetQtdJanelas(){
    int resp = qtdJanelas;
    for (int i=0;i<qtdJanelas;i++)
        if (GetJanela(i)->GetFechada()) resp--;
    return resp;
}

 int CGerenciadorJanelas::CriaJanela(std::string nome,int altura,int largura){
    if (qtdJanelas==MAX_JANELAS) return -1;
    janelas[qtdJanelas++] = new CJanela(nome,qtdJanelas,altura,largura);
    return qtdJanelas-1;//foi incrmentada log acima
}

 void CGerenciadorJanelas::FechaJanela(int idJanela){
    GetJanela(idJanela)->Fecha();
}

 void CGerenciadorJanelas::EscondeJanela(int idJanela){
    GetJanela(idJanela)->Esconde();
}

 void CGerenciadorJanelas::ExibeJanela(int idJanela){
    GetJanela(idJanela)->Exibe();
}

 void CGerenciadorJanelas::GanhaFocoJanela(int idJanela){
    GetJanela(idJanela)->GanhaFoco();
}

 CJanela *CGerenciadorJanelas::GetJanela(int idJanela){
    if (idJanela<0||idJanela>=qtdJanelas||janelas[idJanela]==NULL) throw CPigErroIndice(idJanela,"janelas");
    return janelas[idJanela];
}

 void CGerenciadorJanelas::IniciaDesenho(int idJanela){
    if (idJanela>-1){
        GetJanela(idJanela)->IniciaDesenho();
    }else{
        for (int i=0;i<qtdJanelas;i++){
            GetJanela(i)->IniciaDesenho();
        }
    }
}

 void CGerenciadorJanelas::EncerraDesenho(int idJanela){
    if (idJanela>-1){
        GetJanela(idJanela)->EncerraDesenho();
    }else{
        for (int i=0;i<qtdJanelas;i++){
            GetJanela(i)->EncerraDesenho();
        }
    }
}

 void CGerenciadorJanelas::DefineFundo(std::string nomeArquivo,int idJanela){
    GetJanela(idJanela)->DefineFundo(nomeArquivo);
}

 void CGerenciadorJanelas::SaveScreenshotBMP(std::string nomeArquivo,int idJanela) {
    GetJanela(idJanela)->SaveScreenshot(nomeArquivo,true);//true == bitmap
}

 void CGerenciadorJanelas::SaveScreenshotPNG(std::string nomeArquivo,int idJanela) {
    GetJanela(idJanela)->SaveScreenshot(nomeArquivo,false);//false == PNG
}

 int CGerenciadorJanelas::GetAltura(int idJanela){
    return GetJanela(idJanela)->GetAltura();
}

 int CGerenciadorJanelas::GetLargura(int idJanela){
    return GetJanela(idJanela)->GetLargura();
}

 void CGerenciadorJanelas::SetTamanho(int altura,int largura,int idJanela){ 
    GetJanela(idJanela)->SetTamanho(altura,largura);
}

 std::string CGerenciadorJanelas::GetTitulo(int idJanela){
    return GetJanela(idJanela)->GetTitulo();
}

 void CGerenciadorJanelas::SetTitulo(std::string novoTitulo,int idJanela){
    GetJanela(idJanela)->SetTitulo(novoTitulo);
}

 PIG_Cor CGerenciadorJanelas::GetCorFundo(int idJanela){
    return GetJanela(idJanela)->GetCorFundo();
}

 void CGerenciadorJanelas::SetCorFundo(PIG_Cor cor,int idJanela){
    GetJanela(idJanela)->SetCorFundo(cor);
}

 float CGerenciadorJanelas::GetOpacidade(int idJanela){
    return GetJanela(idJanela)->GetOpacidade();
}

 void CGerenciadorJanelas::SetOpacidade(float valor,int idJanela){
    GetJanela(idJanela)->SetOpacidade(valor);
}

 void CGerenciadorJanelas::SetPosicao(int x,int y,int idJanela){
    GetJanela(idJanela)->SetPosicao(x,y);
}

 void CGerenciadorJanelas::GetPosicao(int *x,int *y,int idJanela){
    GetJanela(idJanela)->GetPosicao(x,y);
}

 void CGerenciadorJanelas::SetBorda(int valor,int idJanela){
    GetJanela(idJanela)->SetBorda(valor);
}

 void CGerenciadorJanelas::SetModo(int modo,int idJanela){
    GetJanela(idJanela)->SetModo(modo);
}

 int CGerenciadorJanelas::GetModo(int idJanela){
    return GetJanela(idJanela)->GetModo();
}

 void CGerenciadorJanelas::DesenhaRetangulo(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor, int idJanela){
    GetJanela(idJanela)->DesenhaRetangulo(x,y,alturaRet,larguraRet,cor);
}

 void CGerenciadorJanelas::DesenhaRetanguloVazado(int x, int y, int alturaRet, int larguraRet, PIG_Cor cor, int idJanela){
    GetJanela(idJanela)->DesenhaRetanguloVazado(x,y,alturaRet,larguraRet,cor);
}

 void CGerenciadorJanelas::DesenhaLinhaSimples(int x1,int y1,int x2,int y2,PIG_Cor cor,int idJanela){
    GetJanela(idJanela)->DesenhaLinhaSimples(x1,y1,x2,y2,cor);
}

 void CGerenciadorJanelas::DesenhaLinhasDisjuntas(int *x,int *y,int qtd,PIG_Cor cor,int idJanela){
    GetJanela(idJanela)->DesenhaLinhasDisjuntas(x,y,qtd,cor);
}

 void CGerenciadorJanelas::DesenhaLinhasSequencia(int *x,int *y,int qtd,PIG_Cor cor,int idJanela){
    GetJanela(idJanela)->DesenhaLinhasSequencia(x,y,qtd,cor);
}

 PIG_Cor CGerenciadorJanelas::GetPixel(int x, int y, int idJanela){
    return GetJanela(idJanela)->GetPixel(x,y);
}
