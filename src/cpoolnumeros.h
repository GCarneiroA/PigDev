
#ifndef CPOOLNUMEROS_H
#define CPOOLNUMEROS_H

class CPoolNumeros
{
    typedef struct xxx{
        int valor;
        struct xxx *prox;
    } Elem;

public:

    int qtdTotal;

    CPoolNumeros(int qtd);
    ~CPoolNumeros();
    int RetiraLivre();
    void DevolveUsado(int valor);
    void ImprimeLivres();
    void ImprimeUsados();

private:

    Elem *livres;
    int *usados;

};

#endif
