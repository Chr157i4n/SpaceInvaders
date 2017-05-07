#include "schuss.h"

schuss::schuss()
{
    //ctor
}

schuss::~schuss()
{
    //dtor
}

schuss::bewegen(int schussgeschwSpieler)
{
    y=y-schussgeschwSpieler;
}
