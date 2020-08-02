
#include "cpigcursor.h"

CPIGCursor::CPIGCursor(std::string nomeArquivo, int retiraFundo, int idJanela)
    : CVisual(nomeArquivo, retiraFundo, NULL, idJanela)
{
}

void CPIGCursor::Desenha()
{
    SDL_RenderCopy(renderer, text, NULL, &dest);
}
