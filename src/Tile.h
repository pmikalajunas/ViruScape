#ifndef TILE_H
#define TILE_H

#include "DisplayableObject.h"
#include "JPGImage.h"

class Tile : public DisplayableObject
{

    public:
        Tile(BaseEngine* pEngine, int initialX, int initialY);
        virtual ~Tile();
        void Draw(void);
        void DoUpdate(int currentTime);
        void setTileYSpeed(double ySpeed);

    private:


    protected:
        ImageSurface* tileImage;
        double m_dSX;
        double m_dSY;
        double m_dX;
        double m_dY;



};

#endif // TILE_H
