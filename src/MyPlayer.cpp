#include <cmath>
#include "header.h"
#include "templates.h"
#include "MyPlayer.h"
#include "Virus.h"
#include "Constants.h"
#include "ParallaxBg.h"
#include "TileAnti.h"

MyPlayer::MyPlayer(BaseEngine* pEngine, TileAnti* tile) : DisplayableObject(pEngine),
m_pMainEngine( pEngine ), touchedTile(false), touchedGround(false),
collectedSanitizer(false), sanitized(false), sanitizerTile(tile), sanitizedTime(0)
{

    // Load frog image.
    frogImage = new ImageSurface();
    frogImage->LoadImage("frog.png");

    // Load shielded frog image.
    frogShielded = new ImageSurface();
    frogShielded->LoadImage("frog_shielded.png");

    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = PLAYER_INITIAL_X;
    m_iCurrentScreenY = m_iPreviousScreenY = PLAYER_INITIAL_Y;

    height = frogImage->GetHeight();

    // Draw position is object's left upper corner.
    m_iStartDrawPosX = m_iStartDrawPosY = 0;

    m_iDrawWidth = frogImage->GetWidth();
    m_iDrawHeight = frogImage->GetHeight() + IMAGE_HEIGHT_OFFSET;

    // Initially player slowly goes down, gravity boosts the process.
    m_dSY = PLAYER_DEFAULT_V_SPEED;

    // Gravity is added to the player's speed, to create falling effect.
    gravity = PLAYER_GRAVITY;
    // Bounce to the walls slows the player.
    bounce = PLAYER_WALL_BOUNCE;
    // Bounce off the tile increases player's speed.
    tileBounce = PLAYER_TILE_BOUNCE;
    // Place the object initially.
    m_dX = m_iCurrentScreenX;
    m_dY = m_iCurrentScreenY;

    // And make it visible
    SetVisible(true);
}

MyPlayer::~MyPlayer()
{
}

/*
    Draws player on the screen.
*/
void MyPlayer::Draw(void)
{

    // Draw a shield over a frog if its sanitized.
    if(!sanitized) {
        m_iDrawWidth = frogImage->GetWidth();
        m_iDrawHeight = frogImage->GetHeight() + IMAGE_HEIGHT_OFFSET;
        frogImage->RenderImage(GetEngine()->GetForeground(),
            0, 0,
            m_iCurrentScreenX, m_iCurrentScreenY,
            frogImage->GetWidth(), frogImage->GetHeight());
    } else {
        m_iDrawWidth = frogShielded->GetWidth();
        m_iDrawHeight = frogShielded->GetHeight() + IMAGE_HEIGHT_OFFSET;
        frogShielded->RenderImage(GetEngine()->GetForeground(),
            0, 0,
            m_iCurrentScreenX, m_iCurrentScreenY,
            frogShielded->GetWidth(), frogShielded->GetHeight());
    }



    // This will store the position at which the object was drawn
    // so that the background can be drawn over the top.
    // This will then remove the object from the screen.
    StoreLastScreenPositionAndUpdateRect();
}


/*
    Calculates distance from player to the given object.
*/
double MyPlayer::calculatePlayersDistanceToObject(DisplayableObject* pObject) {

    int testX = m_dX;
    int testY = m_dY;
    // Get obstacle's X and Y.
    int ox = pObject->getCurrentScreenX();
    int oy = pObject->getCurrentScreenY();
    // Get obstacle's width and height.
    int ow = pObject->getDrawWidth();
    int oh = pObject->getDrawHeight();

    // Ball is to the left of the obstacble.
    if (m_dX < ox) {
        testX = ox;
    }
    // Ball is to the right of the obstacble.
    else if (m_dX > ox + ow) {
        testX = ox + ow;
    }
    // Ball is above the obstacle.
    if (m_dY < oy) {
        testY = oy;
    }
    // Ball is below the obstacle.
    else if (m_dY > oy + oh) {
        testY = oy + oh;
    }

    distanceXToObject = m_dX - testX;
    distanceYToObject = m_dY - testY;
    return sqrt( (distanceXToObject*distanceXToObject) + (distanceYToObject*distanceYToObject) );
}

/*
    Checks if player cought the virus.
    Checks if player touched the tile from above.
*/
void MyPlayer::UpdateInteractingObjects() {

    DisplayableObject* pObject;
    for (int iObjectId = 0; (pObject = m_pMainEngine->GetDisplayableObject(iObjectId)) != NULL; iObjectId++)
    {
        if ( pObject == this ) // This is us, skip it
            continue;

        // Ignore background object.
        if(dynamic_cast<ParallaxBg*>(pObject) != NULL) {
            continue;
        }

        // Skip invisible objects.
        if (!pObject->IsVisible()) {
            continue;
        }

        double distance = calculatePlayersDistanceToObject(pObject);
        int radius = height / 2;

        // If the virus hits us, we are done.
        if (distance < SPREADING_DISTANCE && dynamic_cast<Virus*>(pObject) != NULL) {
            // Hand sanitizer kills all the germs over here.
            if(sanitized) {
                Virus* virus = dynamic_cast<Virus*>(pObject);
                virus->SetVisible(false);
                
            } else {
                touchedGround = true;
                return;
            }

        }

        // If the player is slightly above the tile, we bounce it up
        if ( distance <= (radius + 5) && distance >= radius) {
            if (distanceYToObject < 0) {
                // Check if we have collected hand sanitizer.
                if (dynamic_cast<TileAnti*>(pObject) != NULL) {
                    collectedSanitizer = true;
                    sanitized = true;
                    // Record the time when frog has been sanitized.
                    sanitizedTime = GetEngine()->GetTime();
                    sanitizerTile->setEnabled(false);
                }
                touchedTile = true;
                m_dSY *= -tileBounce;
                m_dY -= 5;
            }
        }
    }
}

/*
    Updates player's location based on speed.
    Checks if player clashed with any other objects.
    Moves player depending on key presses.
    Prevents player from crossing screen boundaries.
*/
void MyPlayer::DoUpdate(int currentTime)
{

    // Check if hand sanitizer expired.
    if (currentTime - sanitizedTime > SANITIZATION_TICKS) {
        sanitized = false;
        sanitizedTime = 0;
    }

    UpdateInteractingObjects();

    // Prevent player from going to fast either direction.
    if(m_dSY > PLAYER_V_SPEED_CAP)
        m_dSY = PLAYER_V_SPEED_CAP;

    // Player can be navigated left and right with arrow keys.
	if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) )
        m_dX -= PLAYER_SIDE_MOVEMENT_SPEED;
	if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) )
        m_dX += PLAYER_SIDE_MOVEMENT_SPEED;

    // Change location based on the current speed.
	m_dX += m_dSX;
	m_dY += m_dSY;

    // Player touched left side of the screen, bounce player back.
	if ( (m_dX  +m_iStartDrawPosX) < 0 )
	{
		m_dX = - m_iStartDrawPosX;
		if ( m_dSX < 0 )
			m_dSX *= -bounce;
	}

    // Player touched right side of the screen, bounce player back.
	if ( (m_dX+m_iStartDrawPosX+m_iDrawWidth) > (GetEngine()->GetScreenWidth()-1) )
	{
		m_dX = GetEngine()->GetScreenWidth() -1 - m_iStartDrawPosX - m_iDrawWidth;
		if ( m_dSX > 0 )
			m_dSX *= -bounce;
	}

    // Player touched top of the screen, bounce player back.
	if ( (m_dY+m_iStartDrawPosY) < 0 )
	{
		m_dY = -m_iStartDrawPosY;
		if ( m_dSY < 0 )
			m_dSY *= -bounce;
	}

    // Player touched the ground, end the game.
	if ((m_dY + m_iStartDrawPosY + m_iDrawHeight) > (GetEngine()->GetScreenHeight()-1) )
	{
		m_dY = GetEngine()->GetScreenHeight() -1 - m_iStartDrawPosY - m_iDrawHeight;
		touchedGround = true;
	}

    // Add gravity to make player go down slowly.
    m_dSY += gravity;

	// Work out current position
	m_iCurrentScreenX = (int)(m_dX+0.5);
	m_iCurrentScreenY = (int)(m_dY+0.5);

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

/*
    If touchedGround is true, sets it false, returns true.
    Otherwise, returns false.
*/
bool MyPlayer::getTouchedGround(){
    if (touchedGround) {
        touchedGround = false;
        return true;
    }
    return touchedGround;
}

/*
    If collectedSanitizer is true, sets it false, returns true.
    Otherwise, returns false.
*/
bool MyPlayer::getCollectedSanitizer(){
    if (collectedSanitizer) {
        collectedSanitizer = false;
        return true;
    }
    return collectedSanitizer;
}