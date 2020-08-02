
#include "pig.h"

#include "canimacao.h"

CJogo *jogo = nullptr;

void CriaJogo(char *nomeJanela,int cursorProprio,int altura,int largura)
{
    if (jogo==NULL){
        jogo = new CJogo(nomeJanela,cursorProprio,altura,largura);
        CAssetLoader::Inicia();
        CMouse::Inicia(cursorProprio);
        CGerenciadorFontes::Inicia();
        CGerenciadorTimers::Inicia();
        CGerenciadorAudios::Inicia();
        CGerenciadorObjetos::Inicia();
        CGerenciadorParticulas::Inicia();
        CGerenciadorAnimacoes::Inicia();
        CGerenciadorControles::Inicia();
        CGerenciadorSockets::Inicia();
        CGerenciadorVideos::Inicia();
    }
}

int GetEstadoJogo()
{
    return jogo->GetEstado();
}

void SetEstadoJogo(int estado)
{
    jogo->SetEstado(estado);
}

void DefineFundo(char *nomeArquivoImagem,int idJanela)
{
    CGerenciadorJanelas::DefineFundo(nomeArquivoImagem,idJanela);
}

PIG_Teclado GetTeclado()
{
    return jogo->PegaTeclado();
}

PIG_Evento GetEvento(){
    return jogo->PegaEvento();
}

void IniciaDesenho(int idJanela){
    jogo->IniciaDesenho(idJanela);
}

void EncerraDesenho(int idJanela){
    CMouse::Desenha();
    jogo->EncerraDesenho(idJanela);
}

void SalvaTela(char *nomeArquivoBMP,int idJanela){
    CGerenciadorJanelas::SaveScreenshotBMP(nomeArquivoBMP,idJanela);
}

int JogoRodando(){
    return jogo->GetRodando();
}

void Espera(int tempo){
    SDL_Delay(tempo);
}

void FinalizaJogo(){
    CGerenciadorControles::Encerra();
    CGerenciadorFontes::Encerra();
    CGerenciadorAnimacoes::Encerra();
    CGerenciadorParticulas::Encerra();
    CGerenciadorObjetos::Encerra();
    CGerenciadorTimers::Encerra();
    CGerenciadorVideos::Encerra();
    CGerenciadorSockets::Encerra();
    if (jogo->cursorPadrao==0)
        CMouse::Encerra();
    CAssetLoader::Encerra();
    delete jogo;
}

float GetFPS(){
    return jogo->GetFPS();
}

void CarregaCursor(int indice,char *nomeArquivoCursor){
    CMouse::CarregaCursor(indice,nomeArquivoCursor);
}

void MudaCursor(int indice){
    CMouse::MudaCursor(indice);
}

int GetQtdJanelas(){
    return CGerenciadorJanelas::GetQtdJanelas();
}

int CriaJanela(char *nomeJanela,int altura,int largura){
    return CGerenciadorJanelas::CriaJanela(nomeJanela,altura,largura);
}

void FechaJanela(int idJanela){
    CGerenciadorJanelas::FechaJanela(idJanela);
}

void EscondeJanela(int idJanela){
    CGerenciadorJanelas::EscondeJanela(idJanela);
}

void ExibeJanela(int idJanela){
    CGerenciadorJanelas::ExibeJanela(idJanela);
}

void GanhaFocoJanela(int idJanela){
    CGerenciadorJanelas::GanhaFocoJanela(idJanela);
}

int GetAlturaJanela(int idJanela){
    return CGerenciadorJanelas::GetAltura(idJanela);
}

int GetLarguraJanela(int idJanela){
    return CGerenciadorJanelas::GetLargura(idJanela);
}

void SetTamanhoJanela(int altura, int largura,int idJanela){
    CGerenciadorJanelas::SetTamanho(altura,largura,idJanela);
}

void GetTituloJanela(char *tituloJanela,int idJanela){
    std::string resp = CGerenciadorJanelas::GetTitulo(idJanela);
    strcpy(tituloJanela,resp.c_str());
}

void SetTituloJanela(char *novoTitulo,int idJanela){
    CGerenciadorJanelas::SetTitulo(novoTitulo,idJanela);
}

PIG_Cor GetCorFundoJanela(int idJanela){
    return CGerenciadorJanelas::GetCorFundo(idJanela);
}

void SetCorFundoJanela(PIG_Cor cor,int idJanela){
    CGerenciadorJanelas::SetCorFundo(cor,idJanela);
}

float GetOpacidadeJanela(int idJanela){
    return CGerenciadorJanelas::GetOpacidade(idJanela);
}

void SetOpacidadeJanela(float nivelOpacidade,int idJanela){
    CGerenciadorJanelas::SetOpacidade(nivelOpacidade,idJanela);
}

void SetPosicaoJanela(int posicaoX,int posicaoY,int idJanela){
    CGerenciadorJanelas::SetPosicao(posicaoX,posicaoY,idJanela);
}

void GetPosicaoJanela(int *posicaoX,int *posicaoY,int idJanela){
    CGerenciadorJanelas::GetPosicao(posicaoX,posicaoY,idJanela);
}

void SetBordaJanela(int valor,int idJanela){
    CGerenciadorJanelas::SetBorda(valor,idJanela);
}

void SetModoJanela(int modo,int idJanela){
    CGerenciadorJanelas::SetModo(modo,idJanela);
}

int GetModoJanela(int idJanela){
    return CGerenciadorJanelas::GetModo(idJanela);
}

int BotaoPressionadoControle(int idControle,int botao){
    return CGerenciadorControles::BotaoPressionado(idControle,botao);
}

int EixoAcionadoControle(int idControle,int eixo){
    return CGerenciadorControles::EixoAcionado(idControle,eixo);
}

float EixoAcionadoPercentualControle(int idControle,int eixo){
    return CGerenciadorControles::EixoAcionadoPercentual(idControle,eixo);
}

int GetQtdEixosControle(int idControle){
    return CGerenciadorControles::GetQtdEixos(idControle);
}

int GetQtdBotoesControle(int idControle){
    return CGerenciadorControles::GetQtdBotoes(idControle);
}

void GetNomeControle(int idControle,char *nomeControle){
    CGerenciadorControles::GetNome(idControle,nomeControle);
}

void DesenhaLinhaSimples(int pontoX1,int pontoY1,int pontoX2,int pontoY2, PIG_Cor cor, int idJanela){
    CGerenciadorJanelas::DesenhaLinhaSimples(pontoX1,pontoY1,pontoX2,pontoY2,cor,idJanela);
}

void DesenhaLinhasDisjuntas(int *pontosX,int *pontosY,int qtd, PIG_Cor cor, int idJanela){
    CGerenciadorJanelas::DesenhaLinhasDisjuntas(pontosX,pontosY,qtd,cor,idJanela);
}

void DesenhaLinhasSequencia(int *pontosX,int *pontosY,int qtd, PIG_Cor cor, int idJanela){
    CGerenciadorJanelas::DesenhaLinhasSequencia(pontosX,pontosY,qtd,cor,idJanela);
}

void DesenhaRetangulo(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela){
    CGerenciadorJanelas::DesenhaRetangulo(posicaoX,posicaoY,altura,largura,cor,idJanela);
}

void DesenhaRetanguloVazado(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela){
    CGerenciadorJanelas::DesenhaRetanguloVazado(posicaoX,posicaoY,altura,largura,cor,idJanela);
}

void DesenhaPoligono(int *pontosX,int *pontosY,int qtd, PIG_Cor cor, int idJanela){
    jogo->PintarPoligono(pontosX,pontosY,qtd,cor,idJanela);
}

void PreparaOffScreenRenderer(int altura,int largura){
    jogo->PreparaOffScreenRenderer(altura,largura);
}

void SalvaOffScreenBMP(char *nomeArquivoBMP){
    jogo->SalvaOffScreenBMP(nomeArquivoBMP);
}

void SalvaOffScreenPNG(char *nomeArquivoPNG){
    jogo->SalvaOffScreenPNG(nomeArquivoPNG);
}

void PintaAreaOffScreen(int posicaoX,int posicaoY,PIG_Cor cor,void *ponteiro){
    jogo->PintaAreaOffScreen(posicaoX,posicaoY,cor,ponteiro);
}

void DefineFuncaoPintarAreaOffscreen(PIG_Cor (*funcao)(int,int,int,int,PIG_Cor,PIG_Cor)){
    jogo->DefineFuncaoPintarArea(funcao);
}

void MoveCanetaOffscreen(double novoX,double novoY){
    jogo->MoveCanetaOffscreen(novoX,novoY);
}

void AvancaCanetaOffscreen(double distancia){
    jogo->AvancaCanetaOffscreen(distancia);
}

void MudaCorCanetaOffscreen(PIG_Cor novaCor){
    jogo->MudaCorCanetaOffscreen(novaCor);
}

void GiraCanetaHorarioOffscreen(double angulo){
    jogo->GiraCanetaHorarioOffscreen(angulo);
}

void GiraCanetaAntiHorarioOffscreen(double angulo){
    jogo->GiraCanetaAntiHorarioOffscreen(angulo);
}

void GiraCanetaAnguloFixoOffscreen(double angulo){
    jogo->GiraCanetaAnguloFixoOffscreen(angulo);
}

double GetAnguloAtualOffscreen(){
    return jogo->GetAngAtual();
}

int GetXCanetaOffscreen(){
    return jogo->GetXCaneta();
}

int GetYCanetaOffscreen(){
    return jogo->GetYCaneta();
}

void PintaFundoOffScreen(PIG_Cor cor){
    jogo->PintaFundoOffScreen(cor);
}

void DesenhaRetanguloOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->DesenhaRetanguloOffScreen(x1,y1,altura,largura,cor);
}

void DesenhaRetanguloVazadoOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->DesenhaRetanguloVazadoOffScreen(x1,y1,altura,largura,cor);
}

void DesenhaLinhaSimplesOffScreen(int x1,int y1,int x2,int y2,PIG_Cor cor){
    jogo->DesenhaLinhaOffScreen(x1,y1,x2,y2,cor);
}

int CriaFonteNormal(char *nome,int tamanho,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,PIG_Estilo estilo,int idJanela){
    return CGerenciadorFontes::CriaFonteNormal(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela);
}

int CriaFonteDinamica(char *nome,int tamanho,int idJanela){
    return CGerenciadorFontes::CriaFonteDinamica(nome,tamanho,idJanela);
}

int CriaFonteFundo(char *nome,int tamanho,char *arquivoFundo,int contorno,PIG_Cor corContorno,PIG_Estilo estilo,int idJanela){
    return CGerenciadorFontes::CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela);
}

int CalculaLarguraPixels(char *str,int numFonte){
    return CGerenciadorFontes::GetLarguraPixels(str,numFonte);
}

void EscreverDireita(char *str,int posicaoX,int posicaoY,int numFonte,float angulo){
    CGerenciadorFontes::EscreverString(str,posicaoX,posicaoY,numFonte,CPIG_TEXTO_DIREITA,angulo);
}

void EscreverEsquerda(char *str,int posicaoX,int posicaoY,int numFonte,float angulo){
    CGerenciadorFontes::EscreverString(str,posicaoX,posicaoY,numFonte,CPIG_TEXTO_ESQUERDA,angulo);
}

void EscreverCentralizada(char *str,int posicaoX,int posicaoY,int numFonte,float angulo){
    CGerenciadorFontes::EscreverString(str,posicaoX,posicaoY,numFonte,CPIG_TEXTO_CENTRO,angulo);
}

void EscreverLongaEsquerda(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,int numFonte,float angulo){
    CGerenciadorFontes::EscreverLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,numFonte,CPIG_TEXTO_ESQUERDA,angulo);
}

void EscreverLongaDireita(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,int numFonte,float angulo){
    CGerenciadorFontes::EscreverLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,numFonte,CPIG_TEXTO_DIREITA,angulo);
}

void EscreverLongaCentralizada(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,int numFonte,float angulo){
    CGerenciadorFontes::EscreverLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,numFonte,CPIG_TEXTO_CENTRO,angulo);
}

void EscreveInteiroEsquerda(int valor, int x, int y, int numFonte,float angulo){
    CGerenciadorFontes::EscreverInteiro(valor,x,y,numFonte,CPIG_TEXTO_ESQUERDA,angulo);
}

void EscreveInteiroDireita(int valor, int x, int y, int numFonte,float angulo){
    CGerenciadorFontes::EscreverInteiro(valor,x,y,numFonte,CPIG_TEXTO_DIREITA,angulo);
}

void EscreveInteiroCentralizado(int valor, int x, int y, int numFonte,float angulo){
    CGerenciadorFontes::EscreverInteiro(valor,x,y,numFonte,CPIG_TEXTO_CENTRO,angulo);
}

void EscreveDoubleEsquerda(double valor, int casas, int x, int y, int numFonte,float angulo){
    CGerenciadorFontes::EscreverReal(valor,x,y,numFonte,casas,CPIG_TEXTO_ESQUERDA,angulo);
}

void EscreveDoubleDireita(double valor, int casas, int x, int y, int numFonte,float angulo){
    CGerenciadorFontes::EscreverReal(valor,x,y,numFonte,casas,CPIG_TEXTO_DIREITA,angulo);
}

void EscreveDoubleCentralizado(double valor, int casas, int x, int y, int numFonte,float angulo){
    CGerenciadorFontes::EscreverReal(valor,x,y,numFonte,casas,CPIG_TEXTO_CENTRO,angulo);
}

PIG_Metricas_Fonte GetMetricas(char letra, PIG_Estilo estilo,int numFonte){
    return CGerenciadorFontes::GetMetricas(letra,numFonte,estilo);
}

int GetLarguraLetra(char letra,PIG_Estilo estilo,int numFonte){
    return CGerenciadorFontes::GetLarguraLetra(letra,numFonte,estilo);
}

int GetTamanhoBaseFonte(int numFonte){
    return CGerenciadorFontes::GetTamanhoBaseFonte(numFonte);
}

int GetFonteDescent(int numFonte){
    return CGerenciadorFontes::GetFonteDescent(numFonte);
}

int GetFonteAscent(int numFonte){
    return CGerenciadorFontes::GetFonteAscent(numFonte);
}

int GetFonteLineSkip(int numFonte){
    return CGerenciadorFontes::GetLineSkip(numFonte);
}

void SubstituiCaractere(char caractere, char *nomeArquivo, int largNova, int x, int y, int altura,int largura,int numFonte){
    CGerenciadorFontes::SubstituiCaracter(caractere,nomeArquivo,largNova,x,y,altura,largura,numFonte);
}

int CriaObjeto(char* nomeArquivo,PIG_Cor *corFundo,int retiraFundo, int idJanela){
    return CGerenciadorObjetos::CriaObjeto(nomeArquivo,corFundo,retiraFundo,idJanela);
}

int CriaObjetoOffScreen(PIG_Cor *corFundo,int retiraFundo){
    return CGerenciadorObjetos::CriaObjetoOffScreen(jogo->offRenderer,corFundo,retiraFundo);
}

void DestroiObjeto(int idObjeto){
    CGerenciadorObjetos::DestroiObjeto(idObjeto);
}

void SetValorIntObjeto(int idObjeto,int indice,int valor){
    CGerenciadorObjetos::SetValorIntObjeto(idObjeto,indice,valor);
}

void SetValorFloatObjeto(int idObjeto,int indice,float valor){
    CGerenciadorObjetos::SetValorFloatObjeto(idObjeto,indice,valor);
}

void SetValorStringObjeto(int idObjeto,int indice,char *valor){
    CGerenciadorObjetos::SetValorStringObjeto(idObjeto,indice,valor);
}

void SetValorIntObjeto(int idObjeto,char *indice,int valor){
    CGerenciadorObjetos::SetValorIntObjeto(idObjeto,indice,valor);
}

void SetValorFloatObjeto(int idObjeto,char *indice,float valor){
    CGerenciadorObjetos::SetValorFloatObjeto(idObjeto,indice,valor);
}

void SetValorStringObjeto(int idObjeto,char *indice,char *valor){
    CGerenciadorObjetos::SetValorStringObjeto(idObjeto,indice,valor);
}

int GetValorIntObjeto(int idObjeto,int indice,int *valor){
    return CGerenciadorObjetos::GetValorIntObjeto(idObjeto,indice,valor);
}

int GetValorFloatObjeto(int idObjeto,int indice,float *valor){
    return CGerenciadorObjetos::GetValorFloatObjeto(idObjeto,indice,valor);
}

int GetValorStringObjeto(int idObjeto,int indice,char *valor){
    return CGerenciadorObjetos::GetValorStringObjeto(idObjeto,indice,valor);
}

int GetValorIntObjeto(int idObjeto,char *indice,int *valor){
    return CGerenciadorObjetos::GetValorIntObjeto(idObjeto,indice,valor);
}

int GetValorFloatObjeto(int idObjeto,char *indice,float *valor){
    return CGerenciadorObjetos::GetValorFloatObjeto(idObjeto,indice,valor);
}

int GetValorStringObjeto(int idObjeto,char *indice,char *valor){
    return CGerenciadorObjetos::GetValorStringObjeto(idObjeto,indice,valor);
}

void GetXYObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    CGerenciadorObjetos::GetPosicaoXY(idObjeto,posicaoX,posicaoY);
}

void MoveObjeto(int idObjeto,int posicaoX,int posicaoY){
    CGerenciadorObjetos::Move(idObjeto,posicaoX,posicaoY);
}

void DeslocaObjeto(int idObjeto,int deltaX,int deltaY){
    CGerenciadorObjetos::Desloca(idObjeto,deltaX,deltaY);
}

void SetAnguloObjeto(int idObjeto, float angulo){
    CGerenciadorObjetos::SetAngulo(idObjeto,angulo);
}

float GetAnguloObjeto(int idObjeto){
    return CGerenciadorObjetos::GetAngulo(idObjeto);
}

void SetPivoObjeto(int idObjeto,int posicaoX,int posicaoY){
    CGerenciadorObjetos::SetPivo(idObjeto,posicaoX,posicaoY);
}

void SetPivoObjeto(int idObjeto,float relX,float relY){
    CGerenciadorObjetos::SetPivo(idObjeto,relX,relY);
}

void GetPivoObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    CGerenciadorObjetos::GetPivo(idObjeto,posicaoX,posicaoY);
}

void SetFlipObjeto(int idObjeto,PIG_Flip valor){
    CGerenciadorObjetos::SetFlip(idObjeto,valor);
}

PIG_Flip GetFlipObjeto(int idObjeto){
    return CGerenciadorObjetos::GetFlip(idObjeto);
}

void SetDimensoesObjeto(int idObjeto, int altura, int largura){
    CGerenciadorObjetos::SetDimensoes(idObjeto,altura,largura);
}

void GetDimensoesObjeto(int idObjeto, int *altura, int *largura){
    CGerenciadorObjetos::GetDimensoes(idObjeto,altura,largura);
}

void GetDimensoesOriginaisObjeto(int idObjeto, int *altura, int *largura){
    CGerenciadorObjetos::GetDimensoesOriginais(idObjeto,altura,largura);
}

void DefineFrameObjeto(int idObjeto, int xBitmap, int yBitmap, int altura, int largura){
    CGerenciadorObjetos::CriaFrame(idObjeto,xBitmap,yBitmap,altura,largura);
}

void SetColoracaoObjeto(int idObjeto, PIG_Cor cor){
    CGerenciadorObjetos::SetColoracao(idObjeto,cor);
}

void SetOpacidadeObjeto(int idObjeto,int valor){
    CGerenciadorObjetos::SetOpacidade(idObjeto,valor);
}

int GetOpacidadeObjeto(int idObjeto){
    return CGerenciadorObjetos::GetOpacidade(idObjeto);
}

void DesenhaObjeto(int idObjeto,int offScreen){
    if (offScreen==0)
    CGerenciadorObjetos::Desenha(idObjeto,NULL);
    else CGerenciadorObjetos::Desenha(idObjeto,jogo->offRenderer);
}

//int TestaColisaoObjetos(int idObjeto1,int idObjeto2){
//    return CGerenciadorObjetos::TestaColisao(idObjeto1,idObjeto2)&&CGerenciadorObjetos::TestaColisao(idObjeto2,idObjeto1);
//}

int TestaColisaoObjetos(int idObjeto1,int idObjeto2){
    if (CGerenciadorObjetos::TestaColisao(idObjeto1, idObjeto2))
        return true;//CGerenciadorObjetos::TestaColisaoPoligono(idObjeto1, idObjeto1);
    return false;
}

void DefineAreaColisao(int id_objeto, int* x, int* y, int quantidadePontos) {
    CGerenciadorObjetos::DefineAreaColisao(id_objeto, x, y, quantidadePontos);
}

PIG_Cor **GetPixelsObjeto(int idObjeto){
    return CGerenciadorObjetos::GetPixels(idObjeto);
}

void AtualizaPixelsObjeto(int idObjeto,int retiraFundo){
    CGerenciadorObjetos::AtualizaPixels(idObjeto,retiraFundo);
}

int CriaGeradorParticulas(int maxParticulas,char* nomeArquivo,int audioCriacao,int audioEncerramento,int idJanela){
    return CGerenciadorParticulas::CriaGeradorParticulas(maxParticulas,nomeArquivo,audioCriacao,audioEncerramento,idJanela);
}

int CriaGeradorParticulasPorAnimacao(int maxParticulas,int idAnimacao,int audioCriacao,int audioEncerramento,int idJanela){
    return CGerenciadorParticulas::CriaGeradorParticulas(maxParticulas,CGerenciadorAnimacoes::GetAnimacao(idAnimacao),audioCriacao,audioEncerramento,idJanela);
}

int CriaGeradorParticulasPorObjeto(int maxParticulas,int idObjeto,int audioCriacao,int audioEncerramento,int idJanela){
    return CGerenciadorParticulas::CriaGeradorParticulas(maxParticulas,CGerenciadorObjetos::GetObjeto(idObjeto),audioCriacao,audioEncerramento,idJanela);
}

void DestroiGeradorParticulas(int idGerador){
    CGerenciadorParticulas::DestroiGeradorParticulas(idGerador);
}

void MoveGeradorParticulas(int idGerador,int posicaoX,int posicaoY){
    CGerenciadorParticulas::Move(idGerador,posicaoX,posicaoY);
}

void DeslocaGeradorParticulas(int idGerador,int deltaX,int deltaY){
    CGerenciadorParticulas::Desloca(idGerador,deltaX,deltaY);
}

void MudaDirecaoParticulas(int idGerador,int valorX,int valorY){
    CGerenciadorParticulas::MudaDirecaoParticulas(idGerador,valorX,valorY);
}

void MudaRotacaoParticulas(int idGerador,float grausPerSec){
    CGerenciadorParticulas::MudaRotacaoParticulas(idGerador,grausPerSec);
}

void MudaCorParticulas(int idGerador,PIG_Cor cor){
    CGerenciadorParticulas::MudaCorParticulas(idGerador,cor);
}

void MudaEscalaParticulas(int idGerador,float escalaInicial,float escalaFinal){
    CGerenciadorParticulas::MudaEscalaParticulas(idGerador,escalaInicial,escalaFinal);
}

void SetPivoParticulas(int idGerador,int posicaoX,int posicaoY){
    CGerenciadorParticulas::MudaEscalaParticulas(idGerador,posicaoX,posicaoY);
}

int CriaParticula(int idGerador,int fadingOut,int minX,int minY,int maxX,int maxY,float maxTempo){
    return CGerenciadorParticulas::CriaParticula(idGerador,fadingOut,minX,minY,maxX,maxY,maxTempo);
}

void MoveParticulas(int idGerador){
    CGerenciadorParticulas::MoveParticulas(idGerador);
}

int QuantidadeParticulasAtivas(int idGerador){
    return CGerenciadorParticulas::GetQtdAtivas(idGerador);
}

void DesenhaParticulas(int idGerador){
    CGerenciadorParticulas::Desenha(idGerador);
}

int ColisaoParticulasObjeto(int idGerador,int idObjeto){
    CObjeto *obj = CGerenciadorObjetos::GetObjeto(idObjeto);
    return CGerenciadorParticulas::Colisao(idGerador,obj);
}

int ColisaoParticulasAnimacao(int idGerador,int idAnimacao){
    CAnimacao *anima = CGerenciadorAnimacoes::GetAnimacao(idAnimacao);
    return CGerenciadorParticulas::Colisao(idGerador,anima);
}

int CriaTimer(int congelado){
    return CGerenciadorTimers::CriaTimer(congelado);
}

float TempoDecorrido(int idTimer){
    return CGerenciadorTimers::GetTempoDecorrido(idTimer);
}

void PausaTimer(int idTimer){
    CGerenciadorTimers::PausaTimer(idTimer);
}

void PausaTudo(){
    CGerenciadorTimers::PausaTodos();
}

void DespausaTimer(int idTimer){
    CGerenciadorTimers::DespausaTimer(idTimer);
}

void DespausaTudo(){
    CGerenciadorTimers::DespausaTodos();
}

void ReiniciaTimer(int idTimer, int congelado){
    CGerenciadorTimers::ReiniciaTimer(idTimer,congelado);
}

void DestroiTimer(int idTimer){
    CGerenciadorTimers::DestroiTimer(idTimer);
}

int CriaAnimacao(char* nomeArquivo,PIG_Cor *corFundo,int retiraFundo,int idJanela){
    return CGerenciadorAnimacoes::CriaAnimacao(nomeArquivo,corFundo,retiraFundo,idJanela);
}

int CriaAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::CriaAnimacao(idAnimacao);
}

void DestroiAnimacao(int idAnimacao){
    CGerenciadorAnimacoes::DestroiAnimacao(idAnimacao);
}

void CriaFrameAnimacao(int idAnimacao,int codigoFrame,int xBitmap,int yBitmap,int altura,int largura){
    CGerenciadorAnimacoes::CriaFrame(idAnimacao,codigoFrame,xBitmap,yBitmap,altura,largura);
}

void CriaModoAnimacao(int idAnimacao,int codigoModo,int loop){
    CGerenciadorAnimacoes::CriaModo(idAnimacao,codigoModo,loop);
}

void InsereFrameAnimacao(int idAnimacao,int codigoModo, int codigoFrame, float tempo, int idAudio){
    CGerenciadorAnimacoes::InsereFrame(idAnimacao,codigoModo,codigoFrame,tempo,idAudio);
}

void MudaModoAnimacao(int idAnimacao,int codigoModo,int indiceFrame,int forcado){
    CGerenciadorAnimacoes::MudaModo(idAnimacao,codigoModo,indiceFrame,forcado);
}

int ColisaoAnimacoes(int idAnimacao1,int idAnimacao2){
    return CGerenciadorAnimacoes::ColisaoAnimacoes(idAnimacao1,idAnimacao2);
}

int ColisaoAnimacaoObjeto(int idAnimacao,int idObjeto){
    CObjeto *obj = CGerenciadorObjetos::GetObjeto(idObjeto);
    return CGerenciadorAnimacoes::ColisaoObjeto(idAnimacao,obj);
}

int DesenhaAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::Desenha(idAnimacao);
}

void MoveAnimacao(int idAnimacao,int x,int y){
    CGerenciadorAnimacoes::Move(idAnimacao,x,y);
}

void DeslocaAnimacao(int idAnimacao,int deltaX,int deltaY){
    CGerenciadorAnimacoes::Desloca(idAnimacao,deltaX,deltaY);
}

void SetOpacidadeAnimacao(int idAnimacao,int valor){
    CGerenciadorAnimacoes::SetOpacidade(idAnimacao,valor);
}

int GetOpacidadeAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::GetOpacidade(idAnimacao);
}

void SetColoracaoAnimacao(int idAnimacao,PIG_Cor cor){
    CGerenciadorAnimacoes::SetColoracao(idAnimacao,cor);
}

void SetFlipAnimacao(int idAnimacao,PIG_Flip valor){
    CGerenciadorAnimacoes::SetFlip(idAnimacao,valor);
}

PIG_Flip GetFlipAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::GetFlip(idAnimacao);
}

void SetAnguloAnimacao(int idAnimacao, float angulo){
    CGerenciadorAnimacoes::SetAngulo(idAnimacao,angulo);
}

float GetAnguloAnimacao(int idAnimacao){
    return CGerenciadorAnimacoes::GetAngulo(idAnimacao);
}

void SetPivoAnimacao(int idAnimacao,int posicaoX,int posicaoY){
    CGerenciadorAnimacoes::SetPivo(idAnimacao,posicaoX,posicaoY);
}

void GetPivoAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    CGerenciadorAnimacoes::GetPivo(idAnimacao,posicaoX,posicaoY);
}

void SetDimensoesAnimacao(int idAnimacao, int altura, int largura){
    CGerenciadorAnimacoes::SetDimensoes(idAnimacao,altura,largura);
}

void GetDimensoesAnimacao(int idAnimacao, int *altura, int *largura){
    CGerenciadorAnimacoes::GetDimensoes(idAnimacao,altura,largura);
}

void SetValorIntAnimacao(int idAnimacao,int indice,int valor){
    CGerenciadorAnimacoes::SetValorIntAnimacao(idAnimacao,indice,valor);
}

void SetValorFloatAnimacao(int idAnimacao,int indice,float valor){
    CGerenciadorAnimacoes::SetValorFloatAnimacao(idAnimacao,indice,valor);
}

void SetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    CGerenciadorAnimacoes::SetValorStringAnimacao(idAnimacao,indice,valor);
}

void SetValorIntAnimacao(int idAnimacao,char *indice,int valor){
    CGerenciadorAnimacoes::SetValorIntAnimacao(idAnimacao,indice,valor);
}

void SetValorFloatAnimacao(int idAnimacao,char *indice,float valor){
    CGerenciadorAnimacoes::SetValorFloatAnimacao(idAnimacao,indice,valor);
}

void SetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    CGerenciadorAnimacoes::SetValorStringAnimacao(idAnimacao,indice,valor);
}

int GetValorIntAnimacao(int idAnimacao,int indice,int *valor){
    return CGerenciadorAnimacoes::GetValorIntAnimacao(idAnimacao,indice,valor);
}

int GetValorFloatAnimacao(int idAnimacao,int indice,float *valor){
    return CGerenciadorAnimacoes::GetValorFloatAnimacao(idAnimacao,indice,valor);
}

int GetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    std::string str;
    bool resp = CGerenciadorAnimacoes::GetValorStringAnimacao(idAnimacao,indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

int GetValorIntAnimacao(int idAnimacao,char *indice,int *valor){
    return CGerenciadorAnimacoes::GetValorIntAnimacao(idAnimacao,indice,valor);
}

int GetValorFloatAnimacao(int idAnimacao,char *indice,float *valor){
    return CGerenciadorAnimacoes::GetValorFloatAnimacao(idAnimacao,indice,valor);
}

int GetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    std::string str;
    bool resp = CGerenciadorAnimacoes::GetValorStringAnimacao(idAnimacao,indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

void GetXYAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    return CGerenciadorAnimacoes::GetPosicaoXY(idAnimacao,posicaoX,posicaoY);
}

int CriaAudio(char *nomeArquivo,int nLoops,int tempoExecucao){
    return CGerenciadorAudios::CriaAudio(nomeArquivo,nLoops,tempoExecucao);
}

void DestroiAudio(int idAudio){
    CGerenciadorAudios::DestroiAudio(idAudio);
}

void CarregaBackground(char *nomeArquivo){
    CGerenciadorAudios::CarregaBackground(nomeArquivo);
}

void PlayBackground(int nVezes){
    CGerenciadorAudios::PlayBackground(nVezes);
}

void StopBackground(){
    CGerenciadorAudios::StopBackground();
}

void PauseBackground(){
    CGerenciadorAudios::PauseBackground();
}

void ResumeBackground(){
    CGerenciadorAudios::ResumeBackground();
}

PIG_StatusAudio GetStatusBackground(){
    return CGerenciadorAudios::GetStatusBackground();
}

void SetVolumeBackground(int valor){
    CGerenciadorAudios::SetVolumeBackground(valor);
}

int GetVolumeBackground(){
    return CGerenciadorAudios::GetVolumeBackground();
}

void SetVolume(int idAudio,int volume){
    CGerenciadorAudios::SetVolume(idAudio,volume);
}

int GetVolume(int idAudio){
    return CGerenciadorAudios::GetVolume(idAudio);
}

void SetVolumeTudo(int volume){
    CGerenciadorAudios::SetVolumeTudo(volume);
}

void PlayAudio(int idAudio){
    CGerenciadorAudios::Play(idAudio);
}

void PauseAudio(int idAudio){
    CGerenciadorAudios::Pause(idAudio);
}

void ResumeAudio(int idAudio){
    CGerenciadorAudios::Resume(idAudio);
}

void StopAudio(int idAudio){
    CGerenciadorAudios::Stop(idAudio);
}

PIG_StatusAudio GetStatusAudio(int idAudio){
    return CGerenciadorAudios::GetStatus(idAudio);
}

void StopTudoAudio(){
    CGerenciadorAudios::StopTudo();
}

void PauseTudoAudio(){
    CGerenciadorAudios::PauseTudo();
}

void ResumeTudoAudio(){
    CGerenciadorAudios::ResumeTudo();
}

int CriaSocketCliente(char *hostname, int porta, int maxBytesPacote){
    return CGerenciadorSockets::CriaCliente(hostname,porta,maxBytesPacote);
}

int CriaSocketServidor(int maxClientes, int porta, int maxBytesPacote){
    return CGerenciadorSockets::CriaServidor(maxClientes,porta,maxBytesPacote);
}

int CriaSocketUDP(int porta){
    return CGerenciadorSockets::CriaSocketUDP(porta);
}

void DestroiSocketCliente(int idSocket){
    CGerenciadorSockets::DestroiCliente(idSocket);
}

void DestroiSocketServidor(int idSocket){
    CGerenciadorSockets::DestroiServidor(idSocket);
}

void DestroiSocketUDP(int idSocket){
    CGerenciadorSockets::DestroiSocketUDP(idSocket);
}

int GetAtivoSocketCliente(int idSocket){
    return CGerenciadorSockets::GetAtivoCliente(idSocket);
}

int GetAtivoSocketServidor(int idSocket){
    return CGerenciadorSockets::GetAtivoServidor(idSocket);
}

int GetAtivoSocketUDP(int idSocket){
    return CGerenciadorSockets::GetAtivoSocketUDP(idSocket);
}

long GetBytesEnviadosSocketCliente(int idSocket){
    return CGerenciadorSockets::GetBytesEnviadosCliente(idSocket);
}

long GetBytesRecebidosSocketCliente(int idSocket){
    return CGerenciadorSockets::GetBytesRecebidosCliente(idSocket);
}

long GetPacotesEnviadosSocketCliente(int idSocket){
    return CGerenciadorSockets::GetPacotesEnviadosCliente(idSocket);
}

long GetPacotesRecebidosSocketCliente(int idSocket){
    return CGerenciadorSockets::GetPacotesRecebidosCliente(idSocket);
}

long GetTempoUltimoRecebidoSocketCliente(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoRecebidoCliente(idSocket);
}

long GetTempoUltimoEnviadoSocketCliente(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoEnviadoCliente(idSocket);
}

long GetBytesEnviadosSocketServidor(int idSocket){
    return CGerenciadorSockets::GetBytesEnviadosServidor(idSocket);
}

long GetBytesRecebidosSocketServidor(int idSocket){
    return CGerenciadorSockets::GetBytesRecebidosServidor(idSocket);
}

long GetPacotesEnviadosSocketServidor(int idSocket){
    return CGerenciadorSockets::GetPacotesEnviadosCliente(idSocket);
}

long GetPacotesRecebidosSocketServidor(int idSocket){
    return CGerenciadorSockets::GetPacotesRecebidosCliente(idSocket);
}

long GetTempoUltimoRecebidoSocketServidor(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoRecebidoServidor(idSocket);
}

long GetTempoUltimoEnviadoSocketServidor(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoEnviadoServidor(idSocket);
}

long GetBytesEnviadosSocketUDP(int idSocket){
    return CGerenciadorSockets::GetBytesEnviadosSocketUDP(idSocket);
}

long GetBytesRecebidosSocketUDP(int idSocket){
    return CGerenciadorSockets::GetBytesRecebidosSocketUDP(idSocket);
}

long GetPacotesEnviadosSocketUDP(int idSocket){
    return CGerenciadorSockets::GetPacotesEnviadosSocketUDP(idSocket);
}

long GetPacotesRecebidosSocketUDP(int idSocket){
    return CGerenciadorSockets::GetPacotesRecebidosSocketUDP(idSocket);
}

long GetTempoUltimoRecebidoSocketUDP(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoRecebidoSocketUDP(idSocket);
}

long GetTempoUltimoEnviadoSocketUDP(int idSocket){
    return CGerenciadorSockets::GetTempoUltimoEnviadoSocketUDP(idSocket);
}

int GetPortaRemotaSocketCliente(int idSocket){
    return CGerenciadorSockets::GetPortaRemotaCliente(idSocket);
}

int GetPortaLocalSocketServidor(int idSocket){
    return CGerenciadorSockets::GetPortaLocalServidor(idSocket);
}

int GetPortaLocalSocketUDP(int idSocket){
    return CGerenciadorSockets::GetPortaLocalSocketUDP(idSocket);
}

void GetHostRemotoSocketCliente(int idSocket,char *hostname){
    std::string resp = CGerenciadorSockets::GetHostRemotoCliente(idSocket);
    strcpy(hostname,resp.c_str());
}

void GetHostLocalSocketCliente(int idSocket,char *hostname){
    std::string resp = CGerenciadorSockets::GetHostLocalCliente(idSocket);
    strcpy(hostname,resp.c_str());
}

void GetHostLocalSocketServidor(int idSocket,char *hostname){
    std::string resp = CGerenciadorSockets::GetHostLocalServidor(idSocket);
    strcpy(hostname,resp.c_str());
}

void GetHostLocalSocketUDP(int idSocket,char *hostname){
    std::string resp = CGerenciadorSockets::GetHostLocalSocketUDP(idSocket);
    strcpy(hostname,resp.c_str());
}

int GetTamanhoPacoteSocketCliente(int idSocket){
    return CGerenciadorSockets::GetTamanhoPacoteCliente(idSocket);
}

int GetTamanhoPacoteSocketServidor(int idSocket){
    return CGerenciadorSockets::GetTamanhoPacoteServidor(idSocket);
}

int GetMaximoConexoesSocketServidor(int idSocket){
    return CGerenciadorSockets::GetMaximoConexoesServidor(idSocket);
}

int GetQuantidadeConexoesSocketServidor(int idSocket){
    return CGerenciadorSockets::GetQuantidadeConexoes(idSocket);
}

int EnviaDadosSocketCliente(int idSocket,void *buffer, int tamanhoBuffer){
    return CGerenciadorSockets::EnviaDadosCliente(idSocket,buffer,tamanhoBuffer);
}

int EnviaDadosSocketServidor(int idSocket,int socketSecundario,void *buffer, int tamanhoBuffer){
    return CGerenciadorSockets::EnviaDadosServidor(idSocket,socketSecundario,buffer,tamanhoBuffer);
}

int EnviaDadosSocketUDP(int idSocket,void *buffer,int tamanhoBuffer, char *hostRemoto, int porta){
    return CGerenciadorSockets::EnviaDadosSocketUDP(idSocket,buffer,tamanhoBuffer,hostRemoto,porta);
}

int CriaVideo(char *nomeArquivo,int idJanela){
    return CGerenciadorVideos::CriaVideo(nomeArquivo,idJanela);
}

void DestroiVideo(int idVideo){
    CGerenciadorVideos::DestroiVideo(idVideo);
}

void SetSeekVideo(int idVideo, double incremento){
    CGerenciadorVideos::SetSeek(idVideo,incremento);
}

void PlayVideo(int idVideo){
    CGerenciadorVideos::Play(idVideo);
}

void StopVideo(int idVideo){
    CGerenciadorVideos::Stop(idVideo);
}

void PauseVideo(int idVideo){
    CGerenciadorVideos::Pause(idVideo);
}

void ResumeVideo(int idVideo){
    CGerenciadorVideos::Resume(idVideo);
}

int DesenhaVideo(int idVideo){
    CGerenciadorVideos::Desenha(idVideo);
}

void SetVolumeVideo(int idVideo, double valor){
    CGerenciadorVideos::SetVolume(idVideo,valor);
}

double GetVolumeVideo(int idVideo){
    return CGerenciadorVideos::GetVolume(idVideo);
}

void GetNomeArquivoVideo(int idVideo, char *nome){
    std::string resp = CGerenciadorVideos::GetNomeArquivo(idVideo);
    strcpy(nome,resp.c_str());
}

double GetTempoAtualVideo(int idVideo){
    return CGerenciadorVideos::GetTempoAtual(idVideo);
}

void GetTempoAtualVideo(int idVideo, char *str){
    std::string resp = CGerenciadorVideos::GetTempoAtualString(idVideo);
    strcpy(str,resp.c_str());
}

double GetTempoTotalVideo(int idVideo){
    return CGerenciadorVideos::GetTempoTotal(idVideo);
}

void GetTempoTotalVideo(int idVideo, char *str){
    std::string resp = CGerenciadorVideos::GetTempoTotalString(idVideo);
    strcpy(str,resp.c_str());
}

double GetTempoFrameVideo(int idVideo){
    return CGerenciadorVideos::GetTempoFrame(idVideo);
}

double GetFPSVideo(int idVideo){
    return CGerenciadorVideos::GetFPS(idVideo);
}

void SetAnguloVideo(int idVideo, float angulo){
    CGerenciadorVideos::SetAngulo(idVideo,angulo);
}

double GetAnguloVideo(int idVideo){
    return CGerenciadorVideos::GetAngulo(idVideo);
}

void SetFlipVideo(int idVideo, PIG_Flip valor){
    CGerenciadorVideos::SetFlip(idVideo,valor);
}

PIG_Flip GetFlipVideo(int idVideo){
    return CGerenciadorVideos::GetFlip(idVideo);
}

void SetPivoVideo(int idVideo, int posicaoX,int posicaoY){
    CGerenciadorVideos::SetPivo(idVideo,posicaoX,posicaoY);
}

void SetPivoVideo(int idVideo, float relX,float relY){
    CGerenciadorVideos::SetPivo(idVideo,relX,relY);
}

void GetPivoVideo(int idVideo, int *posicaoX,int *posicaoY){
    CGerenciadorVideos::GetPivo(idVideo,*posicaoX,*posicaoY);
}

void MoveVideo(int idVideo,int posicaoX,int posicaoY){
    CGerenciadorVideos::Move(idVideo,posicaoX,posicaoY);
}

void SetDimensoesVideo(int idVideo, int altura,int largura){
    CGerenciadorVideos::SetDimensoes(idVideo,altura,largura);
}

void GetDimensoesVideo(int idVideo, int *altura, int *largura){
    CGerenciadorVideos::GetDimensoes(idVideo,*altura,*largura);
}

void GetDimensoesOriginaisVideo(int idVideo, int *altura, int *largura){
    CGerenciadorVideos::GetDimensoesOriginais(idVideo,*altura,*largura);
}

void OcupaJanelaInteiraVideo(int idVideo){
    CGerenciadorVideos::OcupaJanelaInteira(idVideo);
}

void UsaResolucaoOriginalVideo(int idVideo){
    CGerenciadorVideos::UsaResolucaoOriginal(idVideo);
}

void SetColoracaoVideo(int idVideo, PIG_Cor cor){
    CGerenciadorVideos::SetColoracao(idVideo,cor);
}

void SetOpacidadeVideo(int idVideo, int valor){
    CGerenciadorVideos::SetOpacidade(idVideo,valor);
}

int GetOpacidadeVideo(int idVideo){
    return CGerenciadorVideos::GetOpacidade(idVideo);
}
