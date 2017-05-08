#ifndef SPIELER_H
#define SPIELER_H

class schuss;

class spieler
{
    public:
        spieler();
        virtual ~spieler();

        void schiessenerlauben(int anzahlSchuss);
        void schiessen(schuss* Schuss);

        int x=250-16;        //Anfangspositionen
        int y=350;
        bool darfschiessen=true;
        int leben=3;
        int punkte=0;
        wxString name="";



    protected:

    private:
        int schusszaehler=0;
};

#endif // SPIELER_H
