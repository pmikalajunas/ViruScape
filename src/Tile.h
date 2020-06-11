#ifndef TILE_H
#define TILE_H

#include <DisplayableObject.h>


class Tile : public DisplayableObject
{
     private:
        double m_dSX;
        double m_dSY;
        double m_dX;
        double m_dY;

    public:
        Tile(BaseEngine* pEngine, int initialX, int initialY, int sizeX);
        virtual ~Tile();
        void Draw(void);
        void DoUpdate(int currentTime);
        void setTileYSpeed(double ySpeed);


    protected:



};

#endif // TILE_H
