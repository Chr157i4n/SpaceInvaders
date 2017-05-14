#include "alien.h"
#include "alienschuss.h"
#include <ctime>

alien::alien()
{
    std::srand(std::time(0));
}

alien::~alien()
{
    //dtor
}

void alien::bewegenY(int geschwY,int fensterBreite)
{
if (mX+breite>fensterBreite || mX<0) {mY=mY+geschwY;}
}

void alien::bewegenX(int fensterBreite)
{
    mX+=mGeschwX;
    if (mX+breite>fensterBreite || mX<0) {mGeschwX=-1*mGeschwX;}
}

void alien::speedUp()
{
    if (mGeschwX<0)
    {
        mGeschwX--;
    }
    else
    {
        mGeschwX++;
    }
}

void alien::reseten(int x,int y)
{
    mX=x;
    mY=y;
    mGeschwX=1;
}

bool alien::schiessen(alienschuss* NaechsterSchuss,int schusswahrscheinlichkeit)
{
     int zufall= std::rand()%1000+1;

        if (zufall>998-schusswahrscheinlichkeit)
            {
            NaechsterSchuss->abschiessen(mX+14,mY+30);
            return true;

            }
            return false;
}
