#include "header.h"
#include "templates.h"
#include "ParallaxBg.h"
#include "Constants.h"

ParallaxBg::ParallaxBg(BaseEngine* pEngine, int currentY) : DisplayableObject(pEngine)
{
    bg = new ImageData();
    bg->LoadImage("bg_sky.png");

    printf("%d\n", bg->GetWidth());

    // Current and previous coordinates for the object - set them the same initially
    m_iCurrentScreenX = 0;
    m_iCurrentScreenY = currentY;

    // The object coordinate will be the top left of the object
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

    m_iDrawWidth = BASE_SCREEN_WIDTH;
    m_iDrawHeight = BASE_SCREEN_HEIGHT;

    SetVisible(true);
}

ParallaxBg::~ParallaxBg() 
{
    //dtor
}


/*
    Draws the bg image to the background of the screen.
*/
void ParallaxBg::Draw()
{
	bg->RenderImage(GetEngine()->GetBackground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		bg->GetWidth(), bg->GetHeight());

	StoreLastScreenPositionAndUpdateRect();
}

void ParallaxBg::DoUpdate(int iCurrentTime)
{
    if(iCurrentTime % 20 == 0)
	    m_iCurrentScreenY++;

	// Go to the top of the picture, when we reach the bottom.
	if (m_iCurrentScreenY >= BASE_SCREEN_HEIGHT)
		m_iCurrentScreenY = -BASE_SCREEN_HEIGHT;
}


