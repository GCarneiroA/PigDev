
#ifndef CGERADORPOLIGONOS_H
#define CGERADORPOLIGONOS_H

#include "tipos_pig.h"

class COffscreenRenderer;

class CGeradorPoligono
{
public:
    CGeradorPoligono();
    ~CGeradorPoligono();
    void GeraPoligonoRegular(int raio, int lados, PIG_Cor cor);
    void GeraRetanguloChanfrado(int altura, int largura, int chanfro, PIG_Cor cor);
    void GeraEstrela(int raio,int pontas, PIG_Cor cor);
    void GeraCirculoAberto(int raio, int angulo, PIG_Cor cor);
private:
    COffscreenRenderer *off;

};

#endif
