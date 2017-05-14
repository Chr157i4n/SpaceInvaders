#ifndef ALIEN_H
#define ALIEN_H

class alienschuss;

class alien
{
    public:
        alien();
        virtual ~alien();

        void bewegenY(int geschwY,int fensterBreite);
        void bewegenX(int fensterBreite);
        bool schiessen(alienschuss* NaechsterSchuss,int schusswahrscheinlichkeit);
        void reseten(int x,int y);

        void speedUp();

        int getX(){return mX;};
        int getY(){return mY;};

    protected:

    private:
        int mX;
        int mY;
        int mGeschwX=2;
        int breite=40;
};

#endif // ALIEN_H
