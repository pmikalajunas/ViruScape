#include "header.h"
#include "templates.h"
#include "Virus.h"
#include "Constants.h"

Virus::Virus(BaseEngine* pEngine, MyPlayer* player) : DisplayableObject(pEngine),
player(player)
{
    // Load virus image.
    virusImage = new ImageSurface();
    virusImage->LoadImage("virus.png");

    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = m_iPreviousScreenX = 0;
    m_iCurrentScreenY = m_iPreviousScreenY = 0;

    // The object coordinate will be the top left of the object
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

    // // Record the ball size as both height and width
    m_iDrawWidth = virusImage->GetWidth();
    m_iDrawHeight = virusImage->GetHeight();

    // Speed
    m_dSX = 0;
    m_dSY = 0;
    // Place the object initially.
    m_dX = m_iCurrentScreenX;
    m_dY = m_iCurrentScreenY;

    // Virus only appears visible when enemy shoots it.
    SetVisible(false);
}

Virus::~Virus()
{
    //dtor
}

void Virus::Draw() {
    // Hide virus when enemy is not shooting it.
    if (!IsVisible()) {
        return;
    }

    virusImage->RenderImage(GetEngine()->GetForeground(),
    0, 0,
    m_iCurrentScreenX, m_iCurrentScreenY,
    virusImage->GetWidth(), virusImage->GetHeight());

    // This will store the position at which the object was drawn
    // so that the background can be drawn over the top.
    // This will then remove the object from the screen.
    StoreLastScreenPositionAndUpdateRect();

}


void Virus::FollowPlayer(double enemyX, double enemyY) {
    // Reset the speed of the virus.
    m_dSX = 0;
    m_dSY = 0;
    // Put the virus close to the enemy, set it visible.
    m_dX = m_iCurrentScreenX = enemyX;
    m_dY = m_iCurrentScreenY = enemyY;
    SetVisible(true);
}

void Virus::DoUpdate( int iCurrentTime ) {

    if(!IsVisible()) {
        return;
    }

    double playerX = player->getXPosition();
    double playerY = player->getYPosition();

    // Check player position, adjust speed accordingly.
    if (playerX > m_iCurrentScreenX && playerY > m_iCurrentScreenY)
	{
		m_dSY = 0.2;
		m_dSX = 0.2;
	}
	else if (playerX < m_iCurrentScreenX && playerY < m_iCurrentScreenY)
	{
        
		m_dSY = -0.2;
		m_dSX = -0.2;
	}
	else if (playerX > m_iCurrentScreenX && playerY < m_iCurrentScreenY)
	{
		m_dSY = -0.2;
		m_dSX = -0.2;
	}
	else if (playerX < m_iCurrentScreenX && playerY > m_iCurrentScreenY)
	{
		m_dSY = -0.2;
		m_dSX = -0.2;
	} 
	else if (playerX == m_iCurrentScreenX && playerY > m_iCurrentScreenY)
	{
		m_dSY = 0.2;
        m_dSX = 0;
	}
	else if (playerX == m_iCurrentScreenX && playerY < m_iCurrentScreenY)
	{
		m_dSY = -0.2;
        m_dSX = 0;
	}
	else if (playerY == m_iCurrentScreenY && playerX > m_iCurrentScreenX)
	{
		m_dSX = 0.2;
        m_dSY = 0;
	}
	else if (playerY == m_iCurrentScreenY && playerX < m_iCurrentScreenX)
	{
		m_dSX = -0.2;
        m_dSY = 0;
	}

    // Change tile position on their current speed.
    m_dX += m_dSX;
    m_dY += m_dSY;

    // Hide image once it crosses the boundaries of the screen.
	if (m_iCurrentScreenY >= BASE_SCREEN_HEIGHT || m_iCurrentScreenY <= 0)
	{
		SetVisible(false);
	}

    // Hide image once it crosses the boundaries of the screen.
	if (m_iCurrentScreenX >= BASE_SCREEN_WIDTH || m_iCurrentScreenY <= 0)
	{
		SetVisible(false);
	}

    	// Work out current position
	m_iCurrentScreenX = (int)(m_dX+0.5);
	m_iCurrentScreenY = (int)(m_dY+0.5);

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();


}

