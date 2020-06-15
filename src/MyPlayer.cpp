#include <cmath>
#include "header.h"
#include "templates.h"
#include "MyPlayer.h"
#include "Virus.h"
#include "Constants.h"
#include "ParallaxBg.h"

MyPlayer::MyPlayer(BaseEngine* pEngine) : DisplayableObject(pEngine),
m_pMainEngine( pEngine ), touchedTile(false), touchedGround(false)
{

    // Load frog image.
    frogImage = new ImageSurface();
    frogImage->LoadImage("frog.png");

    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = 380;
    m_iCurrentScreenY = m_iPreviousScreenY = 300;

    height = frogImage->GetHeight();

    // Draw position is object's left upper corner.
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

    // Record the ball size as both height and width.
    m_iDrawWidth = frogImage->GetWidth();
    m_iDrawHeight = frogImage->GetHeight() + IMAGE_HEIGHT_OFFSET;

    // Initially player slowly goes down, gravity boosts the process.
    m_dSY = 0.2;

    // Gravity is added to the player's speed, to create falling effect.
    gravity = 0.0019;
    // Bounce to the walls slows the player.
    bounce = 0.95;
    // Bounce off the tile increases player's speed.
    tileBounce = 1.1;
    // Place the object initially.
    m_dX = m_iCurrentScreenX;
    m_dY = m_iCurrentScreenY;

    // And make it visible
    SetVisible(true);
}

MyPlayer::~MyPlayer()
{
    //dtor
}

/*
    Draws player on the screen.
*/
void MyPlayer::Draw(void)
{

    frogImage->RenderImage(GetEngine()->GetForeground(),
    0, 0,
    m_iCurrentScreenX, m_iCurrentScreenY,
    frogImage->GetWidth(), frogImage->GetHeight());

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

        double distance = calculatePlayersDistanceToObject(pObject);
        int radius = height / 2;

        // If the virus hits us, we are done.
        if (distance < SPREADING_DISTANCE && dynamic_cast<Virus*>(pObject) != NULL) {
            touchedGround = true;
            return;
        }

        // If the ball is slightly above the tile, we bounce it up
        if ( distance <= (radius + 5) && distance >= radius) {
            if (distanceYToObject < 0) {
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

    UpdateInteractingObjects();

    // Prevent player from going to fast either direction.
    if(m_dSY > 1)
        m_dSY = 1;
    if(m_dSX > 0.6)
        m_dSX = 0.6;


    // Player can be navigated left and right with arrow keys.
	if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) )
        m_dX -= 0.4;
	if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) )
        m_dX += 0.4;

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