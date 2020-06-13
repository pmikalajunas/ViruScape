#ifndef ENEMYTILE_H
#define ENEMYTILE_H

#include <Tile.h>


class EnemyTile : public Tile
{
    public:
        EnemyTile(BaseEngine* pEngine, int initialX, int initialY);
        virtual ~EnemyTile();

    protected:

    private:
};

#endif // ENEMYTILE_H
