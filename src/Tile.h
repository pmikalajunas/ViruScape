#ifndef TILE_H
#define TILE_H

#include "DisplayableObject.h"
#include "JPGImage.h"
#include <vector>

using namespace std;

class Tile : public DisplayableObject
{

    public:
        Tile(BaseEngine* pEngine, int tileX, int tileY);
        virtual ~Tile();
        void Draw(void);
        void DoUpdate(int currentTime);
        void setTileYSpeed(double ySpeed);
        int getNewXLocation();
        int getNewYLocation();

        // Available x locations for a tile, avoids tile clashes.
        static vector<int> xTileLocations;
        // Save initial set of locations.
        static vector<int> xTileLocationsInitial;
                // Available x locations for a tile, avoids tile clashes.
        static vector<int> yTileLocations;
        // Save initial set of locations.
        static vector<int> yTileLocationsInitial;

    protected:
        ImageSurface* tileImage;
        double m_dSX;
        double m_dSY;
        double m_dX;
        double m_dY;
        // Saving starting tile coordinates.
        int initialX;
        int initialY;


};
#endif 
