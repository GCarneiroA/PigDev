
#include "cpigform.h"


CPigForm::CPigForm(int idForm, int xForm, int yForm, int altForm, int largForm)
{
    id = idForm;
    x = xForm;
    y = yForm;
    alt = altForm;
    larg = largForm;
}

CPigForm::~CPigForm()
{
}

int CPigForm::TrataEvento(PIG_Evento evento)
{
    return 0;
}

int CPigForm::Desenha()
{
    return 0;
}
