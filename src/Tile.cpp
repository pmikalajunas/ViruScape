#include "header.h"
#include "templates.h"
#include "Tile.h"

#define BASE_SCREEN_WIDTH 800
#define BASE_SCREEN_HEIGHT 600


Tile::Tile(BaseEngine* pEngine, int initialX, int initialY, int sizeX) : DisplayableObject(pEngine)
{
    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = initialX;
    m_iCurrentScreenY = m_iPreviousScreenY = initialY;

    // The object coordinate will be the top left of the object
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

    // Record the ball size as both height and width
    m_iDrawWidth = sizeX;
    m_iDrawHeight = 30;

    // Speed
    m_dSX = 0;
    // Place the object initially.
    m_dX = m_iCurrentScreenX;
    m_dY = m_iCurrentScreenY;

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
    m_iCurrentScreenX + (m_iDrawWidth) - 1,
    m_iCurrentScreenY + m_iDrawHeight - 1,
    0x000000 );

    // This will store the position at which the object was drawn
    // so that the background can be drawn over the top.
    // This will then remove the object from the screen.
    StoreLastScreenPositionAndUpdateRect();
}

// Called frequently, this should move the item
// In this case we also accept cursor key presses to change the speed
// Space will set the speed to zero
void Tile::DoUpdate( int iCurrentTime )
{


    // Alter position for speed
    m_dX += m_dSX;
    m_dY += m_dSY;

    //printf("Tile's initial m_dX: (%.2f), m_dY: (%.2f)\n", m_dX, m_dY );

    // Left boundary
    if ( (m_dX+m_iStartDrawPosX) < 0 )
    {
        //printf("Case 1\n");
        m_dX = - m_iStartDrawPosX;
        if ( m_dSX < 0 )
            m_dSX = -m_dSX;
    }
    // Right boundary.
    if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) > (GetEngine()->GetScreenWidth()-1) )
    {
        //printf("Case 2\n");
        m_dX = GetEngine()->GetScreenWidth() -1 - m_iStartDrawPosX - m_iDrawWidth;
        if ( m_dSX > 0 )
            m_dSX = -m_dSX;
    }
    // Top
    if ( (m_dY+m_iStartDrawPosY) < 0 )
    {
        //printf("Case 3\n");
        m_dY = -m_iStartDrawPosY;
        if ( m_dSY < 0 )
            m_dSY = -m_dSY;
    }

    // Bottom
    if ( (m_dY+m_iStartDrawPosY+m_iDrawHeight) > (GetEngine()->GetScreenHeight()-1) )
    {
        //printf("Case 4\n");
        m_dY = -20;

    }

    // Set current position - you NEED to set the current positions
    m_iCurrentScreenX = (int)(m_dX+0.5);
    m_iCurrentScreenY = (int)(m_dY+0.5);

    // Ensure that the object gets redrawn on the display, if something changed
    RedrawObjects();
}


void Tile::setTileYSpeed(double ySpeed) {
    m_dSY = ySpeed;
    printf("setTileYSpeeed, m_dSY: %.2f\n", m_dSY);
}
