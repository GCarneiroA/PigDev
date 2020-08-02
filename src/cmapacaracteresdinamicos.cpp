
#include "cmapacaracteresdinamicos.h"

#include "cgerenciadorjanelas.h"

#include "pigfuncoesbasicas.h"

    //construtor com o nome do arquivo da fonte, o tamanha e a janela
    CMapaCaracteresDinamicos::CMapaCaracteresDinamicos(char *nomeFonte, int tamanhoFonte, int idJanela)
        : CMapaCaracteres()
    {
        IniciaBase(nomeFonte,tamanhoFonte,idJanela, -1);

        for (int estilo=0;estilo<PIG_TOTALESTILOS;estilo++)
            CriaLetrasSurface(estilo, 0, BRANCO, NULL, BRANCO);

        SDL_SetRenderTarget(render, NULL);
    }

    //escreve uma string j� formatada, alinhada com o ponto x,y e o par�metro pos
    void CMapaCaracteresDinamicos::Escreve(CPigStringFormatada formatada,int x,int y,PIG_PosTexto pos,float ang)
    {
        int delta = 0;
        switch(pos){
        case CPIG_TEXTO_ESQUERDA:
            break;
        case CPIG_TEXTO_DIREITA:
            //EscreveStringEsquerda(texto,x-formatada.LargTotalPixels(),y,ang,formatada.LargTotalPixels());break;
            x -= formatada.LargTotalPixels();delta = formatada.LargTotalPixels();break;
        case CPIG_TEXTO_CENTRO:
            //EscreveStringEsquerda(texto,x-formatada.LargTotalPixels()/2,y,ang,formatada.LargTotalPixels()/2);break;
            x -= formatada.LargTotalPixels()/2;delta = formatada.LargTotalPixels()/2;break;
        }

        SDL_Rect rectDestino;
        rectDestino.x = x;
        int altJanela = CGerenciadorJanelas::GetJanela(janela)->GetAltura();
        //rectDestino.y = CGerenciadorJanelas::GetJanela(janela)->GetAltura()-y-tamFonte;
        PIG_Cor corAtual = BRANCO;
        PIG_Estilo estiloAtual = ESTILO_NORMAL;
        SDL_Point ponto = {delta,tamFonte};

        for (int i=0;i<formatada.size();i++){
            Uint16 aux = formatada.GetLetra(i);
            aux = aux %256;
            if (aux-PRIMEIRO_CAR<0) continue;
            corAtual = formatada.GetCor(i);
            estiloAtual = formatada.GetEstilo(i);

            SDL_SetTextureColorMod(glyphsT[estiloAtual][aux-PRIMEIRO_CAR],corAtual.r,corAtual.g,corAtual.b);

            rectDestino.w = larguraLetra[estiloAtual][aux-PRIMEIRO_CAR];
            rectDestino.h = tamFonte+alturaExtra[estiloAtual][aux-PRIMEIRO_CAR];
            rectDestino.y = altJanela-y-rectDestino.h;

            SDL_RenderCopyEx(render,glyphsT[estiloAtual][aux-PRIMEIRO_CAR],NULL,&rectDestino,-ang,&ponto,FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }
    }

    //escreve ums string normal, alinha com o ponto x,y e o par�metro pos
    void CMapaCaracteresDinamicos::Escreve(std::string texto,int x,int y,PIG_PosTexto pos,float ang)
    {
        if (texto=="") return;
        CPigStringFormatada formatada = Processa(texto);
        Escreve(formatada,x,y,pos,ang);
    }

    //escreve uma string longa (m�ltiplas linhas), incluindo formata��o interna, alinhada de acordo com o ponto x,y e o par�metro pos
    void CMapaCaracteresDinamicos::EscreveLonga(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,PIG_PosTexto pos,float angulo) 
    {
        if (texto=="") return;
        CPigStringFormatada formatada = Processa(texto);
        //formatada.Print();
        std::vector<CPigStringFormatada> linhas = formatada.ExtraiLinhas(largMax,PigDelimitadores);
        EscreveLonga(linhas,x,y,espacoEntreLinhas,pos,angulo);
        linhas.clear();
        formatada.Clear();
    }

    //escreve uma string longa (m�ltiplas linhas), com formata��o j� processada e fornecida, alinhada de acordo com o ponto x,y e o par�metro pos
    void CMapaCaracteresDinamicos::EscreveLonga(std::vector<CPigStringFormatada> linhas, int x, int y, int espacoEntreLinhas,PIG_PosTexto pos,float angulo)
    {
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            Escreve(linhas[k],x,yTotal,pos,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    //retorna a largura em pixels da string fornecida (faz a formata��o internamente)
    int CMapaCaracteresDinamicos::GetLarguraPixelsString(std::string texto)
    {
        if (texto=="") return 0;
        CPigStringFormatada formatada = Processa(texto);
        int resp = formatada.LargTotalPixels();
        formatada.Clear();
        return resp;
    }

    //retorna as linhas j� formatadas e organizadas pela largura m�xima fornecida
    std::vector<CPigStringFormatada> CMapaCaracteresDinamicos::ExtraiLinhas(std::string texto, int largMax)
    {
        CPigStringFormatada formatada = Processa(texto);
        std::vector<CPigStringFormatada> linhas = formatada.ExtraiLinhas(largMax,PigDelimitadores);
        formatada.Clear();
        return linhas;
    }


    //processa uma string para transform�-la em StringFormatada
    CPigStringFormatada CMapaCaracteresDinamicos::Processa(std::string textoOrig)
    {
        CPigStringFormatada resp;
        PIG_Cor cor = BRANCO;
        PIG_Estilo estilo = ESTILO_NORMAL;
        int larguraTotal = 0;
        int estado = 0;//estado atual da m�quinda de estados
        int i = 0;

        std::vector<PIG_Cor> pilhaCor;
        std::vector<PIG_Estilo> pilhaEstilo;
        pilhaCor.push_back(cor);
        pilhaEstilo.push_back(estilo);

        Uint16 letra,letraAnt;

        while (i<textoOrig.size()){
            letraAnt = letra;
            letra = textoOrig[i];
            letra = letra %256;

            switch (estado){
            case 0://estado sem formatacao
                if (letra == '<'){//alerta de entrada de formatacao
                   estado = 1;
                }else if (letra=='@'){//alerta de sa�da de cor
                    estado = 3;
                }else if (letra==PIG_SIMBOLO_NEGRITO||letra==PIG_SIMBOLO_ITALICO||letra==PIG_SIMBOLO_SUBLINHADO||letra==PIG_SIMBOLO_CORTADO){//alerta de sa�da de negrito, it�lico, underline ou strike
                    estado = 4;
                }else{
                    larguraTotal += larguraLetra[estilo][letra-PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                break;
            case 1://alerta para inicio de formatacao
                if (letra == '@'){//realmente � entrada de cor
                    estado = 2;
                }else if (letra == PIG_SIMBOLO_NEGRITO){//negrito
                    estilo |= ESTILO_NEGRITO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_ITALICO){
                    estilo |= ESTILO_ITALICO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_SUBLINHADO){
                    estilo |= ESTILO_SUBLINHADO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_CORTADO){
                    estilo |= ESTILO_CORTADO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else{//n�o � entrada de cor nem de formatacao de estilo
                    larguraTotal += larguraLetra[estilo][letraAnt-PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);

                    estado = 0;
                }
                break;
            case 2://reconhecimento da cor
                char stringCor[11];
                strncpy(stringCor,&textoOrig[i],10); //pega os caracteres em hexadecimal (ex: 0xffa64312)
                stringCor[10]='\0';

                i+=9;//avan�a os outros 9 caracteres
                cor = PIGCriaCor(stringCor);//converte para cor
                pilhaCor.push_back(cor);
                estado = 0;
                break;
            case 3://alerta para saida de cor
                if (letra == '>'){//realmente sa�da da cor
                    pilhaCor.pop_back();
                    if (pilhaCor.size()>1)//tira a cor da pilha e pega a de baixo
                        cor = pilhaCor[pilhaCor.size()-1];
                    else cor = BRANCO;
                }else{//n�o � sa�da de cor
                    larguraTotal += larguraLetra[estilo][letraAnt-PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                estado = 0;
                break;
            case 4://saida de negrito, it�lico, underline ou strike
                if (letra=='>'){
                    pilhaEstilo.pop_back();
                    if (pilhaEstilo.size()>1)//tira a cor da pilha e pega a de baixo
                        estilo = pilhaEstilo[pilhaEstilo.size()-1];
                    else estilo = ESTILO_NORMAL;
                }else{//n�o � sa�da de cor
                    larguraTotal += larguraLetra[estilo][letraAnt-PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                estado = 0;
                break;
            }
            i++;
        }
        //system("pause");
        pilhaCor.clear();
        pilhaEstilo.clear();

        return resp;
    }
