#ifndef CPIGFORM_H
#define CPIGFORM_H

#include "cpigcomponente.h"
#include "cpigbotao.h"
#include "cpigscrollbar.h"
#include "cpigcaixatexto.h"
#include "cpigcampotextoesenha.h"
#include "cpigareadetexto.h"
#include "cpigitemcheck.h"
#include "cpigbox.h"
#include "cpigradiobox.h"
#include "cpigcheckbox.h"
#include "cpigitemlista.h"
#include "cpiglista.h"
#include "cpigdropdown.h"
#include "cpiggauge.h"
#include "cpiggaugecircular.h"

#include "tipos_pig.h"

class CPigForm
{
private:
    int id;
    int x,y,alt,larg;

public:
    CPigForm(int idForm, int xForm, int yForm, int altForm, int largForm);
    ~CPigForm();
    int TrataEvento(PIG_Evento evento);
    int Desenha();
};

#endif // CPIGFORM_H
