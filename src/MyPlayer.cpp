#include <cmath>
#include "header.h"
#include "templates.h"
#include "MyPlayer.h"

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

    // Speed.
    m_dSY = 0.2;

    gravity = 0.0019;
    friction = 0.98;
    bounce = 1;
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

double MyPlayer::GetYSpeed() {
    return m_dSY;
}

void MyPlayer::DoUpdate(int currentTime)
{

    DisplayableObject* pObject;
    for (int iObjectId = 0; (pObject = m_pMainEngine->GetDisplayableObject(iObjectId)) != NULL; iObjectId++)
    {

        if ( pObject == this ) // This is us, skip it
            continue;


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
            //printf("left\n");
        }

        // Ball is to the right of the obstacble.
        else if (m_dX > ox + ow) {
            testX = ox + ow;
            //printf("right\n");
        }

        // Ball is above the obstacle.
        if (m_dY < oy) {
            testY = oy;
            //printf("above\n");
        }

        // Ball is below the obstacle.
        else if (m_dY > oy + oh) {
            testY = oy + oh;
            //printf("below\n");
        }

        double distX = m_dX - testX;
        double distY = m_dY - testY;
        double distance = sqrt( (distX*distX) + (distY*distY) );
        int radius = height / 2;

        // If the ball is slightly above the tile, we bounce it up
        if ( distance <= (radius + 5) && distance >= radius) {
            if (distY < 0) {
                touchedTile = true;
                m_dSY *= -tileBounce;
                m_dY -= 5;
                printf("Collision distX: %.2f distY: %.2f\n", distX, distY);
            }
        }
    }


    if(m_dSY > 1){
        m_dSY = 1;
    }

    if(m_dSX > 0.6){
        m_dSX = 0.6;
    }


	if ( GetEngine()->IsKeyPressed( SDLK_UP ) )
		//m_dSY -= 0.01;
        m_dY -= 0.2;
	if ( GetEngine()->IsKeyPressed( SDLK_DOWN ) )
	    //m_dSY += 0.01;
        m_dY += 0.2;
	if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) )
		//m_dSX -= 0.003;
        m_dX -= 0.4;
	if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) )
		//m_dSX += 0.003;
        m_dX += 0.4;
	if ( GetEngine()->IsKeyPressed( SDLK_SPACE ) )
		m_dSX = m_dSY = 0;

	m_dX += m_dSX;
	m_dY += m_dSY;

    // Ball went over left bound.
	if ( (m_dX  +m_iStartDrawPosX) < 0 )
	{
        printf("Ball - left bound.\n");
		m_dX = - m_iStartDrawPosX;
		if ( m_dSX < 0 )
			m_dSX *= -bounce;
	}

    // Ball went over right bound.
	if ( (m_dX+m_iStartDrawPosX+m_iDrawWidth) > (GetEngine()->GetScreenWidth()-1) )
	{
        printf("Ball - right bound.\n");
		m_dX = GetEngine()->GetScreenWidth() -1 - m_iStartDrawPosX - m_iDrawWidth;
		if ( m_dSX > 0 )
			m_dSX *= -bounce;
	}

    // Ball went over top bound.
	if ( (m_dY+m_iStartDrawPosY) < 0 )
	{
        printf("Ball - top bound.\n");
		m_dY = -m_iStartDrawPosY;
		if ( m_dSY < 0 )
			m_dSY *= -bounce;
            m_dSX *= friction;

	}

    // Ball went over bottom bound.
	if ((m_dY + m_iStartDrawPosY + m_iDrawHeight) > (GetEngine()->GetScreenHeight()-1) )
	{
        printf("Ball - bottom bound.\n");
		m_dY = GetEngine()->GetScreenHeight() -1 - m_iStartDrawPosY - m_iDrawHeight;
		touchedGround = true;

	}

    // add gravity
    m_dSY += gravity;
    //printf("m_dSY: %f m_dSX: %f\n", m_dSY, m_dSX);
    //printf("m_dY: %f m_dX: %f\n", m_dY, m_dX);

	// Work out current position
	m_iCurrentScreenX = (int)(m_dX+0.5);
	m_iCurrentScreenY = (int)(m_dY+0.5);

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();

}


bool MyPlayer::getTileCollision(){
    return touchedTile;
}

void MyPlayer::setTileCollision(bool tileCollision) {
    touchedTile = tileCollision;
}

bool MyPlayer::getTouchedGround(){
    if (touchedGround) {
        touchedGround = false;
        return true;
    }
    return touchedGround;
}