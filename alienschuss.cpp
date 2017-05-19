#include "alienschuss.h"
#include "spieler.h"
#include "spiel.h"

alienschuss::alienschuss()
{
    mHoehe=9;
    mBreite=3;
}

alienschuss::~alienschuss()
{
    //dtor
}

void alienschuss::bewegen(int schussgeschwAliens)
{
     mY=mY+schussgeschwAliens;
}


int alienschuss::trefferpruefen(spieler* ZuPruefenderSpieler,spiel* Spiel)
{

    if ( (mX>ZuPruefenderSpieler->getX()) && (mX+mBreite<ZuPruefenderSpieler->getX()+ZuPruefenderSpieler->getBreite()) && (mY>ZuPruefenderSpieler->getY()) & (mY+mBreite<ZuPruefenderSpieler->getY()+ZuPruefenderSpieler->getHoehe()) )
            {
                if (Spiel->isGameRunning())
                {
                ZuPruefenderSpieler->setX(Spiel->getBreite()/2-ZuPruefenderSpieler->getBreite()/2);
                ZuPruefenderSpieler->setLeben(ZuPruefenderSpieler->getLeben()-1);
                }

            return 1;
            }
        return -1;

}
