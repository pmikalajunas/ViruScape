#include <cmath>
#include "header.h"
#include "templates.h"
#include "MyBall.h"

MyBall::MyBall(BaseEngine* pEngine, int size) : DisplayableObject(pEngine),
m_pMainEngine( pEngine ), height(size), touchedTile(false)
{
    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = 380;
    m_iCurrentScreenY = m_iPreviousScreenY = 300;

    // Set ball coordinate to the centre of the ball.
    m_iStartDrawPosX = - size / 2;
    m_iStartDrawPosY = - size / 2;

    // Record the ball size as both height and width.
    m_iDrawWidth = size;
    m_iDrawHeight = size;

    // Speed.
    m_dSY = 0.2;

    gravity = 0.0019;
    friction = 0.98;
    bounce = 1;
    tileBounce = 1.2;
    // Place the object initially.
    m_dX = m_iCurrentScreenX;
    m_dY = m_iCurrentScreenY;

    // And make it visible
    SetVisible(true);
}

MyBall::~MyBall()
{
    //dtor
}

void MyBall::Draw(void)
{

	unsigned int uiColourMult = 0x010001;
	unsigned int uiColourText = 0xffffff;

	// Concentric circles for pseudo-sphere
	int iRadiusSquared = (m_iDrawWidth/2) * (m_iDrawWidth/2);
	int iCentreX = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth/2;
	int iCentreY = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight/2;
	for ( int iX = m_iCurrentScreenX + m_iStartDrawPosX ; iX < (m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth) ; iX++ )
		for ( int iY = m_iCurrentScreenY + m_iStartDrawPosY ; iY < (m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight) ; iY++ )
			if ( ( (iX-iCentreX)*(iX-iCentreX) + (iY-iCentreY)*(iY-iCentreY) ) <= iRadiusSquared )
			{
				// 0xB0 is the range of values, 0xff is the brightest value.
				unsigned int uiColour = (0xB0 * ((iX-iCentreX)*(iX-iCentreX) + (iY-iCentreY)*(iY-iCentreY))) / iRadiusSquared;
				uiColour = 0xff - uiColour;
				GetEngine()->SafeSetScreenPixel( iX, iY, uiColourMult * uiColour );
			}

    // This will store the position at which the object was drawn
    // so that the background can be drawn over the top.
    // This will then remove the object from the screen.
    StoreLastScreenPositionAndUpdateRect();
}

double MyBall::GetYSpeed() {
    return m_dSY;
}

void MyBall::DoUpdate(int currentTime)
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

        if (distance <= radius) {
            if (distY > -radius && distY < (-radius + 1)) {
                touchedTile = true;
                m_dSY *= -tileBounce;
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
		if ( m_dSY > 0 )
			m_dSY *= -bounce;
            m_dSX *= friction;

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


bool MyBall::getTileCollision(){
    return touchedTile;
}

void MyBall::setTileCollision(bool tileCollision) {
    touchedTile = tileCollision;
}