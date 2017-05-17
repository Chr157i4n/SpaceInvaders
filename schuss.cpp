#include "schuss.h"
#include "alien.h"
#include "explosion.h"
#include "spiel.h"
#include "spieler.h"

schuss::schuss()
{
    mHoehe=9;
    mBreite=4;
}

schuss::~schuss()
{
    //dtor
}

void schuss::bewegen(int schussgeschwSpieler)
{
    mY=mY-schussgeschwSpieler;
}

int schuss::trefferpruefen(alien Alien[],explosion* NaechsteExplosion,spiel* Spiel,spieler* Spieler)
{
for (int c=0; c<Spiel->getAnzahl().Alien; c++)
        {
if ( (mX>Alien[c].getX()) && (mX+mBreite<Alien[c].getX()+Alien[c].getBreite()) && (mY>Alien[c].getY()) & (mY+mHoehe<Alien[c].getY()+Alien[c].getHoehe()) )
            {               ///Treffer erkennen
                if (Spiel->getAnzahl().Explosion<10)
                {
                NaechsteExplosion->explodieren(Alien[c].getX(),Alien[c].getY());
                Spiel->setAnzahlExplosion(Spiel->getAnzahl().Explosion+1);

                }

                if (Spiel->isGameRunning())
                {Spiel->addPunkte(Spieler);}               ///Punkte hinzufügen

            return c;
            }
        }
    return -1;
}
