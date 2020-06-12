#ifndef MYBALL_H
#define MYBALL_H

#include "DisplayableObject.h"


class MyBall : public DisplayableObject
{
    public:
        MyBall(BaseEngine* pEngine, int size);
        virtual ~MyBall();
        void Draw(void);
        void DoUpdate(int currentTime);
        double GetYSpeed(void);
        bool getTileCollision(void);
        void setTileCollision(bool tileCollision);
        bool getTouchedGround(void);


    protected:

     private:
        BaseEngine * m_pMainEngine;
        double m_dSX;
        double m_dSY;
        double m_dX;
        double m_dY;
        double gravity;
        double friction;
        double bounce;
        int height;
        double tileBounce;
        bool touchedTile;
        bool touchedGround;
};

#endif // MYBALL_H
