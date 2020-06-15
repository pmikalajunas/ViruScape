#ifndef TILEANTI_H
#define TILEANTI_H

#include "Tile.h"
#include "Constants.h"


class TileAnti : public Tile
{
    public:
        TileAnti(BaseEngine* pEngine, int tileX, int tileY);
        virtual ~TileAnti();
        void Draw();
        void HandleBottomBound();
        
        // Getters / Setters
        void setEnabled(bool sanitizerEnabled) { enabled = sanitizerEnabled; }

    protected:

    private:
        ImageSurface* sanitizerTile;
        bool enabled;
};

#endif // TILEANTI_H
