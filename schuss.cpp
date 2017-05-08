#include "schuss.h"
#include "alien.h"
#include "explosion.h"

schuss::schuss()
{
    //ctor
}

schuss::~schuss()
{
    //dtor
}

void schuss::bewegen(int schussgeschwSpieler)
{
    mY=mY-schussgeschwSpieler;
}

bool schuss::trefferpruefen(alien* ZuPruefenderAlien,explosion* NaechsteExplosion,int* anzahlExplosion)
{

if ( (mX>ZuPruefenderAlien->getX()) && (mX+4<ZuPruefenderAlien->getX()+30) && (mY>ZuPruefenderAlien->getY()) & (mY+9<ZuPruefenderAlien->getY()+30) )
            {               ///Treffer erkennen
                if (*anzahlExplosion<10)
                {
                NaechsteExplosion->x=mX-20;
                NaechsteExplosion->y=mY-20;
                NaechsteExplosion->laufzeit=0;
                (*anzahlExplosion)++;
                return true;
                }
            return false;
            }
}
