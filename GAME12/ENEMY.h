#pragma once
#include "CHARACTER.h"

namespace GAME12 {

    class ENEMY :
        public CHARACTER
    {
    private:
        float BulletLaunchInterval = 0;
        float BulletLaunchRestTime = 0;
        float BulletSpeed = 0;
        float CenterPosY = 0;
        float MoveAngle = 0;
        float MoveAngSpeed = 0;
        float MoveRadius = 0;
    public:
        ENEMY(class GAME* game);
        ~ENEMY();
        void init(float px, float py);
        void update();
        void move();
        void launch();
        void setCenterPosY(float y);
        void damage();
    };

}
