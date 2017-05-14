#ifndef ALIENSCHUSS_H
#define ALIENSCHUSS_H

class spieler;

class alienschuss
{
    public:
        alienschuss();
        virtual ~alienschuss();

        bewegen(int schussgeschwAliens);

         bool trefferpruefen(spieler* ZuPruefenderSpieler);

        int getX(){return mX;};
        int getY(){return mY;};

        void abschiessen(int x,int y)
        {
         if (x>0 && x<500) mX=x;
         if (y>0 && y<500) mY=y;
        };

    protected:

    private:
        int mX,mY;
};

#endif // ALIENSCHUSS_H
