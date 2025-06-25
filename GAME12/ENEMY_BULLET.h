#pragma once
#include "BULLET.h"

namespace GAME12 {

    class ENEMY_BULLET :
        public BULLET
    {
    public:
        ENEMY_BULLET(class GAME* game);
        ~ENEMY_BULLET();
    };

}

