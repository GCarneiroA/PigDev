class CPigCheckBox: public CPigComponente{

private:

int largItem,altItem;//altura e largura da imagem de cada item
char nomeImgItem[80];//nome da imagem de cada item
int espacoLinha; //espa�o vertical entre os itens
PIG_PosicaoComponente posItens;
std::vector <CPigItemCheck*> itens;

void IniciaBase(int alturaItem, int larguraItem, int espacoVertical, char *nomeArqItem){
    SetPosicaoPadraoLabel(COMPONENTE_CIMA);//posi��o padr�o do label
    strcpy(nomeImgItem,nomeArqItem);
    largItem = larguraItem;
    altItem = alturaItem;
    espacoLinha = espacoVertical;
    posItens = COMPONENTE_DIREITA;//s� pode ser posicionamento � esquerda ou � direita
}

public:

CPigCheckBox(int idComponente, int posX, int posY, int largura, char *nomeArqFundo, char *nomeArqItem, int alturaItem, int larguraItem, int espacoVertical, int retiraFundo=1):
    CPigComponente(idComponente,posX,posY,0,largura,nomeArqFundo,retiraFundo){
    IniciaBase(alturaItem, larguraItem, espacoVertical, nomeArqItem);
}

CPigCheckBox(int idComponente, int posX, int posY, int largura, char *nomeArqItem,int alturaItem, int larguraItem, int espacoVertical):
    CPigComponente(idComponente,posX,posY,0,largura){
    IniciaBase(alturaItem, larguraItem, espacoVertical, nomeArqItem);
}

~CPigCheckBox(){
    for (CPigItemCheck* x: itens)
        delete x;
    itens.clear();
}

void CriaItem(char *itemLabel, bool itemMarcado, bool itemHabilitado, int audio=-1, char *hintMsg=NULL, int retiraFundo=1,int janela=0){
    CPigItemCheck *item = new CPigItemCheck(itens.size(),x,y+(espacoLinha)*(itens.size()),altItem,largItem,larg,nomeImgItem,itemLabel,retiraFundo,janela);
    itens.push_back(item);
    alt += espacoLinha;
    SetDimensoes(alt,larg);
    item->SetHint(hintMsg);
    if (audio==-1)
        audio = audioComponente;//audio padrao do checkbox
    item->SetAudio(audio);
    item->SetMarcado(itemMarcado);
    item->SetHabilitado(itemHabilitado);
}

void AlinhaDireita(){
    if (posItens==COMPONENTE_DIREITA){//se os labels est�o � direita do bot�es, inverte
        for (CPigItemCheck* x: itens)
            x->AlinhaDireita();
        posItens = COMPONENTE_ESQUERDA;
    }
}

void AlinhaEsquerda(){
    if (posItens==COMPONENTE_ESQUERDA){//se os labels est�o � esquerda dos bot�es, inverte
        for (CPigItemCheck* x: itens)
            x->AlinhaEsquerda();
        posItens = COMPONENTE_DIREITA;
    }
}

int Desenha(){
    if (estado==COMPONENTE_INVISIVEL) return 0;

    if (text){//se tiver imagem de fundo
        SDL_RenderCopyEx(renderer,text,NULL,&dest,-angulo,NULL,flip);
    }
    DesenhaLabel();

    for (CPigItemCheck* x: itens)
        x->Desenha();

    return 1;
}

int TrataEvento(PIG_Evento evento){
    int resp = 0;
    for (CPigItemCheck* x: itens)
        resp += x->TrataEvento(evento);
     return resp;
}

int GetMarcado(int indice){
    return itens[indice]->GetMarcado();
}

int SetMarcado(int indice, bool marcado){
    if (indice<0||indice>=itens.size()) return 0;
    itens[indice]->SetMarcado(marcado);
    return 1;
}

int SetAudio(int indice, int audio){
    if (indice<0||indice>=itens.size()) return 0;
    itens[indice]->SetAudio(audio);
    return 1;
}

int GetHabilitado(int indice){
    return itens[indice]->GetHabilitado();
}

int SetHabilitado(int indice, bool habilitado){
    if (indice<0||indice>=itens.size()) return 0;
    if (habilitado)
        itens[indice]->DefineEstado(COMPONENTE_NORMAL);
    else itens[indice]->DefineEstado(COMPONENTE_DESABILITADO);
    return 1;
}

int SetLabelIndice(int indice, char *label){
    if (indice<0||indice>=itens.size()) return 0;
    itens[indice]->SetLabel(label);
    return 1;
}

void SetFonteHint(int fonte) override{
    for (CPigItemCheck* x: itens)
        x->SetFonteHint(fonte);
}

void SetAudio(int audio) override{
    audioComponente = audio;
    for (CPigItemCheck* x: itens)
        x->SetAudio(audio);
}

int OnMouseOn(){return 1;} //o evento � repassado para cada item

int OnMouseOff(){return 1;} //oevento � repassado para cada item

void DefineEstado(PIG_EstadoComponente estadoComponente){
    //quando for definido como desabilitado, desabilita tudo

    //quando for definidio como habilitado, habilita tudo

    //outros estados n�o fazem sentido
}

};
