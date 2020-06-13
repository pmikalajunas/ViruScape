#ifndef MYBALL_H
#define MYBALL_H

#include "DisplayableObject.h"
#include "JPGImage.h"

// We add the offset to the object.
#define IMAGE_HEIGHT_OFFSET 10;

class MyBall : public DisplayableObject
{
    public:
        MyBall(BaseEngine* pEngine);
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
        ImageSurface* frogImage;
};

#endif // MYBALL_H
