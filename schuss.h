#ifndef SCHUSS_H
#define SCHUSS_H

class alien;
class explosion;
class spiel;
class spieler;


class schuss
{
    public:
        schuss();
        virtual ~schuss();

        void bewegen(int schussgeschwSpieler);
        bool trefferpruefen(alien* ZuPruefenderAlien,explosion* NaechsteExplosion,spiel* Spiel,spieler* Spieler);

        int getX(){return mX;};
        int getY(){return mY;};

        int setX(int x)
        {if (x>0 && x<500) mX=x;};
        int setY(int y)
        {if (y>0 && y<500) mY=y;};

        void abschiessen(int x,int y)
        {
         if (x>0 && x<500) mX=x;
         if (y>0 && y<500) mY=y;
        };


    protected:

    private:
        int mX;
        int mY;
};

#endif // SCHUSS_H
