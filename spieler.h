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


        bool darfschiessen=true;
        int leben=-100;
        int punkte=0;




        int getX(){return mX;};
        int getY(){return mY;};
        wxString getName(){return mName;};

        int setX(int x)
        {if (x>0 && x<500) mX=x;};
        int setY(int y)
        {if (y>0 && y<500) mY=y;};
        int setName(wxString name)
        {mName=name;};

        void bewegen(int wert)
        {
            mX+=wert;
        }



    protected:

    private:
        int schusszaehler=0;
        int mX=250-16;        //Anfangspositionen
        int mY=350;

        wxString mName="";

};

#endif // SPIELER_H
