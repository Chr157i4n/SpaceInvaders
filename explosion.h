#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "objekt.h"



class explosion : public objekt
{
    public:
        explosion();
        virtual ~explosion();

        int getLaufzeit(){return mLaufzeit;};

        int setLaufzeit(int laufzeit)
        {if (laufzeit>0) mLaufzeit=laufzeit;};

        explodieren(int x,int Y);
        bool ueberpruefen();

    protected:

    private:
        int mLaufzeit;
};

#endif // EXPLOSION_H
