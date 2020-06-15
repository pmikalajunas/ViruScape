#include "header.h"
#include "templates.h"
#include "Tile.h"
#include "Constants.h"


Tile::Tile(BaseEngine* pEngine, int tileX, int tileY)
: DisplayableObject(pEngine)
{

    // Load tile image.
    tileImage = new ImageSurface();
    tileImage->LoadImage("tile.png");

    // Saving original coordinates
    initialX = tileX;
    initialY = tileY;

    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = tileX;
    m_iCurrentScreenY = m_iPreviousScreenY = tileY;

    // The object coordinate will be the top left of the object
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

    // Record the ball size as both height and width
    m_iDrawWidth = tileImage->GetWidth();
    m_iDrawHeight = tileImage->GetHeight();

    // Speed
    m_dSX = m_dSY = 0;
    // Place the object initially.
    m_dX = m_iCurrentScreenX;
    m_dY = m_iCurrentScreenY;

    // And make it visible
    SetVisible(true);
}


Tile::~Tile()
{
    m_dSX = 0;
    m_dSY = 0;
    m_dX = 0;
    m_dY = 0;
}


void Tile::Draw(void)
{
	tileImage->RenderImage(GetEngine()->GetForeground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		tileImage->GetWidth(), tileImage->GetHeight());

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

    // Slowly reduce the speed of moving tiles.
    m_dSY -= TILE_SPEED_DECREASE;
    // Prevent tiles from going upwards.
    if(m_dSY < 0) {
        m_dSY = 0;
    }

    // Change tile position on their current speed.
    m_dX += m_dSX;
    m_dY += m_dSY;

    // Left boundary
    if ( (m_dX+m_iStartDrawPosX) < 0 )
    {
        m_dX = - m_iStartDrawPosX;
        if ( m_dSX < 0 )
            m_dSX = -m_dSX;
    }
    // Right boundary.
    if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) > (BASE_SCREEN_WIDTH - 1) )
    {
        m_dX = GetEngine()->GetScreenWidth() -1 - m_iStartDrawPosX - m_iDrawWidth;
        if ( m_dSX > 0 )
            m_dSX = -m_dSX;
    }

    // Bottom, here we set random tile's x position.
    HandleBottomBound();

    // Set current position - you NEED to set the current positions
    m_iCurrentScreenX = (int)(m_dX+0.5);
    m_iCurrentScreenY = (int)(m_dY+0.5);

    // Ensure that the object gets redrawn on the display, if something changed
    RedrawObjects();
}


/*
    Handles the case when tile reaches the bottom of the screen.
    Sets tile's speed and new location.
*/
void Tile::HandleBottomBound() {
    if ( (m_dY+m_iStartDrawPosY+m_iDrawHeight) > (BASE_SCREEN_HEIGHT - 1) )
    {
        // Set tile to move horizontally at random times.
        if (rand() % P_TILE_X_SPEED == 0) {
            m_dSX = TILE_X_SPEED;
        }

        setTileYSpeed(TILE_Y_SPEED);
        // Select x and y out of available x and y locations to avoid clashes.
        m_dY = getNewYLocation();
        m_dX = getNewXLocation();
    }
}

// Select x out of available x locations to avoid clashes.
int Tile::getNewXLocation() {
    int newX = 0;
    if(!xTileLocations.empty()) {
        newX = xTileLocations.back();
        xTileLocations.pop_back();
    } else {
        for (int x : xTileLocationsInitial)
            xTileLocations.push_back(x);
        newX = xTileLocations.back();
        xTileLocations.pop_back();
    }
    return newX;
}


// Select y out of available y locations to avoid clashes.
int Tile::getNewYLocation() {
    int newY = 0;
    if(!yTileLocations.empty()) {
        newY = yTileLocations.back();
        yTileLocations.pop_back();
    } else {
        for (int y : yTileLocationsInitial)
            yTileLocations.push_back(y);
        newY = yTileLocations.back();
        yTileLocations.pop_back();
    }
    return newY;
}

