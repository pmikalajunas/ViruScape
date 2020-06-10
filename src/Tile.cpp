#include "header.h"
#include "templates.h"
#include "Tile.h"

Tile::Tile(BaseEngine* pEngine) : DisplayableObject(pEngine)
{
    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = 100;
    m_iCurrentScreenY = m_iPreviousScreenY = 100;

    // The object coordinate will be the top left of the object
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

    // Record the ball size as both height and width
    m_iDrawWidth = 100;
    m_iDrawHeight = 50;

    // And make it visible
    SetVisible(true);
}

Tile::~Tile()
{
    
}


void Tile::Draw(void)
{
    GetEngine()->DrawScreenRectangle(
    m_iCurrentScreenX, m_iCurrentScreenY,
    m_iCurrentScreenX + m_iDrawWidth -1,
    m_iCurrentScreenY + m_iDrawHeight -1,
    0x00ff00 );

    // This will store the position at which the object was drawn
    // so that the background can be drawn over the top.
    // This will then remove the object from the screen.
    StoreLastScreenPositionAndUpdateRect();
}
