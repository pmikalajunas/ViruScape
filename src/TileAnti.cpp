#include "header.h"
#include "templates.h"
#include "TileAnti.h"

TileAnti::TileAnti(BaseEngine* pEngine, int tileX, int tileY) 
:Tile(pEngine, tileX, tileY), enabled(true)
{
    // Load tile image.
    sanitizerTile = new ImageSurface();
    sanitizerTile->LoadImage("tile_anti.png");

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

void TileAnti::Draw(void)
{
    if(!enabled){
        m_iDrawWidth = tileImage->GetWidth();
        m_iDrawHeight = tileImage->GetHeight();   
	    tileImage->RenderImage(GetEngine()->GetForeground(),
            0, 0,
            m_iCurrentScreenX, m_iCurrentScreenY,
            tileImage->GetWidth(), tileImage->GetHeight());
    }
    else
    {
        m_iDrawWidth = sanitizerTile->GetWidth();
        m_iDrawHeight = sanitizerTile->GetHeight();   
        sanitizerTile->RenderImage(GetEngine()->GetForeground(),
            0, 0,
            m_iCurrentScreenX, m_iCurrentScreenY,
            sanitizerTile->GetWidth(), sanitizerTile->GetHeight());
    }
    

    // This will store the position at which the object was drawn
    // so that the background can be drawn over the top.
    // This will then remove the object from the screen.
    StoreLastScreenPositionAndUpdateRect();
}


/*
    Handles the case when tile reaches the bottom of the screen.
    Sets tile's speed and new location.
    Sets sanitizer on the tile.
*/
void TileAnti::HandleBottomBound() {
    if ( (m_dY+m_iStartDrawPosY+m_iDrawHeight) > (BASE_SCREEN_HEIGHT - 1) )
    {
        // Put hand sanitizer.
        enabled = true;
        
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
