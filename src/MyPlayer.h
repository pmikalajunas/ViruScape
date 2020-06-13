#ifndef MYPLAYER_H
#define MYPLAYER_H

#include "DisplayableObject.h"
#include "JPGImage.h"
#include "Constants.h"

// We add the offset to the object.
#define IMAGE_HEIGHT_OFFSET 10;

class MyPlayer : public DisplayableObject
{
    public:
        MyPlayer(BaseEngine* pEngine);
        virtual ~MyPlayer();
        void Draw(void);
        void DoUpdate(int currentTime);
        double GetYSpeed(void);
        bool getTileCollision(void);
        void setTileCollision(bool tileCollision);
        bool getTouchedGround(void);
        double calculatePlayersDistanceToObject(DisplayableObject* pObject);

        int getXPosition() { return m_iCurrentScreenX; }
        int getYPosition() { return m_iCurrentScreenY; }

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
        double distanceXToObject;
        double distanceYToObject;
        int height;
        double tileBounce;
        bool touchedTile;
        bool touchedGround;
        ImageSurface* frogImage;
};

#endif // MyPlayer_H
