#ifndef MYPLAYER_H
#define MYPLAYER_H

#include "DisplayableObject.h"
#include "JPGImage.h"
#include "Constants.h"
#include "TileAnti.h"


class MyPlayer : public DisplayableObject
{
    public:
        MyPlayer(BaseEngine* pEngine, TileAnti* tile);
        virtual ~MyPlayer();
        
        void Draw(void);
        void DoUpdate(int currentTime);
        double calculatePlayersDistanceToObject(DisplayableObject* pObject);
        void UpdateInteractingObjects();

        // GETTERS/SETTERS
        double GetYSpeed() { return m_dSY; }
        int getXPosition() { return m_iCurrentScreenX; }
        int getYPosition() { return m_iCurrentScreenY; }
        bool getTileCollision(void) { return touchedTile; }
        void setTileCollision(bool tileCollision) { touchedTile = tileCollision; }
        bool getTouchedGround(void);
        bool getCollectedSanitizer(void);
        
    private:
        BaseEngine* m_pMainEngine;
        double m_dSX;
        double m_dSY;
        double m_dX;
        double m_dY;
        double gravity;
        double bounce;
        double distanceXToObject;
        double distanceYToObject;
        int height;
        double tileBounce;
        bool touchedTile;
        bool touchedGround;
        bool collectedSanitizer;
        bool sanitized;
        int sanitizedTime;
        ImageSurface* frogImage;
        ImageSurface* frogShielded;
        TileAnti* sanitizerTile;

};

#endif
