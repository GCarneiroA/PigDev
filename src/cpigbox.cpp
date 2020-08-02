
#include "cpigbox.h"

CPigBox::CPigBox(int idComponente, int posX, int posY, int largura, std::string nomeArqFundo, std::string nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo,int janela)
    : CPigComponente(idComponente,posX,posY,0,largura,nomeArqFundo,retiraFundo,janela)
{
    IniciaBase(alturaItem, larguraItem, espacoVertical, nomeArqItem);
}

CPigBox::CPigBox(int idComponente, int posX, int posY, int largura, std::string nomeArqItem,int alturaItem, int larguraItem, int espacoVertical,int janela)
    : CPigComponente(idComponente,posX,posY,0,largura,janela)
{
    IniciaBase(alturaItem, larguraItem, espacoVertical, nomeArqItem);
}

CPigBox::~CPigBox(){
    for (CPigItemCheck* i: itens)
        delete i;
    itens.clear();
}

void CPigBox::AlinhaDireita(){
    if (posItens==PIG_COMPONENTE_DIR_CENTRO){//se os labels est�o � direita do bot�es, inverte
        for (CPigItemCheck* i: itens)
            i->AlinhaDireita(larg);
        posItens = PIG_COMPONENTE_ESQ_CENTRO;
    }
}

void CPigBox::AlinhaEsquerda(){
    if (posItens==PIG_COMPONENTE_ESQ_CENTRO){//se os labels est�o � esquerda dos bot�es, inverte
        for (CPigItemCheck* i: itens)
            i->AlinhaEsquerda(larg);
        posItens = PIG_COMPONENTE_DIR_CENTRO;
    }
}

int CPigBox::Desenha(){
    if (estado==COMPONENTE_INVISIVEL) return 0;

    if (text){//se tiver imagem de fundo
        SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,NULL,flip);
    }
    DesenhaLabel();

    for (CPigItemCheck* i: itens)
        i->Desenha();

    return 1;
}

int CPigBox::GetMarcadoItem(int indice){
    if (indice<0||indice>=itens.size()) return -1;
    return itens[indice]->GetMarcado();
}

int CPigBox::SetAudioItem(int indice, int audio){
    if (indice<0||indice>=itens.size()) return -1;
    itens[indice]->SetAudio(audio);
    return 1;
}

int CPigBox::GetHabilitadoItem(int indice){
    if (indice<0||indice>=itens.size()) return -1;
    return itens[indice]->GetHabilitado();
}

int CPigBox::SetHabilitadoItem(int indice, bool habilitado){
    if (indice<0||indice>=itens.size()) return -1;
    itens[indice]->SetHabilitado(habilitado);
    return 1;
}

int CPigBox::SetHabilitado(bool habilitado){
    if(habilitado)
        DefineEstado(COMPONENTE_NORMAL);
    else
        DefineEstado(COMPONENTE_DESABILITADO);

    for(CPigItemCheck *i :itens)
        i->SetHabilitado(habilitado);

    return 1;
}

int CPigBox::SetLabelIndice(int indice, std::string label){
    if (indice<0||indice>=itens.size()) return -1;
    itens[indice]->SetLabel(label);
    return 1;
}

void CPigBox::SetFonteHint(int fonte) {
    for (CPigItemCheck* i: itens)
        i->SetFonteHint(fonte);
}

void CPigBox::SetAudio(int audio) {
    audioComponente = audio;
    for (CPigItemCheck* i: itens)
        i->SetAudio(audio);
}

void CPigBox::Move(int nx,int ny){
    CVisual::Move(nx,ny);
    for(int i=0;i<itens.size();i++)
        itens[i]->Move(nx , ny + (espacoLinha + altItem) * i);
}

int CPigBox::OnMouseOn()
{
    return 1;
} //o evento � repassado para cada item

int CPigBox::OnMouseOff()
{
    return 1;
} //oevento � repassado para cada item

//define o estado global de todos os itens
void CPigBox::DefineEstado(PIG_EstadoComponente estadoComponente){
    if(estadoComponente == COMPONENTE_DESABILITADO)
        for (CPigItemCheck* i: itens)
            i->DefineEstado(COMPONENTE_DESABILITADO);

    if(estadoComponente == COMPONENTE_NORMAL)
        for (CPigItemCheck* i: itens)
            i->DefineEstado(COMPONENTE_NORMAL);
}

void CPigBox::IniciaBase(int alturaItem, int larguraItem, int espacoVertical, std::string nomeArqItem){
    SetPosicaoPadraoLabel(PIG_COMPONENTE_CIMA_CENTRO);//posi��o padr�o do label
    nomeImgItem = nomeArqItem;
    largItem = larguraItem;
    altItem = alturaItem;
    espacoLinha = espacoVertical;
    posItens = PIG_COMPONENTE_DIR_CENTRO;//s� pode ser posicionamento � esquerda ou � direita
}

