#include "header.h"
#include "templates.h"
#include "MyBall.h"

MyBall::MyBall(BaseEngine* pEngine) : DisplayableObject(pEngine)
{
    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = 380;
    m_iCurrentScreenY = m_iPreviousScreenY = 500;

    // The object coordinate will be the top left of the object
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

    // Record the ball size as both height and width
    m_iDrawWidth = 60;
    m_iDrawHeight = 60;

    // Speed
    m_dSX = 1;
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

        // Ensure that the object gets redrawn on the display, if something changed
    RedrawObjects();

}
