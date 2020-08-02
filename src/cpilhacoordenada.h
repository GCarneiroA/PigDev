
#ifndef CPILHACOORDENADA_H
#define CPILHACOORDENADA_H

class CPilhaCoordenada
{
public:
    CPilhaCoordenada();
    void Empilha(int x,int y);
    int Desempilha(int &x,int &y);
    ~CPilhaCoordenada();

private:
    typedef struct Ponto{
        int x,y;
        struct Ponto *prox;
    } Ponto;

    Ponto *ini;
};

#endif
