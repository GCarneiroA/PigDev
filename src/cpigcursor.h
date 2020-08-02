#ifndef CPIGCURSOR_H
#define CPIGCURSOR_H

#include "cvisual.h"

class CPIGCursor : public CVisual
{
public:
    CPIGCursor(std::string nomeArquivo, int retiraFundo, int idJanela);
    void Desenha();
};

#endif // CPIGCURSOR_H
