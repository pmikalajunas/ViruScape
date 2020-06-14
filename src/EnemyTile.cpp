#include "header.h"
#include "templates.h"
#include "EnemyTile.h"

EnemyTile::EnemyTile(BaseEngine* pEngine, int tileX, int tileY, Virus* virus) 
: Tile(pEngine, tileX, tileY), reset(false), virus(virus), virusReleased(true)
{
    // Load tile image.
    tileImage = new ImageSurface();
    tileImage->LoadImage("enemy_tile.png");

    // Saving original coordinates
    initialX = tileX;
    initialY = tileY;

    // Current nd previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = tileX;
    m_iCurrentScreenY = m_iPreviousScreenY = tileY;

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
}


void EnemyTile::DoUpdate( int iCurrentTime )
{

    // Slowly reduce the speed of moving tiles.
    m_dSY -= 0.0001;
    // Prevent tiles from going upwards.
    if(m_dSY < 0) {
        m_dSY = 0;
    }

    // Change tile position on their current speed.
    m_dX += m_dSX;
    m_dY += m_dSY;


    // Release the virus if it haven's been released ...
    // and tile reached 100 pixels
    if (m_dY > 100 && !virusReleased) {

        // Find x and y of the player.
        int playerX = m_dX + (m_iDrawWidth / 2);
        int playerY = m_dY + (m_iDrawHeight / 3);
        virus->FollowPlayer(playerX, playerY);
        virusReleased = true;
    }

    // Left boundary
    if ( (m_dX+m_iStartDrawPosX) < 0 )
    {
        m_dX = - m_iStartDrawPosX;
        if ( m_dSX < 0 )
            m_dSX = -m_dSX;
    }
    // Right boundary.
    if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) > (GetEngine()->GetScreenWidth()-1) )
    {
        m_dX = GetEngine()->GetScreenWidth() -1 - m_iStartDrawPosX - m_iDrawWidth;
        if ( m_dSX > 0 )
            m_dSX = -m_dSX;
    }

    // Bottom, here we set random tile's x position.
    if ( (m_dY+m_iStartDrawPosY+m_iDrawHeight) > (GetEngine()->GetScreenHeight()-1) )
    {
        reset = true;
        //m_dY = (initialY / 2);
        m_dY = getNewYLocation();

        // Get it slowly moving.
        setTileYSpeed(0.1);
        // Select x out of available x locations to avoid clashes.
        m_dX = getNewXLocation();
        // Reset the virus release flag.
        virusReleased = false;
    }

    // Set current position - you NEED to set the current positions
    m_iCurrentScreenX = (int)(m_dX+0.5);
    m_iCurrentScreenY = (int)(m_dY+0.5);

    // Ensure that the object gets redrawn on the display, if something changed
    RedrawObjects();
}
