#include "alienschuss.h"
#include "spieler.h"

alienschuss::alienschuss()
{
    //ctor
}

alienschuss::~alienschuss()
{
    //dtor
}

alienschuss::bewegen(int schussgeschwAliens)
{
     mY=mY+schussgeschwAliens;
}


bool alienschuss::trefferpruefen(spieler* ZuPruefenderSpieler)
{

    if ( (mX>ZuPruefenderSpieler->getX()) && (mX+4<ZuPruefenderSpieler->getX()+30) && (mY>ZuPruefenderSpieler->getY()) & (mY+9<ZuPruefenderSpieler->getY()+30) )
            {
                ZuPruefenderSpieler->setX(250-16);
                ZuPruefenderSpieler->leben--;

            return true;
            }
        return false;

}
