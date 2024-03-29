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
    m_iStartDrawPosX = m_iStartDrawPosY = 0;

    // // Record the ball size as both height and width
    m_iDrawWidth = virusImage->GetWidth();
    m_iDrawHeight = virusImage->GetHeight();

    // Speed
    m_dSX = m_dSY = 0;

    // Place the object initially.
    m_dX = m_iCurrentScreenX;
    m_dY = m_iCurrentScreenY;

    // Virus only appears visible when enemy shoots it.
    SetVisible(false);
}

Virus::~Virus()
{
}

/*
    Draws virus on the screen. (If it's visible)
*/
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


/*
    Function sets playerPositionToVirus based on player's and virus locations.
*/
void Virus::setPlayerPositionToVirus() {

    // Set player coordinates so that the virus could follow.
    playerX = player->getXPosition();
    playerY = player->getYPosition();

    if (playerX > m_iCurrentScreenX && playerY > m_iCurrentScreenY)
		playerPositionToVirus = NW;

	else if (playerX < m_iCurrentScreenX && playerY < m_iCurrentScreenY)
		playerPositionToVirus = SE;

	else if (playerX > m_iCurrentScreenX && playerY < m_iCurrentScreenY)
		playerPositionToVirus = SW;

	else if (playerX < m_iCurrentScreenX && playerY > m_iCurrentScreenY)
        playerPositionToVirus = NE;

	else if (playerX == m_iCurrentScreenX && playerY > m_iCurrentScreenY)
        playerPositionToVirus = N;

	else if (playerX == m_iCurrentScreenX && playerY < m_iCurrentScreenY)
        playerPositionToVirus = S;

	else if (playerY == m_iCurrentScreenY && playerX > m_iCurrentScreenX)
        playerPositionToVirus = W;

	else if (playerY == m_iCurrentScreenY && playerX < m_iCurrentScreenX)
        playerPositionToVirus = E;

}

/*
    Sets virus visible, shoots it from opponent's location.
*/
void Virus::FollowPlayer(double enemyX, double enemyY) {

    setPlayerPositionToVirus();

    // Put the virus close to the enemy, set it visible.
    m_iCurrentScreenX = enemyX;
    m_iCurrentScreenY = enemyY;
    SetVisible(true);
}

/*
    Makes virus to move towards initial player's location.
    Hides virus once it goes over boundaries of the screen.
*/
void Virus::DoUpdate( int iCurrentTime ) {

    if(!IsVisible()) {
        RedrawObjects();
        return;
    }

    switch(playerPositionToVirus) {
        case NW:
            m_iCurrentScreenY += VIRUS_SPEED;
		    m_iCurrentScreenX += VIRUS_SPEED;
            break;
        case SE:
            m_iCurrentScreenY -= VIRUS_SPEED;
		    m_iCurrentScreenX -= VIRUS_SPEED;
            break;
        case SW:
            m_iCurrentScreenY -= VIRUS_SPEED;
		    m_iCurrentScreenX += VIRUS_SPEED;
            break;
        case NE:
            m_iCurrentScreenY += VIRUS_SPEED;
		    m_iCurrentScreenX -= VIRUS_SPEED;
            break;
        case N:
            m_iCurrentScreenY += VIRUS_SPEED;
            break;
        case S:
            m_iCurrentScreenY -= VIRUS_SPEED;
            break;
        case W:
            m_iCurrentScreenX += VIRUS_SPEED;
            break;
        case E:
            m_iCurrentScreenX -= VIRUS_SPEED;
            break;
        default:
            break;
    }

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

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}
