#include "header.h"
#include "templates.h"
#include "Constants.h"
#include "SelectionRectangle.h"

SelectionRectangle::SelectionRectangle(BaseEngine* pEngine, int posX, int posY)
: DisplayableObject(pEngine)
{
    // Load tile image.
    rectangleImage = new ImageSurface();
    rectangleImage->LoadImage("rectangle.png");

    m_iCurrentScreenX = m_iPreviousScreenX = posX;
    m_iCurrentScreenY = m_iPreviousScreenY = posY;

    // The object coordinate will be the top left of the object
    m_iStartDrawPosX = 0;
    m_iStartDrawPosY = 0;

    // Record the ball size as both height and width
    m_iDrawWidth = rectangleImage->GetWidth();
    m_iDrawHeight = rectangleImage->GetHeight();

    // And make it visible
    SetVisible(true);
}

SelectionRectangle::~SelectionRectangle()
{
    //dtor
}

void SelectionRectangle::Draw() {
    rectangleImage->RenderImage(GetEngine()->GetForeground(),
    0, 0,
    m_iCurrentScreenX, m_iCurrentScreenY,
    rectangleImage->GetWidth(), rectangleImage->GetHeight());

    // This will store the position at which the object was drawn
    // so that the background can be drawn over the top.
    // This will then remove the object from the screen.
    StoreLastScreenPositionAndUpdateRect();
}


void SelectionRectangle::setPosition(int x, int y) {
    m_iCurrentScreenX = x;
    m_iCurrentScreenY = y;
}