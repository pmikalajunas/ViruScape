#ifndef VIRUS_H
#define VIRUS_H

#include <DisplayableObject.h>
#include "JPGImage.h"
#include "MyPlayer.h"


class Virus : public DisplayableObject
{
    public:
        Virus(BaseEngine* pEngine, MyPlayer* player);
        virtual ~Virus();
        void Draw();
        void DoUpdate(int currentTime);
        void FollowPlayer(double enemyX, double enemyY);

    private:
        ImageSurface* virusImage;
        MyPlayer* player;
        double m_dSX;
        double m_dSY;
        double m_dX;
        double m_dY;
};

#endif // VIRUS_H
