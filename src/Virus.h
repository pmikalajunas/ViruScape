#ifndef VIRUS_H
#define VIRUS_H

#include "DisplayableObject.h"
#include "JPGImage.h"
#include "MyPlayer.h"
#include <string>
#include "Constants.h"

using namespace std;

class Virus : public DisplayableObject
{
    public:
        Virus(BaseEngine* pEngine, MyPlayer* player);
        virtual ~Virus();
        void Draw();
        void DoUpdate(int currentTime);
        void FollowPlayer(double enemyX, double enemyY);
        void setPlayerPositionToVirus();

    private:
        ImageSurface* virusImage;
        MyPlayer* player;
        // Player coordinates are recorder after introducing enemy.
        int playerX;
        int playerY;
        // Where the virus is located relative to the virus?
        int playerPositionToVirus;
        double m_dSX;
        double m_dSY;
        double m_dX;
        double m_dY;
        

};

#endif // VIRUS_H
