#include "spieler.h"
#include "schuss.h"

spieler::spieler()
{
    //ctor
}

spieler::~spieler()
{
    //dtor
}

void spieler::schiessenerlauben(int anzahlSchuss)
{
    schusszaehler++;

    if (schusszaehler>40 && anzahlSchuss<10)
    {
    darfschiessen=true;
    schusszaehler=0;
    }
}

void spieler::schiessen(schuss* NaechsterSchuss)
{

    NaechsterSchuss->setX(x+12);      ///Schuss positionieren
    NaechsterSchuss->setY(y-8);

    darfschiessen=false;                        ///Beides daf�r, dass man nicht durchgehend schie�en kann.
    schusszaehler=0;
}
