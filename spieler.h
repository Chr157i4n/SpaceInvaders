#ifndef SPIELER_H
#define SPIELER_H
#include "objekt.h"

class schuss;

class spieler : public objekt
{
    public:
        spieler();
        virtual ~spieler();

        void schiessenerlauben(int anzahlSchuss);
        void schiessen(schuss* Schuss);


        void setPunkte(int neuepunkte){ punkte=neuepunkte;};
        void addPunkte(int neuepunkte){if (neuepunkte>punkte) {punkte=neuepunkte;} else {punkte++;}};
        int getPunkte(){return punkte;};

        void setLeben(int neueLeben);
        int getLeben(){return leben;};

        void allowShooting(){darfschiessen=true;};
        void pauseShooting(){darfschiessen=false;};
        bool ShootingAllowed(){return darfschiessen;};

        wxString getName(){return mName;};
        void setName(wxString name)
        {mName=name;};



        void bewegen(int wert)
        {
            mX+=wert;
        }



    protected:

    private:

        bool darfschiessen=true;
        int leben=-100;
        int punkte=0;

        int schusszaehler=0;
        wxString mName="";

};

#endif // SPIELER_H
