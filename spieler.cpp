#include "spieler.h"
#include "schuss.h"

spieler::spieler()
{
    mX=250-16;        //Anfangspositionen
    mY=350;
    mHoehe=45;
    mBreite=28;
}

spieler::~spieler()
{
    //dtor
}

void spieler::schiessenerlauben(int anzahlSchuss)
{
    schusszaehler++;

    if (schusszaehler>60 && anzahlSchuss<10)
    {
    darfschiessen=true;
    schusszaehler=0;
    }
}

void spieler::schiessen(schuss* NaechsterSchuss)
{

    NaechsterSchuss->abschiessen(mX+12,mY-8);      ///Schuss positionieren

    darfschiessen=false;                        ///Beides dafür, dass man nicht durchgehend schießen kann.
    schusszaehler=0;

}

void spieler::setLeben(int neueLeben)
{

    if (neueLeben>=0 && neueLeben<=10)
        {leben=neueLeben;}


}
