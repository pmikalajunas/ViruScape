#include "header.h"
#include "templates.h"
#include "TileAnti.h"

TileAnti::TileAnti(BaseEngine* pEngine, int tileX, int tileY) 
:Tile(pEngine, tileX, tileY)
{
    // Load tile image.
    tileImage = new ImageSurface();
    tileImage->LoadImage("tile_anti.png");

    // Saving original coordinates
    initialX = tileX;
    initialY = tileY;

    // Current nd previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = tileX;
    m_iCurrentScreenY = m_iPreviousScreenY = tileY;

    // The object coordinate will be the top left of the object
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

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

TileAnti::~TileAnti()
{
    //dtor
}
