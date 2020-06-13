#include "header.h"
#include "templates.h"
#include "EnemyTile.h"

EnemyTile::EnemyTile(BaseEngine* pEngine, int initialX, int initialY) 
: Tile(pEngine, initialX, initialY)
{
    // Load tile image.
    tileImage = new ImageSurface();
    tileImage->LoadImage("enemy_tile.png");
    
    // Current nd previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = initialX;
    m_iCurrentScreenY = m_iPreviousScreenY = initialY;

    // The object coordinate will be the top left of the object
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

    // Record the ball size as both height and width
    m_iDrawWidth = tileImage->GetWidth();
    m_iDrawHeight = tileImage->GetHeight();

    // Speed
    m_dSX = 0;
    // Place the object initially.
    m_dX = m_iCurrentScreenX;
    m_dY = m_iCurrentScreenY;

    // And make it visible
    SetVisible(true);
}

EnemyTile::~EnemyTile()
{
    //dtor
}
