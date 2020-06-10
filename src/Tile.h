#ifndef TILE_H
#define TILE_H

#include <DisplayableObject.h>


class Tile : public DisplayableObject
{
    public:
        Tile(BaseEngine* pEngine);
        virtual ~Tile();
        void Draw(void);

    protected:

    private:
};

#endif // TILE_H
