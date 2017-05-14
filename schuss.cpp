#include "schuss.h"
#include "alien.h"
#include "explosion.h"
#include "spiel.h"
#include "spieler.h"

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

bool schuss::trefferpruefen(alien* ZuPruefenderAlien,explosion* NaechsteExplosion,spiel* Spiel,spieler* Spieler)
{

if ( (mX>ZuPruefenderAlien->getX()) && (mX+4<ZuPruefenderAlien->getX()+30) && (mY>ZuPruefenderAlien->getY()) & (mY+9<ZuPruefenderAlien->getY()+30) )
            {               ///Treffer erkennen
                if (Spiel->anzahlExplosion<10)
                {
                NaechsteExplosion->x=mX-20;
                NaechsteExplosion->y=mY-20;
                NaechsteExplosion->laufzeit=0;
                (Spiel->anzahlExplosion)++;

                }

                if (Spiel->isGameRunning())
                {Spiel->addPunkte(Spieler);}               ///Punkte hinzufügen

            return true;
            }
    return false;
}
