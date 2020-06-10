#include "header.h"
#include "templates.h"
#include "MyBall.h"

MyBall::MyBall(BaseEngine* pEngine, int size) : DisplayableObject(pEngine)
{
    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = 380;
    m_iCurrentScreenY = m_iPreviousScreenY = 400;

    // Set ball coordinate to the centre of the ball.
    m_iStartDrawPosX = -size/2;
    m_iStartDrawPosY = -size/2;

    // Record the ball size as both height and width
    m_iDrawWidth = size;
    m_iDrawHeight = size;

    // Speed
    m_dSY = 0.1;

    gravity = 0.001;
    friction = 0.98;
    bounce = 1;
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

void MyBall::DoUpdate(int currentTime) 
{

	if ( GetEngine()->IsKeyPressed( SDLK_UP ) )
		m_dSY -= 0.01;
	if ( GetEngine()->IsKeyPressed( SDLK_DOWN ) )
		m_dSY += 0.01;
	if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) )
		m_dSX -= 0.01;
	if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) )
		m_dSX += 0.01;
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
