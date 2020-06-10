#ifndef MYBALL_H
#define MYBALL_H

#include <DisplayableObject.h>


class MyBall : public DisplayableObject
{
    public:
        MyBall(BaseEngine* pEngine);
        virtual ~MyBall();
        void Draw(void);
        void DoUpdate(int currentTime);
    protected:

     private:
        double m_dSX;
        double m_dSY;
        double m_dX;
        double m_dY;
};

#endif // MYBALL_H
