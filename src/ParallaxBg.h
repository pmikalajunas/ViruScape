#ifndef PARALLAXBG_H
#define PARALLAXBG_H

#include "DisplayableObject.h"
#include "JPGImage.h"


class ParallaxBg : public DisplayableObject
{
    public:
        ParallaxBg(BaseEngine* pEngine, int currentY);
        virtual ~ParallaxBg();
        void Draw();
        void DoUpdate(int currentTime);

    protected:

    private:
        ImageData* bg;
};

#endif // PARALLAXBG_H
