#ifndef OBJEKT_H
#define OBJEKT_H


class objekt
{
    public:
        objekt();
        virtual ~objekt()=0;


        int getX(){return mX;};
        int getY(){return mY;};
        int getBreite(){return mBreite;};
        int getHoehe(){return mHoehe;};


        void setX(int x)
        {if (x>0 && x<500) mX=x;};
        void setY(int y)
        {if (y>0 && y<500) mY=y;};




    protected:
        int mBreite,mHoehe;
        int mX;
        int mY;
    private:


};

#endif // OBJEKT_H
