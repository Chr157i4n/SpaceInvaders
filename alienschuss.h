#ifndef ALIENSCHUSS_H
#define ALIENSCHUSS_H
#include "objekt.h"

class spieler;
class spiel;

class alienschuss : public objekt
{
    public:
        alienschuss();
        virtual ~alienschuss();

        void bewegen(int schussgeschwAliens);

         int trefferpruefen(spieler* ZuPruefenderSpieler,spiel* Spiel);



        void abschiessen(int x,int y)
        {
         if (x>0 && x<500) mX=x;
         if (y>0 && y<500) mY=y;
        };

    protected:

    private:

};

#endif // ALIENSCHUSS_H
