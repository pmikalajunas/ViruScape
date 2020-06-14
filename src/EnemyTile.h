#ifndef ENEMYTILE_H
#define ENEMYTILE_H

#include "Tile.h"
#include "Virus.h"

class EnemyTile : public Tile
{
    public:
        EnemyTile(BaseEngine* pEngine, int tileX, int tileY, Virus* virus);
        virtual ~EnemyTile();
        void DoUpdate(int currentTime);
        double getXPosition() { return m_dX; }
        double getYPosition() { return m_dY; }
        bool hasBeenReset() { return reset; }

    private:
        // Whether or not tile has been reset (it crossed the bottom bound)
        bool reset;
        Virus* virus;
        // Whether enemy released the virus.
        bool virusReleased;
};

#endif 
