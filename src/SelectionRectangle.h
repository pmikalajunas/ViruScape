#ifndef SELECTIONRECTANGLE_H
#define SELECTIONRECTANGLE_H

#include "DisplayableObject.h"
#include "JPGImage.h"


class SelectionRectangle : public DisplayableObject
{
    public:
        SelectionRectangle(BaseEngine* pEngine, int posX, int posY);
        virtual ~SelectionRectangle();
        void Draw();
        void setPosition(int x, int y);

    protected:

    private:
        ImageSurface* rectangleImage;
};

#endif // SELECTIONRECTANGLE_H
